# !/bin/python3
# encoding: utf-8
import os, cgi, json
from http.server import BaseHTTPRequestHandler, HTTPServer

SECRET_KEY = ""


class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(418)
        self.send_header('X-Hook', 'I am a teapot!')
        self.end_headers()

    def do_POST(self):
        ctype, _ = cgi.parse_header(self.headers['content-type'])
        event = cgi.parse_header(self.headers['X-Github-Event'])
        if ctype != 'application/json':
            self.send_error(400, 'only json supported')
            return
        data = self.rfile.read(int(self.headers['content-length']))
        data = data.decode()
        try:
            data = json.loads(data)
        except json.JSONDecodeError:
            self.send_error(400, 'json decode error')
            return
        print("Event: %s" % event)
        print(data)
        self.send_response(204)
        self.send_header("Content-Type", "text/plain")
        self.send_header("X-Hook", "v0.1")
        self.end_headers()


def start_server(port):
    http_server = HTTPServer(('', int(port)), RequestHandler)
    http_server.serve_forever()


if __name__ == "__main__":
    start_server(8080)
