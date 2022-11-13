#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> PII;

const int N = 2e5 + 10, M = N;

int h[N], e[M], ne[M], w[M], idx;
bool st[N]; // 当前点是否已经确定最小值
int dist[N];
int n, m; // 点数 边数 有向边

void add(int a, int b, int c){
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}

int heap_dijkstra(){
    priority_queue<PII, vector<PII>, greater<PII> > heap;
    heap.push({0 , 1});// 距离、编号
    
    while(not heap.empty()){
        auto t = heap.top(); heap.pop();
        int ver = t.second, d = t.first;
        if(st[ver]) continue;
        st[ver] = true;
        
        for(int i = h[ver]; ~i; i = ne[i]){
            int j = e[i];
            if(d + w[i] < dist[j]){
                dist[j] = d + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    return (dist[n] == 0x3f3f3f3f ? -1 : dist[n]);
}

int main(){
    memset(h, -1, sizeof h);
    memset(dist, 0x3f, sizeof dist);
    
    cin >> n >> m;
    
    for(int i = 1; i <= m; ++ i){
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c); // 加边操作
    }
    
    cout << heap_dijkstra();
}
