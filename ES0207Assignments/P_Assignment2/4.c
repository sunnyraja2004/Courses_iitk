#include <stdio.h>
#include <stdlib.h>

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int elements, segments;
        scanf("%d %d", &elements, &segments);

        int *values = (int *)malloc(elements * sizeof(int));
        for (int i = 0; i < elements; i++)
            scanf("%d", &values[i]);

        int (*intervals)[2] = (int (*)[2])malloc(segments * sizeof(int[2]));
        for (int i = 0; i < segments; i++)
            scanf("%d %d", &intervals[i][0], &intervals[i][1]);

        int queries, threshold;
        scanf("%d %d", &queries, &threshold);

        int *indices = (int *)malloc(queries * sizeof(int));
        for (int i = 0; i < queries; i++)
            scanf("%d", &indices[i]);

        int left_idx = 0, right_idx = queries + 1;

        while (left_idx < right_idx) {
            int mid_idx = (left_idx + right_idx) / 2;

            int *updated_values = (int *)malloc(elements * sizeof(int));
            for (int i = 0; i < elements; i++)
                updated_values[i] = values[i];

            for (int i = 0; i < mid_idx; i++) {
                updated_values[indices[i] - 1] = abs(updated_values[indices[i] - 1]);
            }

            int *prefix_sum = (int *)malloc((elements + 1) * sizeof(int));
            prefix_sum[0] = 0;
            for (int i = 1; i < elements + 1; i++) {
                prefix_sum[i] = prefix_sum[i - 1] + updated_values[i - 1];
            }

            int count = 0;

            for (int i = 0; i < segments; i++) {
                if (prefix_sum[intervals[i][1]] - prefix_sum[intervals[i][0] - 1] > 0) {
                    count++;
                }
            }

            free(updated_values);
            free(prefix_sum);

            if (count >= threshold) {
                right_idx = mid_idx;
            } else {
                left_idx = mid_idx + 1;
            }
        }

        free(values);
        free(intervals);
        free(indices);

        if (left_idx == queries + 1)
            left_idx = -1;

        printf("%d\n", left_idx);
    }

    return 0;
}