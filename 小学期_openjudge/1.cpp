#include<iostream>
using namespace std;
int main()
{
	int rows,pos[101],max=0;
	cin >> rows;
	pos[0]=0;
	for (int i=1;i<=rows;++i)
	{
		char end=',';
		int rowmax=0;
		while (end!='\n')
		{
			int now;
			cin >> now;
			end=cin.get();
			rowmax=(rowmax<now)?now:rowmax;
		}
		if (rowmax>max)
		{
			max=rowmax;
			pos[0]=1;
			pos[1]=i;
		}
		else if (rowmax==max)
			pos[++pos[0]]=i;
	}
	cout << max << endl << pos[1];
	for (int i=2;i<=pos[0];++i)
		cout << "," <<pos[i];
	cout << endl;
	return 0;
}
