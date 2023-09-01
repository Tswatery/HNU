#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
const int INF = 100000;
const int MAX_N = 22;
using namespace std;
//n*n��һ������
int n;
int cost[MAX_N][MAX_N];//����3���㣬���MAX_N����
struct Node
{
    bool visited[MAX_N];//�����Щ������
    int s;//��һ����
    int s_p;//��һ������ڽӵ�
    int e;//���һ����
    int e_p;//���һ������ڽӵ�
    int k;//�߹��ĵ���
    int sumv;//����·���ľ���
    int lb;//Ŀ�꺯����ֵ��Ŀ������
    bool operator <(const Node &p)const
    {
        return p.lb < lb;//Ŀ�꺯��ֵС���ȳ�����
    }
};
priority_queue<Node> pq;//����һ�����ȶ���
int low, up;//�½���Ͻ�
bool dfs_visited[MAX_N];//��dfs������������

                        //ȷ���Ͻ�,����dfs������̰���㷨����̰�ķ��Ľ����һ������ʵ��ֵ�Ĺ�����
int dfs(int u, int k, int l)//��ǰ�ڵ㣬Ŀ��ڵ㣬�Ѿ����ĵ�·��
{
    if (k == n) return l + cost[u][1];//����Ѿ������n���ڵ㣬��ֱ�ӷ���·������+��n���ڵ�ع���������
    int minlen = INF, p;
    for (int i = 1; i <= n; i++)
    {
        if (!dfs_visited[i] && minlen > cost[u][i])//ȡ�����е����������С�ı�
        {
            minlen = cost[u][i];//�ҳ�����ÿһ���ڵ㣬��ɴ�ڵ�������Ľڵ�
            p = i;
        }
    }
    dfs_visited[p] = true;//��pΪ��һ���ڵ��������
    return dfs(p, k + 1, l + minlen);
}
void get_up()
{
    dfs_visited[1] = true;//�Ե�һ������Ϊ���
    up = dfs(1, 1, 0);
}
//�����ּ򵥴ֱ��ķ�����ȡ�ض�С�ڽ����һ��ֵ
void get_low()
{
    //ȡÿ����Сֵ֮����Ϊ�½�
    low = 0;
    for (int i = 1; i <= n; i++)
    {
        //����һ����ͬ��map����ʱ���飬����memcpy
        int tmpA[MAX_N];
        for (int j = 1; j <= n; j++)
        {
            tmpA[j] = cost[i][j];
        }
        sort(tmpA + 1, tmpA + 1 + n);//����ʱ�������������
        low += tmpA[1];
    }
}
int get_lb(Node p)
{
    int ret = p.sumv * 2;//·���ϵĵ�ľ���Ķ���
    int min1 = INF, min2 = INF;//�����յ��������ı�
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
    //̰�ķ�ȷ���Ͻ�
    get_up();
    //ȡÿ����С�ı�֮����Ϊ�½�
    //cout << up << endl;//test
    get_low();
    //cout << low << endl;//test
    //���ó�ʼ��,Ĭ�ϴ�1��ʼ
    Node star;
    star.s = 1;//���Ϊ1
    star.e = 1;//�յ�Ϊ1
    star.k = 1;//�߹���1����
    for (int i = 1; i <= n; i++)
    {
        star.visited[i] = false;
    }
    star.visited[1] = true;
    star.sumv = 0;//������·�������ʼ��
    star.lb = low;//��Ŀ��ֵ�ȵ����½�  
    int ret = INF;//retΪ����Ľ�
    pq.push(star);//�����������
    while (pq.size())
    {
      
        Node tmp = pq.top();pq.pop();
        if (tmp.k == n - 1)//����Ѿ��߹���n-1����
        {
            //�����һ��û���ߵĵ�
            int p;
            for (int i = 1; i <= n; i++)
            {
                if (!tmp.visited[i])
                {
                    p = i;//��û���ߵ��Ǹ���Ϊ�������ߵĵ�
                    break;
                }
            }
            int ans = tmp.sumv + cost[p][tmp.s] + cost[tmp.e][p];//������+�ص���ʼ����+�ߵ�P������
            //�����ǰ��·���ͱ����е�Ŀ�꺯��ֵ��С������
            if (ans <= tmp.lb)
            {
                ret = min(ans, ret);
                break;
            }
            //����������������ܵ�·���ͣ��������Ͻ�
            else
            {
                up = min(up, ans);//�Ͻ����Ϊ���ӽ�Ŀ���ansֵ
                ret = min(ret, ans);
                continue;
            }
        }
        //��ǰ�����������չ�ĵ������ȼ�����
        Node next;
        for (int i = 1; i <= n; i++)
        {
            if (!tmp.visited[i])
            {
                //cout << "test" << endl;
                next.s = tmp.s;//����tmp�ߵ�next����㲻��          
                next.sumv = tmp.sumv + cost[tmp.e][i];//����·����              
                next.e = i;//�������һ����              
                next.k = tmp.k + 1;//�����߹��Ķ�����              
                for (int j = 1; j <= n; j++) next.visited[j] = tmp.visited[j];//tmp�����ĵ�Ҳ��next�����ĵ�
                next.visited[i] = true;//��ȻҲҪ���µ�ǰ��
                //cout << next.visited[i] << endl;
                next.lb = get_lb(next);//��Ŀ�꺯��
                //cout << next.lb << endl;
                if (next.lb > up) continue;//��������Ͻ�Ͳ��������
                pq.push(next);//����������
                //cout << "test" << endl;
            }
        }
        //cout << pq.size() << endl;BUG:����Ϊ0
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
