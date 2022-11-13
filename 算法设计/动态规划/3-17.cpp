#include <bits/stdc++.h>

using namespace std;

string a, b;

const int N = 1e3;
int dp[N][N];

int main(){
	cin >> a >> b;
	int k; cin >> k;
	
	for(int i = 0; i <= b.size(); ++ i)
		dp[0][i] = i * k;// 边界条件 a中不选串的时候最短的距离是i * k 便于递推
		
	for(int i = 0; i <= a.size(); ++ i)
		dp[i][0] = i * k;
		
	for(int i = 1; i <= a.size(); ++ i){
		for(int j = 1; j <= b.size(); ++ j){
			dp[i][j] = min(dp[i - 1][j - 1] + abs(a[i - 1] - b[j - 1]), min(dp[i - 1][j] + k, dp[i][j - 1] + k));
		}
	}
	
	cout << dp[a.size()][b.size()];
}
