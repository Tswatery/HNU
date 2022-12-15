#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
int a[N];

int main(){
    int n, k; cin >> n >> k;
    for(int i = 0; i <= k; ++ i) cin >> a[i];

    int res = 0, cnt = n;
    for(int i = 0; i <= k; ++ i){
        if(cnt > a[i]){
            cnt -= a[i];
        }else if(n < a[i]){
            res = -1;
            break;
        }else {
            cnt = n - a[i]; res ++;
        }
    }
    if(res == -1) cout << "No Solution\n";
    else cout << res << endl;
}
