# !/bin/python3
# encoding: utf-8
import os, cgi, json, hashlib, hmac, subprocess
from http.server import BaseHTTPRequestHandler, HTTPServer

SECRET_KEY = None
REPO_FULLNAME = None


class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(204)

    def do_POST(self):
        ctype, _ = cgi.parse_header(self.headers['content-type'])
        event, _ = cgi.parse_header(self.headers['x-github-event'])
        remote_digest, _ = cgi.parse_header(self.headers['x-hub-signature'])
        if event is None:
            self.send_error(400, 'event is none')
            return
        if ctype != 'application/json':
            self.send_error(400, 'only json supported')
            return
        data = self.rfile.read(int(self.headers['content-length']))
        data = data.decode()
        hmac_digest = hmac.new(SECRET_KEY.encode(), msg=data.encode(), digestmod=hashlib.sha1)
        print(hmac_digest.hexdigest())
        if not hmac.compare_digest("sha1=" + hmac_digest.hexdigest(), remote_digest):
            self.send_error(417, "Signature error")
            return
        try:
            data = json.loads(data)
        except json.JSONDecodeError:
            self.send_error(400, 'json decode error')
            return
        print("Event: %s" % event)
        try:
            if data['repository']['full_name'] != REPO_FULLNAME:
                raise Exception("full_name not match")
            ret = subprocess.call(["git", "pull"], cwd=data['repository']['name'])
            if ret != 0:
                raise Exception("git pull error")
        except KeyError:
            self.send_error(400, "KeyError happened!")
        except Exception as e:
            error, = e.args
            self.send_error(400, "error: %s" % error)
        else:
            self.send_response(204)
            self.send_header("Content-Type", "text/plain")
            self.send_header("X-Hook", "v0.1")
            self.end_headers()


def start_server(port):
    http_server = HTTPServer(('', int(port)), RequestHandler)
    print("Server running at 0.0.0.0:%s" % str(port))
    http_server.serve_forever()


if __name__ == "__main__":
    if SECRET_KEY is None:
        SECRET_KEY = os.getenv('SECRET_KEY', None)
    if REPO_FULLNAME is None:
        REPO_FULLNAME = os.getenv('REPO_FULLNAME', None)
    if SECRET_KEY is None:
        print("""SECRET_KEY NOT SET!
        Please set SECRET_KEY in env or edit source code!""")
        exit(1)
    if REPO_FULLNAME is None:
        print("""REPO_FULLNAME NOT SET!
        Please set REPO_FULLNAME in env or edit source code!
        """)
    print("REPO_FULLNAME is %s" % REPO_FULLNAME)
    start_server(8080)
