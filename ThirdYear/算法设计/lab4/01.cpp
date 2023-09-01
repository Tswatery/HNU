#include<iostream>//cin cout
#include<queue>//队列 
#include<cstring>//字符串处理 
#include<algorithm>//提供许多泛型算法和函数sort 
#include<stdlib.h>
#include<windows.h>
//特殊定义 
using namespace std;// 用到输入输出的时候就可以省略std::不用每次都写 
const int maxn=1e5 + 10;//常变量maxn 最多物品数 


//定义结构体 
struct object//物品结构体
{
    double w;//物品重量
    double v;//物品价值
    double d;//物品单位重量的价值（价值重量比）
    int id;//物品序号
} a[maxn];

int n,W;//物品种数，背包容量
int bestx[maxn];//最优解 
int bestv;//最优总价值

//预处理重排 
bool tmp1(object b1,object b2)//物品优先级，以单位价值高的优先
{
    return b1.d>b2.d;
}

int init()//初始化
{
    memset(bestx,0,sizeof(bestx));//初始化最优解bestx数组，全为0 
    bestv=0;//最优总价值 
    sort(a+1,a+n+1,tmp1);//数组的降序排序 (按单位价值排序) +1:在数组中先从1位置开始存储 
   	for(int i=1;i<=n;i++)
    	printf("a[%d]=%f ",i,a[i].d);
    printf("\n");
    return 0;
   
}
struct node//结点结构体
{
    double cv,lv;//当前价值，价值上界（注意类型）
    int lw;//剩余容量
    int id;//物品排序后的序号
    int x[maxn];//解向量
    node()
    {
        memset(x,0,sizeof(x));//初始化解向量组x 全为0 
        lv=0;//价值上界定义为0 
    }
    node(int cvv,int lvv,int lww,int idd)//构造函数
    {
        memset(x,0,sizeof(x));
        cv=cvv;//当前价值 
        lv=lvv;//价值上界 
        lw=lww;//背包剩余容量 
        id=idd;//物品排序后的序号 
    }
};

struct tmp2//结点优先级，价值上界高的优先级高
{
    bool operator() (node& n1,node& n2)
    {
        return n1.lv<n2.lv;
    }
};
double CalInf(node t)//计算价值上界：当前背包中物品的价值 + 剩余物品装满背包剩余容量的最大价值 
{
    int num=t.id;//获取此节点序号 
    double maxvalue=t.cv;//获取此节点当前价值 
    int left=t.lw;//获取背包剩余容量 
    while(num<=n&&left>=a[num].w)//循环每一个物品 满足条件：剩余容量大于等于此节点物品重量 
    {
        left-=a[num].w;//更新剩余容量 (-此节点物品重量)
        maxvalue+=a[num].v;//更新当前价值 
        ++num;//更新到下一节点 
    }
    if(num<=n&&left>0)//一定要加下标限制  背包剩余容量大于0 
        maxvalue+=1.0*a[num].v/a[num].w*left;
	//最大价值 = 当前重量+剩余物品中单位重量价值最大的物品的平均价值*剩余容量
    return maxvalue;
}

void bfs()
{
    priority_queue<node,vector<node>,tmp2> q;//结构体类型的优先队列 
    int sumv=0;
    int i;
    for(i=1; i<=n; ++i)
            sumv+=a[i].v;//价值上界sumv为所有物品价值之和 
    q.push(node(0,sumv,W,1));//堆内部放入根结点node(当前价值0，价值上界0，背包剩余容量W，物品排序后的序号1) 

    while(!q.empty())
    {
        node live,lchild,rchild;
        live=q.top();//将指针置于堆顶部  获取顶部元素 
        q.pop();//从堆中取出数据 弹出顶部元素 
        int t=live.id;//当前处理物品的序号
        if(t>n||live.lw==0)//到达叶子结点或者没有剩余容量了
        {
            if(live.cv>=bestv)//更新最优解,不加等号的话，第一次计算得到的值不会更新
            {//当前价值大于等于最优总价值 
                for(int i=1; i<=n; ++i)
                    bestx[i]=live.x[i];//最优解=解向量 
                bestv=live.cv;
            }
            continue;
        }
        if(live.lv<bestv)//不满足限界条件 价值上界小于当前价值(即最优总价值) ，不再拓展 
            continue;//限界剪枝：当问题已经搜索到一个可行解时，将其与当前求解状态进行比较，不满足限界条件进行剪枝 

        if(live.lw>=a[t].w)//满足约束条件，背包剩余容量大于等于物品重量，可以放入背包，可以生成左孩子
        {
            lchild.cv=live.cv+a[t].v;//左孩子结点当前价值 = 当前价值+物品价值 
            lchild.lw=live.lw-a[t].w;//左孩子结点剩余容量 =  背包剩余容量-物品重量 
            lchild.id=t+1;//左孩子结点物品排序后的序号=下一物品序号 
            lchild.lv=CalInf(lchild);//左孩子价值上界
            for(int i=1; i<=n; ++i)
                lchild.x[i]=live.x[i];
            lchild.x[t]=1;
            if(lchild.cv>bestv)//注意要更新最优值
                bestv=lchild.cv;//最优价值更新为左孩子当前价值 
            q.push(lchild);
        }

        rchild.cv=live.cv;//右孩子当前价值=当前处理物品价值 
        rchild.lw=live.lw;//右孩子剩余容量 
        rchild.id=t+1;//右孩子序号+1 
        rchild.lv=CalInf(rchild);//右孩子价值上界 
        if(rchild.lv>=bestv)//(判断价值上界)满足限界条件，不放入背包，可以生成右孩子
        {
            for(int i=1; i<=n; ++i)
                rchild.x[i]=live.x[i];
            rchild.x[t]=0;
            q.push(rchild);//加入右节点 
        }
    }
}
void output()
{
    cout<<"可装载物品的最大价值为："<<bestv<<endl;
    cout<<"装入的物品为：";
    for(int i=1; i<=n; ++i)
        if(bestx[i])
            cout<<a[i].id<<" ";
    cout<<endl;
    return ;
}

int main()
{
    cout<<"请输入物品个数：";
    cin>>n;
    cout<<"请输入背包容量：";
    cin>>W;
    /*cout<<"请依次输入物品的重量和价值：";*/
	srand((unsigned)time(NULL));
    for(int i=1;i<=n;++i)//随机生成价值和重量
	{
		a[i].v=rand()%n+1;
		a[i].w=rand()%n+1;
  		cout<<"物品";
		cout<<i;
		cout<<"重量";
		cout<<a[i].w;
		cout<<"价值";
		cout<<a[i].v<<endl; 
    	a[i].d=a[i].v/a[i].w;//物品单位价值 
        a[i].id=i;//物品序号 
        cout<<"单位价值";
        cout<<a[i].d<<endl;
        
	}

    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    double time;

    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);

   	init();
    bfs();
    output();


    QueryPerformanceCounter(&nEndTime);
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;

    cout << "time是" << time << endl;



}
