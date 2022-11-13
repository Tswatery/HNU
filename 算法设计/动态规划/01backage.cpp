#include <bits/stdc++.h>

using namespace std;

int n, m; // n是背包大小 m是背包容量

const int N = 10;

int w[N], p[N]; // 表示第i个物品的质量与价值
bool st[N];
int res = -1;

void dfs(int start, int sum_w, int sum){
	if(sum_w > m) return ; //剪枝
	if(start == n && sum_w == m && sum > res) {res = sum; return ;}
	if(start > n) return ; // 剪枝
	
	
	st[start] = true;
	dfs(start + 1, sum_w + w[start], sum + p[start]);
	st[start] = false; // 回溯
	dfs(start + 1, sum_w, sum);
}

int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; ++ i)
		cin >> w[i] >> p[i];
		
	dfs(1, 0, 0);
	
	cout << res;
	
}
