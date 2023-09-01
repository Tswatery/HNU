#include<iostream>//cin cout
#include<queue>//���� 
#include<cstring>//�ַ������� 
#include<algorithm>//�ṩ��෺���㷨�ͺ���sort 
#include<stdlib.h>
#include<windows.h>
//���ⶨ�� 
using namespace std;// �õ����������ʱ��Ϳ���ʡ��std::����ÿ�ζ�д 
const int maxn=1e5 + 10;//������maxn �����Ʒ�� 


//����ṹ�� 
struct object//��Ʒ�ṹ��
{
    double w;//��Ʒ����
    double v;//��Ʒ��ֵ
    double d;//��Ʒ��λ�����ļ�ֵ����ֵ�����ȣ�
    int id;//��Ʒ���
} a[maxn];

int n,W;//��Ʒ��������������
int bestx[maxn];//���Ž� 
int bestv;//�����ܼ�ֵ

//Ԥ�������� 
bool tmp1(object b1,object b2)//��Ʒ���ȼ����Ե�λ��ֵ�ߵ�����
{
    return b1.d>b2.d;
}

int init()//��ʼ��
{
    memset(bestx,0,sizeof(bestx));//��ʼ�����Ž�bestx���飬ȫΪ0 
    bestv=0;//�����ܼ�ֵ 
    sort(a+1,a+n+1,tmp1);//����Ľ������� (����λ��ֵ����) +1:���������ȴ�1λ�ÿ�ʼ�洢 
   	for(int i=1;i<=n;i++)
    	printf("a[%d]=%f ",i,a[i].d);
    printf("\n");
    return 0;
   
}
struct node//���ṹ��
{
    double cv,lv;//��ǰ��ֵ����ֵ�Ͻ磨ע�����ͣ�
    int lw;//ʣ������
    int id;//��Ʒ���������
    int x[maxn];//������
    node()
    {
        memset(x,0,sizeof(x));//��ʼ����������x ȫΪ0 
        lv=0;//��ֵ�Ͻ綨��Ϊ0 
    }
    node(int cvv,int lvv,int lww,int idd)//���캯��
    {
        memset(x,0,sizeof(x));
        cv=cvv;//��ǰ��ֵ 
        lv=lvv;//��ֵ�Ͻ� 
        lw=lww;//����ʣ������ 
        id=idd;//��Ʒ��������� 
    }
};

struct tmp2//������ȼ�����ֵ�Ͻ�ߵ����ȼ���
{
    bool operator() (node& n1,node& n2)
    {
        return n1.lv<n2.lv;
    }
};
double CalInf(node t)//�����ֵ�Ͻ磺��ǰ��������Ʒ�ļ�ֵ + ʣ����Ʒװ������ʣ������������ֵ 
{
    int num=t.id;//��ȡ�˽ڵ���� 
    double maxvalue=t.cv;//��ȡ�˽ڵ㵱ǰ��ֵ 
    int left=t.lw;//��ȡ����ʣ������ 
    while(num<=n&&left>=a[num].w)//ѭ��ÿһ����Ʒ ����������ʣ���������ڵ��ڴ˽ڵ���Ʒ���� 
    {
        left-=a[num].w;//����ʣ������ (-�˽ڵ���Ʒ����)
        maxvalue+=a[num].v;//���µ�ǰ��ֵ 
        ++num;//���µ���һ�ڵ� 
    }
    if(num<=n&&left>0)//һ��Ҫ���±�����  ����ʣ����������0 
        maxvalue+=1.0*a[num].v/a[num].w*left;
	//����ֵ = ��ǰ����+ʣ����Ʒ�е�λ������ֵ������Ʒ��ƽ����ֵ*ʣ������
    return maxvalue;
}

