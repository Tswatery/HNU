#include <bits/stdc++.h>

using namespace std;

const int N = 100;

int tri[N][N];
int s[N][N];

int main(){
	int n; cin >> n;
	
	for(int i = 1; i <= n; ++ i){
		for(int j = 1; j <= i; ++ j)
			cin >> tri[i][j];
	}	
	for(int i = 1; i <= n; ++ i)
		s[n][i] = tri[n][i];
		
	for(int i = n - 1; i >= 1; -- i){
		for(int j = 1; j <= i; ++ j){
			s[i][j] = max(s[i + 1][j], s[i + 1][j + 1]) + tri[i][j];
		}
	}
	
	cout << s[1][1];
}
