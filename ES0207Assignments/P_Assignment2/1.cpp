#include <iostream>
using namespace std;

long c3(int c[], int a[], int i, int j, int mid) {
    int p = i, s = mid + 1, k = 0;
    long int c1 = 0;
    while (p <= mid && s <= j) {
        if (a[p] <= a[s]) {
            c[k++] = a[p++];
        }
        else {
            c[k++] = a[s++];
            c1 += mid - p + 1;
        }
    }
    while (p <= mid) {
        c[k++] = a[p++];
    }
    while (s <= j) {
        c[k++] = a[s++];
    }
    for (int p = i, q = 0; p <= j; ++p, ++q) {
        a[p] = c[q];
    }
    return c1;
}

long int count(int a[], int i, int j) {
    long int c1 = 0;
    if (i < j) {
        int mid = (i + j) / 2;
        c1 = count(a, i, mid) + count(a, mid + 1, j);
        int c[j - i + 1];
        c1 += c3(c, a, i, j, mid);
    }
    return c1;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n];
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        int i = 0, j = n - 1;
        long int c = count(a, i, j);
        cout << c << endl;
    }
    return 0;
}
