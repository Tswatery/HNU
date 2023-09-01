#include <bits/stdc++.h>

using namespace std;

const int N = 500;
int dp[N][N], mx[N][N];
int S[N], a[N];

int main(){
	int n; cin >> n;
	for(int i = 1; i <= n; ++ i){
		cin >> a[i];
		a[i + n] = a[i];
	}
	for(int i = 1; i <= 2 * n; ++ i) S[i] = S[i - 1] + a[i];
	
	for(int len = 2; len <= n; ++ len){
		for(int l = 1; l <= 2 * n - 1; ++ l){
			int r = len + l - 1;
			dp[l][r] = 1e8; mx[l][r] = -1;
			for(int k = l; k < r && k <= 2 * n - 1; ++ k){
				dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + S[r] - S[l - 1]);
				mx[l][r] = max(mx[l][r], mx[l][k] + mx[k + 1][r] + S[r] - S[l - 1]);	
			}
		}
	}
	int mi = dp[1][n], ma = mx[1][n];
	
	for(int i = 1; i <= n - 1; ++ i){
		mi = min(mi, dp[i][i + n - 1]);
		ma = max(ma, mx[i][i + n - 1]);
	}
	cout << mi << endl;
	cout << ma << endl;
}
