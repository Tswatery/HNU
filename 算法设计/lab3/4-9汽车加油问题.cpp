#include <bits/stdc++.h>
#include <windows.h>

using namespace std;
#define int long long

const int N = 1e7 + 10;
int a[N];

signed main(){
    freopen("test.txt", "r", stdin);
    freopen("out1.txt", "w", stdout);

    
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    double time;

    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);
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

    QueryPerformanceCounter(&nEndTime);
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;

	cout << endl;

    cout << "timeÎª£º"<< time;

}
