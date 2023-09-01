int main(){
    int n; cin >> n;
    for(int i = 1; i <= n; ++ i) cin >> a[i];
    for(int i = 1; i <= n; ++ i) cin >> b[i];
    int t1 = 0, t2 = 0;
    dp[1][1] = min(a[1], b[1]);

    int A = 0, B = 0;
    dp[1][0] = a[1];
    dp[1][1] = b[1];

    for(int i = 2; i <= n; ++ i){
        if(dp[i - 1][0] > dp[i - 1][1]){
            B = dp[i - 1][1] ; //此时B应该更新
            dp[i][0] = a[i] + A;
            dp[i][1] = b[i] + B;
        }else{
            A = dp[i - 1][0]; // 此时A应该更新
            dp[i][0] = a[i] + A;
            dp[i][1] = b[i] + B;
        }
    }

    if(dp[n][0] > dp[n][1]) B = dp[n][1];
    else A = dp[n][0];

    cout << max(A, B);
}
