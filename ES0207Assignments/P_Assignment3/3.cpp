#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

const int maxN = 2e5 + 1;
const int logN = 20;

int N, M, a, b, sub[maxN], parent[maxN][logN];
int timer, in[maxN], out[maxN];
vector<int> children[maxN];

bool isAncestor(int u, int v) {
    return in[u] <= in[v] && out[u] >= out[v];
}

int findLowestCommonAncestor(int u, int v) {
    if (in[u] <= in[v] && out[u] >= out[v]) return u;
    if (in[v] <= in[u] && out[v] >= out[u]) return v;
    for (int i = logN - 1; i >= 0; i--) {
        if (parent[u][i] != -1 && !isAncestor(parent[u][i], v)) {
            u = parent[u][i];
        }
    }
    return parent[u][0];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
     cin >> N >> M;
    vector<int> A(N - 1), B(N - 1);
    for (int i = 0; i < N - 1; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N - 1; i++) {
        cin >> B[i];
    }
    for (int i = 0; i < N - 1; i++) {
        children[A[i]].push_back(B[i]);
        children[B[i]].push_back(A[i]);
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < logN; j++) {
            parent[i][j] = -1;
        }
    }

    // Depth-First Search 1 to calculate in and out times.
     function<void(int, int)> dfs1 = [&](int u, int par) {
        in[u] = ++timer;
        parent[u][0] = par;
        for (int i = 1; i < logN; i++) {
            if (parent[u][i - 1] != -1) {
                parent[u][i] = parent[parent[u][i - 1]][i - 1];
            }
        }
        for (int v : children[u]) {
            if (v != par) {
                dfs1(v, u);
            }
        }
        out[u] = ++timer;
    };

    // Depth-First Search 2 to calculate sub-array.
    function<void(int)> dfs2 = [&](int u) {
        for (int v : children[u]) {
            if (v != parent[u][0]) {
                dfs2(v);
                 sub[u] += sub[v];
            }
        }
    };

    dfs1(1, 1);

    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        int l = findLowestCommonAncestor(a, b);
        sub[a]++;
        sub[b]++;
        sub[l]--;
        if (l != 1) {
            sub[parent[l][0]]--;
        }
    }
    dfs2(1);

    for (int i = 1; i <= N; i++) {
        cout << sub[i] << (i == N ? '\n' : ' ');
    }
    
    return 0;
}
