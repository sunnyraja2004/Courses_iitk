#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

vector<int> depth;

void buildTree(vector<int>& arr, int l, int r, int d) {
    if (l > r) return;
    int mx = arr[l], idx = l;
    for (int i = l; i <= r; i++) {
        if (arr[i] > mx) {
            mx = arr[i];
            idx = i;
        }
    }
    depth[mx] = d;
    buildTree(arr, l, idx - 1, d + 1);
    buildTree(arr, idx + 1, r, d + 1);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        depth.assign(100001, 0); 
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        buildTree(arr, 0, n - 1, 0);
        for (int i = 0; i < n; i++) {
            cout << depth[arr[i]] << " ";
        }
        cout << endl;
    }
    return 0;
}