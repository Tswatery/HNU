#include <bits/stdc++.h>

using namespace std;

// 如果想得到最长上升子序列 我们希望它上升的尽可能的慢 因此我们希望在上升子序列末尾加上的数在满足条件的时候尽量的小

int LIS(vector<int>& nums) {
    int n = nums.size(), len = 1;
    vector<int> d(n + 1, 0);

    d[len] = nums[0];
    for(int i = 1; i < n; ++ i){
        if(nums[i] > d[len]) d[++ len] = nums[i];
        else {
            int l = 1, r = len, pos = 0;
            while(l <= r){
                int mid = (l + r) >> 1;
                if(d[mid] < nums[i]) {
                    pos = mid;
                    l = mid + 1;
                }else r = mid - 1;
            }
            d[pos + 1] = nums[i]; 
        }
    }
    return len;
}

int main(){
	vector<int> a;
	int n;
	cin >> n;
	for(int i = 0; i < n; ++ i){
		int x; cin >> x; a.push_back(x);
	}
	cout << LIS(a);
	
}
