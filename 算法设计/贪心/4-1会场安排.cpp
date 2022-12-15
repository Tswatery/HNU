#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
int s[N], f[N];

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; ++ i) {
        cin >> s[i] >> f[i];
    }

    int cnt = 1, j = 0;
    sort(s, s + n);
    sort(f, f + n);

    for(int i = 1; i < n; ++ i) {
        if (f[j] <= s[i]) j++;
        else cnt++;
    }

    cout << cnt;
}
