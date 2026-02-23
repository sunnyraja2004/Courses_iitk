#include <stdio.h>
#include <stdlib.h>
 int h[100001];
void computeDepth(int values[], int i, int j, int currentDepth) {
    if (i > j) return;

    int maxVal = values[i];
    int maxIndex = i;

    for (int k = i; k <= j; k++) {
        if (values[k] > maxVal) {
            maxVal = values[k];
            maxIndex = k;
        }
    }

    h[maxVal] = currentDepth;

    computeDepth(values, i, maxIndex - 1, currentDepth + 1);
    computeDepth(values, maxIndex + 1, j, currentDepth + 1);
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int numElements;
        scanf("%d", &numElements);

        int values[numElements];
       for(int i=0;i<numElements;++i){
           h[i]=0;
       }
        for (int i = 0; i < numElements; i++) {
            scanf("%d", &values[i]);
        }

        computeDepth(values, 0, numElements - 1, 0);
        for (int i = 0; i < numElements; i++) {
            printf("%d ", h[values[i]]);
        }printf("\n");
    }

    return 0;
}