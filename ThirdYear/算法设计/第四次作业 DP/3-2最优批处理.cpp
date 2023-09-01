#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
int t[N], f[N], sumt[N], sumf[N], dp[N];
int n, S;

int main(){
	cin >> n >> S;
	memset(dp, 0x3f, sizeof dp);
	
	for(int i = 1; i <= n; ++ i)
		cin >> t[i] >> f[i];
		
	for(int i = 1; i <= n; ++ i){
		sumt[i] = sumt[i - 1] + t[i];
		sumf[i] = sumf[i - 1] + f[i];
	}
	dp[n + 1] = 0;
	for(int i = n; i > 0; -- i)
		for(int j = i + 1; j <= n + 1; ++ j)
			dp[i] = min(dp[i], dp[j] + (S + sumt[j - 1] - sumt[i - 1]) * (sumf[n] - sumf[i - 1]));
	cout << dp[1];
}

// 较简单的DP 要注意的是边界条件
