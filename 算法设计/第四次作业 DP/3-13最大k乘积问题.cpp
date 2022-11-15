#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 20;
LL dp[N][N];

string s;

LL getval(int start, int end){
	LL res = 0;
	for(int i = start; i <= end; ++ i){
		res = res * 10 + s[i - 1] - '0';
	}
	return res;
}

int main(){
	int n, m, num;
	cin >> n >> m >> num;
	s = to_string(num);
	
	for(int i = 1; i <= n; ++ i)
		dp[i][0] = getval(1, i);
	
	for(int j = 1; j <= m - 1; ++ j){//m¶Îm - 1¸ö³ËºÅ
		for(int i = j + 1; i <= n; ++ i){
			for(int k = j; k <= i - 1; ++ k)
			dp[i][j] = max(dp[i][j], 1LL * dp[k][j - 1] * getval(k + 1, i));
		}
	}
	cout << dp[n][m - 1];
}
