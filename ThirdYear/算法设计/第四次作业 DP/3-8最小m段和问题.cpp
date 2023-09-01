#include <bits/stdc++.h>

using namespace std;
const int N = 105;

int dp[N][N], a[N];

int main(){
	int n, m; cin >> n >> m;
	
	for(int i = 1; i <= n; ++ i){
		cin >> a[i]; dp[i][1] += dp[i - 1][1] + a[i]; // dp[i][1]是当前段的总和
	} 
	
	for(int i = 1; i <= n; ++ i){
		for(int j = 2; j <= m; ++ j){
			int mn = INT_MAX;
			for(int k = 1; k <= i; ++ k){
				int t = max(dp[k][j - 1], dp[i][1] - dp[k][1]);
				mn = min(mn, t);
			}
			dp[i][j] = mn;
		}
	}
	cout << dp[n][m];
}
