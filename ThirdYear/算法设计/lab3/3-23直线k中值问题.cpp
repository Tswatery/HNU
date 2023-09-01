#include <bits/stdc++.h>

using namespace std;
struct City{
	bool operator <(City c){
		return x<=c.x;
	}
	City(){
		x=w=c=0;
	}
	static void init(int n);
	float x;
	float w;
	float c;
};
int t[1001][101],trans[1001][1001],p[1001][1001]; 
City* city;

float countPlus(int r,int pos){
	City c1=city[r],c2=city[pos];
	return c2.w*(c2.x-c1.x);
}

void init(int n){
	float cost,mid;
	City c1,c2,c3;
	for(int j=1;j<=n;j++){
		c1=city[j];
		cost=c1.c;
		for(int i=1;i<j;i++){
			c2=city[i];
			cost+=c2.w*(c1.x-c2.x);
		}
		trans[0][j]=cost;
	} 
	for(int i=1;i<n;i++)
		for(int j=i+1; j<=n;j++){
			c1=city[i];
			c2=city[j];
			cost=c2.c;
			mid=(c1.x+c2.x)/2;
			for(int k=i+1;k<j;k++){
				c3=city[k];
				if(c3.x>mid){
					cost+=c3.w*(c2.x+c1.x-2*c3.x); 
				}
			}
			trans[i][j]=cost; 
		}
}
void solve(int n,int k){
	sort(city+1,city+n+1);
	init(n);
	int max;
	float f1,f2;
	for(int i=1;i<=n;i++){
		max=min(k,i);
		for(int j=1;j<=max;j++){
			f2=t[i-1][j-1]+trans[ p[i-1][j-1] ] [ i ];
			if(j==i){
				t[i][j]=f2;
				p[i][j]=i;
			}
			else{
				f1=t[i-1][j]+countPlus(p[i-1][j],i);
				t[i][j]=min(f1,f2);
				if(f2<=f1){
					p[i][j]=i;
				}
				else {
					p[i][j]=p[i-1][j];
				}
			}
		}
	}
}
void output(int n,int k){
	int min=0x7fffffff,num=0;
	for(int i=1;i<=k;i++)
		if(t[n][i]<min){
			min=t[n][i];
			num=k;
		}
	cout<<min; 
}
int main(){
	int n,k;
	cin>>n>>k;
	city=new City[n+1];
	City C;
	for(int i=1;i<=n;i++){
		cin>>C.x>>C.w>>C.c;
		city[i]=C;
	}
	solve(n,k);
	output(n,k);
	return 0;
}
