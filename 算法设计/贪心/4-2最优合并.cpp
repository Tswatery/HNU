#include <bits/stdc++.h>

using namespace std;

int main(){
    priority_queue<int, vector<int>, greater<int> > heap;
    priority_queue<int> heap1;
    int n;
    cin >> n;
    while(n -- ){
        int x; cin >> x;
        heap.push(x);
        heap1.push(x);
    }
    int res = 0;
    while(heap.size() > 1){
        int a = heap.top(); heap.pop();
        int b = heap.top(); heap.pop();
        res += a + b - 1;
        heap.push(a + b);
    }
    int ans = 0;
    while(heap1.size() > 1){
        int a = heap1.top(); heap1.pop();
        int b = heap1.top(); heap1.pop();
        ans += a + b - 1;
        heap1.push(a + b);
    }
    if(!heap.size()) res += heap.top();
    if(!heap1.size()) ans += heap1.top();
    cout << ans << ' ' << res;
}
