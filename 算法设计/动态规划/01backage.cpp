#include <bits/stdc++.h>

using namespace std;

int n, m; // n�Ǳ�����С m�Ǳ�������

const int N = 10;

int w[N], p[N]; // ��ʾ��i����Ʒ���������ֵ
bool st[N];
int res = -1;

void dfs(int start, int sum_w, int sum){
	if(sum_w > m) return ; //��֦
	if(start == n && sum_w == m && sum > res) {res = sum; return ;}
	if(start > n) return ; // ��֦
	
	
	st[start] = true;
	dfs(start + 1, sum_w + w[start], sum + p[start]);
	st[start] = false; // ����
	dfs(start + 1, sum_w, sum);
}

int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; ++ i)
		cin >> w[i] >> p[i];
		
	dfs(1, 0, 0);
	
	cout << res;
	
}
