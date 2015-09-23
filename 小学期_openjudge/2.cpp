#include <iostream>
#include <string>
//#define DEBUG
using namespace std;
string key[129];
int cnt[129];
int num;
string process(string input)
{
	int pos;
	if (input[0]=='+') input.erase(0,1);
	pos=(input[0]=='-')?1:0;
	while (input[pos]=='0' && pos!=input.length()-1) input.erase(pos,1);
	if (input.compare("-0")==0) input.erase(0,1);
	#ifdef DEBUG
	cout << "DEBUG:Processed: "<<input << endl;
	#endif
	return input;
}
int main()
{
	int n;
	cin >> n;
	for (int i=1;i<=n;++i)
	{
		string tmp;
		bool found=false;
		cin >> tmp;
		if (tmp.empty()) {--i;continue;}
		tmp=process(tmp);
		for (int j=1;j<=num;++j)
			if (key[j].compare(tmp)==0)
			{
				++cnt[j];
				found=true;
				break;
			}
		if (!found)
		{
			++num;
			key[num]=tmp;
			cnt[num]=1;
		}
	}
	int pos=1;
	for (int i=2;i<=num;++i)
		pos=(cnt[pos]<cnt[i])?i:pos;
	if (cnt[pos]==n)
		cout << "no" << endl;
	else
		cout << key[pos] << endl;
	return 0;
}
