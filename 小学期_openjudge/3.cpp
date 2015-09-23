#include<iostream>
//#define DEBUG
using namespace std;
int a[101][101];
int main()
{
	int n;
	cin >> n;
	for (int cnt=1;cnt<=n;++cnt)
	{
		int sum=0;
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n;++j)
				cin >> a[i][j];
		int m=n;
		while(1){
		for (int i=1;i<=m;++i)
		{
			int min=a[i][1];
			for (int j=2;j<=m;++j)
				min=(a[i][j]<min)?a[i][j]:min;
			for (int j=1;j<=m;++j)
				a[i][j]-=min;
		}
		for (int j=1;j<=m;++j)
		{
			int min=a[1][j];
			for (int i=2;i<=m;++i)
				min=(a[i][j]<min)?a[i][j]:min;
			for (int i=1;i<=m;++i)
				a[i][j]-=min;
		}
		#ifdef DEBUG
		cout << "====DEBUG MATRIX====" << endl;
		for (int i=1;i<=m;++i)
		{
			for (int j=1;j<=m;++j)
				cout << a[i][j] << " ";
			cout << endl;
		}
		cout << "====END OF DEBUG====" << endl;
		#endif
		sum+=a[2][2];
		for (int i=2;i<m;++i)
			for (int j=1;j<=m;++j)
				a[i][j]=a[i+1][j];
		for (int j=2;j<m;++j)
			for (int i=1;i<m;++i)
				a[i][j]=a[i][j+1];
		--m;
		cout << "====DEBUG MATRIX====" << endl;
		for (int i=1;i<=m;++i)
		{
			for (int j=1;j<=m;++j)
				cout << a[i][j] << " ";
			cout << endl;
		}
		cout << "====END OF DEBUG====" << endl;
		if (m==1)
		{
			cout << sum << endl;
			break;
		}	
		}
	}
	return 0;
}
