#include <bits/stdc++.h>
#include <windows.h>


using namespace std;

const int MAXN = 10;
const int MAX = 100;
int n;
int sum[MAXN][MAX];
bool s[MAXN][MAX];
int t[MAX];
int best[MAX];
int k;  //搜索的深度，逐渐加深

void out()
{ 
    for(int i=1; i<=n; i++)  //划分个数
    {
        for(int j=1; j<=k; j++)  //每个数字
            if(i == best[j])  //如果数字j属于第i个划分
                cout << j << "\t";  //输出数字j
        cout << endl;
    }
}

void record()
{ 
    for(int i=1; i<=n; i++)  //划分个数
    {
        for(int j=1; j<=k; j++)   //每个数字
            if(i == t[j])  //如果数字j属于第i个划分
                best[j] =  i;
    }
}


clock_t start, finish;
double duration = 0;
bool backtrack(int dep)
{

    finish = clock();
    duration += (double) (finish-start)/CLOCKS_PER_SEC;
    start = finish;
    if(duration > 15.0)
    { 
        cout << duration << endl;
        cout << "No Solution!\n";
        return false;
    }

    if(dep > k)
    {   
        record();
        return true;
    }
    for(int i=1; i<=n; i++)  //第i个划分
        if(sum[i][dep] == 0)
        { 
            t[dep] = i;  //dep被选入划分i中
            s[i][dep] = true;
            for(int j=1; j<dep; j++) 
                if(s[i][j])  //如果数字j已加入划分i中
                    sum[i][dep+j]++;  //j+dep便不能再加入
            if(backtrack(dep+1))
                return true;
            for(int j=1; j<dep; j++)
                if(s[i][j])
                    sum[i][dep+j]--;
            s[i][dep] = false;
        }
    return false;
}

void search()
{
    k = n;
    while(true)
    {
        memset(sum, 0, sizeof(sum));
        memset(t, 0, sizeof(t));
        memset(s, 0, sizeof(s));

        if(backtrack(1))
            ++k;  //深度逐渐加大
        else
            break;  
    }
    --k;
}

int main()
{
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    double time;

    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);
    cout << "输入正整数n：";
    cin >> n;  

    search();
    cout << "\n计算结果为：F(" << n << ") = " << k << "\n";
    out();  //输出划分中的数字
    cout << endl;


    QueryPerformanceCounter(&nEndTime);
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;

    cout << "time是" << time << endl;



}
