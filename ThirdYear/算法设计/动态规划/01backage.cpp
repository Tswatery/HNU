#include <bits/stdc++.h>

using namespace std;

int n, m; // n�Ǳ�����С m�Ǳ�������

const int N = 10;

int w[N], p[N]; // ��ʾ��i����Ʒ���������ֵ
bool st[N];
int res = -1;

void dfs(int cur, int sum_w, int sum){
    if(sum_w > m) return ; //��֦
    if(cur == n && sum_w == m && sum > res) {res = sum; return ;}
    if(cur > n) return ;

    for(int i = cur; i <= n; ++ i){
        if(st[i]) continue;
        else {
            st[i] = true;
            dfs(i + 1, sum_w + w[i], sum + p[i]);
            st[i] = false;
            dfs(i + 1, sum_w, sum);
        }
    }
}

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; ++ i)
        cin >> w[i] >> p[i];

    dfs(1, 0, 0);

    cout << res;
}
