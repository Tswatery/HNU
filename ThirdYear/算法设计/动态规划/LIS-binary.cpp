#include <bits/stdc++.h>

using namespace std;

// �����õ������������ ����ϣ���������ľ����ܵ��� �������ϣ��������������ĩβ���ϵ���������������ʱ������С

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
