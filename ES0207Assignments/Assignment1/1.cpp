#include <iostream>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        long long A[N];
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }

        long long max_sum[N];
        max_sum[N - 1] = A[N - 1];
        
        for (int i = N - 2; i >= 0; --i) {
            max_sum[i] = max(A[i], A[i] + max_sum[i + 1]);
        }

        for (int i = 0; i < N; ++i) {
            cout << max_sum[i] << " ";
        }

        cout << endl;
    }

    return 0;
}
