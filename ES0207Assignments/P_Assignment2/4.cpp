#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

vector<int> calculatePrefixSum(const vector<int>& v) {
    int n = v.size();
    vector<int> prefixSum(n + 1, 0);

    for (int i = 1; i < n + 1; i++) {
        prefixSum[i] = prefixSum[i - 1] + v[i - 1];
    }

    return prefixSum;
}

bool checkSegments(const vector<vector<int>>& segments, const vector<int>& prefixSum, int k) {
    int count = 0;
    for (const vector<int>& segment : segments) {
        if (prefixSum[segment[1]] - prefixSum[segment[0] - 1] > 0) {
            count++;
        }
    }
    return count >= k;
}

int solveProblem() {
    int n, s;
    cin >> n >> s;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    vector<vector<int>> segments(s, vector<int>(2));
    for (int i = 0; i < s; i++)
        cin >> segments[i][0] >> segments[i][1];

    int queries, k;
    cin >> queries >> k;
    vector<int> queryIndices(queries);
    for (int i = 0; i < queries; i++)
        cin >> queryIndices[i];
     int left = 0, right = queries + 1;
    while (left != right) {
        int mid = (left + right) / 2;
        vector<int> newElements = v;
        for (int i = 0; i < mid; i++) {
            newElements[queryIndices[i] - 1] = abs(newElements[queryIndices[i] - 1]);
        }
        vector<int> prefixSum = calculatePrefixSum(newElements);
        if (checkSegments(segments, prefixSum, k)) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
    if (left == queries + 1)
        left = -1;

    return left;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int t;
    cin >> t;

    while (t--) {
        int result = solveProblem();
        cout << result << endl;
    }
    return 0;
}