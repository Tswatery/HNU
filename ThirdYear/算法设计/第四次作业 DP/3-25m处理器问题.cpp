#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;
int dp[N][N];
int d[N];
int a[N];

int main(){
	int n, m;
	cin >> n >> m;
	
	memset(dp, 0, sizeof dp);
	memset(d, 0, sizeof d);
	
	for(int i = 1; i <= n; ++ i){
		cin >> a[i];
		d[i] = d[i - 1] + a[i] * a[i];
		dp[i][1] = d[i];
	}
	
	for(int j = 2; j <= n && j <= m; ++ j){
		// j 为处理器的个数
		for(int i = j; i <= n; ++ i){
			dp[i][j] = 0x3f3f3f3f;
			for(int k = j - 1; k <= i; ++ k) // 前j - 1
				dp[i][j] = min(dp[i][j], max(dp[k][j - 1], d[i] - d[k]));
		}
	}
	cout << sqrt(dp[n][m]);
}
