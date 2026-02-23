#include <iostream>
using namespace std;

const int MOD = 998244353;
const int MAX_K = 20;

int main() {
    int T;
    cin >> T;

    while (T--) {
        long long N;
        int K;
        cin >> N >> K;
        
         int dp[MAX_K];
        dp[0] = 1;
        for (int i = 1; i < K; i++) {
            dp[i] = 0;
            for (int j = 1; j <= i; j++) {
                dp[i] += dp[i - j];
                dp[i] %= MOD;
            }
        }

        if (N < K) {
            cout << dp[N] << endl;
            continue;
        }
        
        long long A[MAX_K][MAX_K] = {0};
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < K; j++) {
                if (i == 0) A[i][j] = 1;
                else if (j == K - 1) {
                    A[i][j] = 0;
                }
                else if (i == j + 1) A[i][j] = 1;
                else A[i][j] = 0;
            }
        }

        long long power_result[MAX_K][MAX_K] = {0};
        for (int i = 0; i < K; i++) {
            power_result[i][i] = 1;
        }

        for (long long p = N - K + 1; p > 0; p /= 2) {
            if (p % 2) {
                long long temp[MAX_K][MAX_K] = {0};
                for (int i = 0; i < K; i++) {
                    for (int j = 0; j < K; j++) {
                        long long temp_sum = 0;
                        for (int x = 0; x < K; x++) {
                            temp_sum = (temp_sum + 1LL * power_result[i][x] * A[x][j]) % MOD;
                        }
                        temp[i][j] = temp_sum % MOD;
                    }
                }
                for (int i = 0; i < K; i++) {
                    for (int j = 0; j < K; j++) {
                        power_result[i][j] = temp[i][j];
                    }
                }
            }
            
             long long temp[MAX_K][MAX_K] = {0};
            for (int i = 0; i < K; i++) {
                for (int j = 0; j < K; j++) {
                    long long temp_sum = 0;
                    for (int x = 0; x < K; x++) {
                        temp_sum = (temp_sum + 1LL * A[i][x] * A[x][j]) % MOD;
                    }
                    temp[i][j] = temp_sum % MOD;
                }
            }
            for (int i = 0; i < K; i++) {
                for (int j = 0; j < K; j++) {
                    A[i][j] = temp[i][j];
                }
            }
        }

        long long result = 0;
        for (int i = 0; i < K; i++) {
            result = (result + 1LL * dp[K - 1 - i] * power_result[0][i]) % MOD;
        }

        cout << result << endl;
    }

    return 0;
}