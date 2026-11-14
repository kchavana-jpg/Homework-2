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
    if (!root)
        return newNode;
    if (newNode->data.departure < root->data.departure)
        root->left = insertNode(root->left, newNode);
    else if (newNode->data.departure > root->data.departure)
        root->right = insertNode(root->right, newNode);
    return rebalance(root);
}

Node* deleteNode(Node* root, int departure) {
    if (!root)
        return nullptr;
    if (departure < root->data.departure) {
        root->left = deleteNode(root->left, departure);
    } else if (departure > root->data.departure) {
        root->right = deleteNode(root->right, departure);
    } else {
        if (!root->left || !root->right) {
            Node* child = root->left ? root->left : root->right;
            delete root;
            return child;
        }
        Node* succ = root->right;
        while (succ->left)
            succ = succ->left;
        root->data = succ->data;
        root->right = deleteNode(root->right, succ->data.departure);
    }
    return rebalance(root);
}

const Node* findNode(const Node* root, int departure) {
    const Node* curr = root;
    while (curr) {
        if (departure == curr->data.departure)
            return curr;
        curr = (departure < curr->data.departure) ? curr->left : curr->right;
    }
    return nullptr;
}

const Node* earliestNode(const Node* root, int departure) {
    const Node* best = nullptr;
    const Node* curr = root;
    while (curr) {
        if (curr->data.departure >= departure) {
            best = curr;
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return best;
}

void findRange(const Node* root, int start, int end,
               const Node* results[], int& count) {
    if (!root || start > end)
        return;
    if (root->data.departure > start)
        findRange(root->left, start, end, results, count);
    if (root->data.departure >= start && root->data.departure <= end)
        results[count++] = root;
    if (root->data.departure < end)
        findRange(root->right, start, end, results, count);
}
