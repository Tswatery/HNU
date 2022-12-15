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
int k;  //��������ȣ��𽥼���

void out()
{ 
    for(int i=1; i<=n; i++)  //���ָ���
    {
        for(int j=1; j<=k; j++)  //ÿ������
            if(i == best[j])  //�������j���ڵ�i������
                cout << j << "\t";  //�������j
        cout << endl;
    }
}

void record()
{ 
    for(int i=1; i<=n; i++)  //���ָ���
    {
        for(int j=1; j<=k; j++)   //ÿ������
            if(i == t[j])  //�������j���ڵ�i������
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
    for(int i=1; i<=n; i++)  //��i������
        if(sum[i][dep] == 0)
        { 
            t[dep] = i;  //dep��ѡ�뻮��i��
            s[i][dep] = true;
            for(int j=1; j<dep; j++) 
                if(s[i][j])  //�������j�Ѽ��뻮��i��
                    sum[i][dep+j]++;  //j+dep�㲻���ټ���
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
            ++k;  //����𽥼Ӵ�
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
    cout << "����������n��";
    cin >> n;  

    search();
    cout << "\n������Ϊ��F(" << n << ") = " << k << "\n";
    out();  //��������е�����
    cout << endl;


    QueryPerformanceCounter(&nEndTime);
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;

    cout << "time��" << time << endl;



}