void bfs()
{
    priority_queue<node,vector<node>,tmp2> q;//�ṹ�����͵����ȶ��� 
    int sumv=0;
    int i;
    for(i=1; i<=n; ++i)
            sumv+=a[i].v;//��ֵ�Ͻ�sumvΪ������Ʒ��ֵ֮�� 
    q.push(node(0,sumv,W,1));//���ڲ���������node(��ǰ��ֵ0����ֵ�Ͻ�0������ʣ������W����Ʒ���������1) 

    while(!q.empty())
    {
        node live,lchild,rchild;
        live=q.top();//��ָ�����ڶѶ���  ��ȡ����Ԫ�� 
        q.pop();//�Ӷ���ȡ������ ��������Ԫ�� 
        int t=live.id;//��ǰ������Ʒ�����
        if(t>n||live.lw==0)//����Ҷ�ӽ�����û��ʣ��������
        {
            if(live.cv>=bestv)//�������Ž�,���ӵȺŵĻ�����һ�μ���õ���ֵ�������
            {//��ǰ��ֵ���ڵ��������ܼ�ֵ 
                for(int i=1; i<=n; ++i)
                    bestx[i]=live.x[i];//���Ž�=������ 
                bestv=live.cv;
            }
            continue;
        }
        if(live.lv<bestv)//�������޽����� ��ֵ�Ͻ�С�ڵ�ǰ��ֵ(�������ܼ�ֵ) ��������չ 
            continue;//�޽��֦���������Ѿ�������һ�����н�ʱ�������뵱ǰ���״̬���бȽϣ��������޽��������м�֦ 

        if(live.lw>=a[t].w)//����Լ������������ʣ���������ڵ�����Ʒ���������Է��뱳����������������
        {
            lchild.cv=live.cv+a[t].v;//���ӽ�㵱ǰ��ֵ = ��ǰ��ֵ+��Ʒ��ֵ 
            lchild.lw=live.lw-a[t].w;//���ӽ��ʣ������ =  ����ʣ������-��Ʒ���� 
            lchild.id=t+1;//���ӽ����Ʒ���������=��һ��Ʒ��� 
            lchild.lv=CalInf(lchild);//���Ӽ�ֵ�Ͻ�
            for(int i=1; i<=n; ++i)
                lchild.x[i]=live.x[i];
            lchild.x[t]=1;
            if(lchild.cv>bestv)//ע��Ҫ��������ֵ
                bestv=lchild.cv;//���ż�ֵ����Ϊ���ӵ�ǰ��ֵ 
            q.push(lchild);
        }

        rchild.cv=live.cv;//�Һ��ӵ�ǰ��ֵ=��ǰ������Ʒ��ֵ 
        rchild.lw=live.lw;//�Һ���ʣ������ 
        rchild.id=t+1;//�Һ������+1 
        rchild.lv=CalInf(rchild);//�Һ��Ӽ�ֵ�Ͻ� 
        if(rchild.lv>=bestv)//(�жϼ�ֵ�Ͻ�)�����޽������������뱳�������������Һ���
        {
            for(int i=1; i<=n; ++i)
                rchild.x[i]=live.x[i];
            rchild.x[t]=0;
            q.push(rchild);//�����ҽڵ� 
        }
    }
}
void output()
{
    cout<<"��װ����Ʒ������ֵΪ��"<<bestv<<endl;
    cout<<"װ�����ƷΪ��";
    for(int i=1; i<=n; ++i)
        if(bestx[i])
            cout<<a[i].id<<" ";
    cout<<endl;
    return ;
}

int main()
{
    cout<<"��������Ʒ������";
    cin>>n;
    cout<<"�����뱳��������";
    cin>>W;
    /*cout<<"������������Ʒ�������ͼ�ֵ��";*/
	srand((unsigned)time(NULL));
    for(int i=1;i<=n;++i)//������ɼ�ֵ������
	{
		a[i].v=rand()%n+1;
		a[i].w=rand()%n+1;
  		cout<<"��Ʒ";
		cout<<i;
		cout<<"����";
		cout<<a[i].w;
		cout<<"��ֵ";
		cout<<a[i].v<<endl; 
    	a[i].d=a[i].v/a[i].w;//��Ʒ��λ��ֵ 
        a[i].id=i;//��Ʒ��� 
        cout<<"��λ��ֵ";
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

    cout << "time��" << time << endl;



}
