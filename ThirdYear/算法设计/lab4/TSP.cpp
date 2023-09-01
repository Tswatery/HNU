#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
const int INF = 100000;
const int MAX_N = 22;
using namespace std;
//n*n的一个矩阵
int n;
int cost[MAX_N][MAX_N];//最少3个点，最多MAX_N个点
struct Node
{
    bool visited[MAX_N];//标记哪些点走了
    int s;//第一个点
    int s_p;//第一个点的邻接点
    int e;//最后一个点
    int e_p;//最后一个点的邻接点
    int k;//走过的点数
    int sumv;//经过路径的距离
    int lb;//目标函数的值（目标结果）
    bool operator <(const Node &p)const
    {
        return p.lb < lb;//目标函数值小的先出队列
    }
};
priority_queue<Node> pq;//创建一个优先队列
int low, up;//下界和上界
bool dfs_visited[MAX_N];//在dfs过程中搜索过

                        //确定上界,利用dfs（属于贪心算法），贪心法的结果是一个大于实际值的估测结果
int dfs(int u, int k, int l)//当前节点，目标节点，已经消耗的路径
{
    if (k == n) return l + cost[u][1];//如果已经检查了n个节点，则直接返回路径消耗+第n个节点回归起点的消耗
    int minlen = INF, p;
    for (int i = 1; i <= n; i++)
    {
        if (!dfs_visited[i] && minlen > cost[u][i])//取与所有点的连边中最小的边
        {
            minlen = cost[u][i];//找出对于每一个节点，其可达节点中最近的节点
            p = i;
        }
    }
    dfs_visited[p] = true;//以p为下一个节点继续搜索
    return dfs(p, k + 1, l + minlen);
}
void get_up()
{
    dfs_visited[1] = true;//以第一个点作为起点
    up = dfs(1, 1, 0);
}
//用这种简单粗暴的方法获取必定小于结果的一个值
void get_low()
{
    //取每行最小值之和作为下界
    low = 0;
    for (int i = 1; i <= n; i++)
    {
        //创建一个等同于map的临时数组，可用memcpy
        int tmpA[MAX_N];
        for (int j = 1; j <= n; j++)
        {
            tmpA[j] = cost[i][j];
        }
        sort(tmpA + 1, tmpA + 1 + n);//对临时的数组进行排序
        low += tmpA[1];
    }
}
int get_lb(Node p)
{
    int ret = p.sumv * 2;//路径上的点的距离的二倍
    int min1 = INF, min2 = INF;//起点和终点连出来的边
    for (int i = 1; i <= n; i++)
    {
        //cout << p.visited[i] << endl;
        if (!p.visited[i] && min1 > cost[i][p.s])
        {
            min1 = cost[i][p.s];
        }
        //cout << min1 << endl;
    }
    ret += min1;
    for (int i = 1; i <= n; i++)
    {
        if (!p.visited[i] && min2 > cost[p.e][i])
        {
            min2 = cost[p.e][i];
        }
        //cout << min2 << endl;
    }
    ret += min2;
    for (int i = 1; i <= n; i++)
    {
        if (!p.visited[i])
        {
            min1 = min2 = INF;
            for (int j = 1; j <= n; j++)
            {
                if (min1 > cost[i][j])
                    min1 = cost[i][j];
            }
            for (int j = 1; j <= n; j++)
            {
                if (min2 > cost[j][i])
                    min2 = cost[j][i];
            }
            ret += min1 + min2;
        }
    }
    return (ret + 1) / 2;
}

int solve()
{
    //贪心法确定上界
    get_up();
    //取每行最小的边之和作为下界
    //cout << up << endl;//test
    get_low();
    //cout << low << endl;//test
    //设置初始点,默认从1开始
    Node star;
    star.s = 1;//起点为1
    star.e = 1;//终点为1
    star.k = 1;//走过了1个点
    for (int i = 1; i <= n; i++)
    {
        star.visited[i] = false;
    }
    star.visited[1] = true;
    star.sumv = 0;//经过的路径距离初始化
    star.lb = low;//让目标值先等于下界  
    int ret = INF;//ret为问题的解
    pq.push(star);//将起点加入队列
    while (pq.size())
    {
      
        Node tmp = pq.top();pq.pop();
        if (tmp.k == n - 1)//如果已经走过了n-1个点
        {
            //找最后一个没有走的点
            int p;
            for (int i = 1; i <= n; i++)
            {
                if (!tmp.visited[i])
                {
                    p = i;//让没有走的那个点为最后点能走的点
                    break;
                }
            }
            int ans = tmp.sumv + cost[p][tmp.s] + cost[tmp.e][p];//已消耗+回到开始消耗+走到P的消耗
            //如果当前的路径和比所有的目标函数值都小则跳出
            if (ans <= tmp.lb)
            {
                ret = min(ans, ret);
                break;
            }
            //否则继续求其他可能的路径和，并更新上界
            else
            {
                up = min(up, ans);//上界更新为更接近目标的ans值
                ret = min(ret, ans);
                continue;
            }
        }
        //当前点可以向下扩展的点入优先级队列
        Node next;
        for (int i = 1; i <= n; i++)
        {
            if (!tmp.visited[i])
            {
                //cout << "test" << endl;
                next.s = tmp.s;//沿着tmp走到next，起点不变          
                next.sumv = tmp.sumv + cost[tmp.e][i];//更新路径和              
                next.e = i;//更新最后一个点              
                next.k = tmp.k + 1;//更新走过的顶点数              
                for (int j = 1; j <= n; j++) next.visited[j] = tmp.visited[j];//tmp经过的点也是next经过的点
                next.visited[i] = true;//自然也要更新当前点
                //cout << next.visited[i] << endl;
                next.lb = get_lb(next);//求目标函数
                //cout << next.lb << endl;
                if (next.lb > up) continue;//如果大于上界就不加入队列
                pq.push(next);//否则加入队列
                //cout << "test" << endl;
            }
        }
        //cout << pq.size() << endl;BUG:测试为0
    }
    return ret;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> cost[i][j];
            if (i == j)
            {
                cost[i][j] = INF;
            }
        }
    }
    cout << solve() << endl;
    return 0;
}
