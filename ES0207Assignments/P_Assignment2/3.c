#include <stdio.h>
#include <stdlib.h>

struct StockNode {
    int value;
    struct StockNode* left;
    struct StockNode* right;
};

typedef struct StockNode StockNode;

StockNode* locateStock(StockNode* T, int target) {
    if (!T) return T;
    else if (T->value == target) return T;
    else if (T->value < target) return locateStock(T->right, target);
    else return locateStock(T->left, target);
}

StockNode* addStock(StockNode* T, int target) {
    if (!T) {
        T = (StockNode*)malloc(sizeof(StockNode));
        T->value = target;
        T->left = NULL;
        T->right = NULL;
    } else if (T->value < target) {
        T->right = addStock(T->right, target);
    } else {
        T->left = addStock(T->left, target);
    }
    return T;
}

StockNode* findMinimum(StockNode* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

StockNode* removeStock(StockNode* T, int target) {
    if (!T) return T;

    if (T->value < target) {
        T->right = removeStock(T->right, target);
    } else if (T->value > target) {
        T->left = removeStock(T->left, target);
    } else {
        if (!T->left) {
            StockNode* temp = T->right;
            free(T);
            return temp;
        } else if (!T->right) {
            StockNode* temp = T->left;
            free(T);
            return temp;
        }

        StockNode* temp = findMinimum(T->right);
        T->value = temp->value;
        T->right = removeStock(T->right, temp->value);
    }
    return T;
}

int main() {
    int numTransactions;
    scanf("%d", &numTransactions);
    StockNode* market = NULL;

    while (numTransactions--) {
        char action;
        int stockValue;
        scanf(" %c %d", &action, &stockValue);

        if (action == 'B') {
            market = addStock(market, stockValue);
        } else if (action == 'S') {
            market = removeStock(market, stockValue);
        } else if (action == 'R') {
            StockNode* temp = locateStock(market, stockValue);
            if (!temp)  printf("NO\n");
            else   printf("YES\n");
        }
    }

    return 0;
}
