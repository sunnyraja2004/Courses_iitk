#include <iostream>
using namespace std;

long long computeMaxHeight(long long K, long long h[], int N) {
    long long maxHeight = 0;
    for (int i = 0; i < N; ++i) {
        if (h[i] > maxHeight) {
            maxHeight = h[i];
        }
    }
    
    long long left = 0, right = maxHeight + 1;
    while (left < right) {
        long long mid = left + (right - left) / 2;
        long long cost = 0;
        for (int i = 0; i < N; ++i) {
            long long he = (h[i] * (h[i] + 1)) / 2;
            long long mi = (mid * (mid + 1)) / 2;
            if (h[i] > mid) {
                cost += he - mi;
            }
        }
        if (cost <= K) {
            right = mid;
        } else {
            left = mid + 1;
            }
    }
    return left;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N;
        long long K;
        cin >> N >> K;
        long long heights[N];
        for (int i = 0; i < N; ++i) {
            cin >> heights[i];
        }
        long long ans = computeMaxHeight(K, heights, N);
        cout << ans << endl;
    }
    
    return 0;
}
