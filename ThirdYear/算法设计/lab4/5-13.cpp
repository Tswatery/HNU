nclude <bits/stdc++.h>
#include <windows.h>

using namespace std;

int n;
int pay[1010][1010];   //pay[i][j]表示将工作i分配给第j个人的费用为pay[i][j]
int Min=INT_MAX;   //因为要求最小值，所以将Min初始化为最大整数（int型）
int sum=0;   //记录搜索过程中得到的工作费用和
int book[21];   //用于标记一个人是否已被分配工作：book[i]=0表示没有被分配工作；book[i]=1表示已经被分配工作

void dfs(int t)
{
    if(t>=n)   //已经到达叶子结点，继续判断是否找到了最小总费用
    {
        if(Min>sum)   //没有找到最小总费用
        {
            Min=sum;   //更新最小总费用
            return;
        }
    }
    for(int i=0;i<n;i++)   //为第工作t安排人
    {
        if(!book[i])   //第i个人还没有被安排工作
        {
            book[i]=1;   //将工作t分配给第i个人
            sum+=pay[t][i];   //更新总费用
            if(sum<Min)   //如果当前得到的sum小于最小值，就向下搜索子树；否则剪枝
                dfs(t+1);
            book[i]=0;   //没有得到比Min更小的和，回溯
            sum-=pay[t][i];
        }
    }

}

int main()
{
    freopen("test.txt", "r", stdin);

    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    double time;

    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);
    cin>>n;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>pay[i][j];
        }
        book[i]=0;
    }
    dfs(0);
    cout<<Min<<endl;

    QueryPerformanceCounter(&nEndTime);
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;

    cout << "time是" << time << endl;



}
