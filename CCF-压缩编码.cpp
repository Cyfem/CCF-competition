
#include<iostream>
using namespace std;
const int INF = 1 << 30;  
int dp[1010][1010],a[1010],sum[1010];
int n;
int main()
{
	int i,j,k,t;
	cin >>n;
	for(i=1;i<=n;i++)
	{
		cin >> a[i];
		sum[i] = sum[i-1] + a[i];//用于指定区间内的计算总数 
	}
	
	//沿斜线扫描 
	for(j=2;j<=n;j++)
	{
		for(i=1,k=j;i<=n-j+1;i++,k++)
		{
			dp[i][k] = INF;
			for(t=i;t<k;t++)
			{
				if(dp[i][k] > dp[i][t]+dp[t+1][k]+sum[k]-sum[i-1])
			    {
			    	dp[i][k] = dp[i][t]+dp[t+1][k]+sum[k]-sum[i-1];
			    }
			}
		}
	}
	
	cout << dp[1][n];
	return 0;
}
