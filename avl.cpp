// Implement only this file. See avl.h and the assignment for contracts.
#include "avl.h"

int nodeHeight(const Node* node) {
    return node ? node->height : 0;
}
void updateHeight(Node* node) {
    int leftH = nodeHeight(node->left);
    int rightH = nodeHeight(node->right);
    node->height = 1 + (leftH > rightH ? leftH : rightH);
}

int balanceFactor(const Node* node) {
    return node ? nodeHeight(node->left) - nodeHeight(node->right) : 0;
} 

Node* rotateLeft(Node* root) {
    Node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

Node* rotateRight(Node* root) {
    Node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

Node* rebalance(Node* root) {
    if (!root)
        return nullptr;
    updateHeight(root);
    int bf = balanceFactor(root);
    if (bf > 1) {
        if (balanceFactor(root->left) < 0)
            root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (bf < -1) {
        if (balanceFactor(root->right) > 0)
            root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

Node* insertNode(Node* root, Node* newNode) {
    if () ;
}

Node* deleteNode(Node* root, int departure) {
    (void)departure;
    return root; // TODO
}

const Node* findNode(const Node* root, int departure) {
    (void)root;
    (void)departure;
    return nullptr; // TODO
}

const Node* earliestNode(const Node* root, int departure) {
    (void)root;
    (void)departure;
    return nullptr; // TODO
}

void findRange(const Node* root, int start, int end,
               const Node* results[], int& count) {
    (void)root;
    (void)start;
    (void)end;
    (void)results;
    (void)count; // TODO
}
