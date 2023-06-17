#include "Matrix.h"
#include <exception>
#include <iostream>

using namespace std;

Node::Node(tupleP tup) {
    info = tup;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}
//// Best-case: Theta(1) Average-case:Theta(1) Worst-case: Theta(1)


Matrix::Matrix(int nrLines, int nrCols) {
    this->nrOfLines = nrLines;
    this->nrOfColumns = nrCols;
    this->root = nullptr;
}
//// Best-case: Theta(1) Average-case:Theta(1) Worst-case: Theta(1)


int Matrix::nrLines() const {
    return nrOfLines;
}
//// Best-case: Theta(1) Average-case:Theta(1) Worst-case: Theta(1)


int Matrix::nrColumns() const {
    return nrOfColumns;
}
//// Best-case: Theta(1) Average-case:Theta(1) Worst-case: Theta(1)


TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= nrOfLines || j < 0 || j >= nrOfColumns)
        throw std::out_of_range("The line or column index is out of range!");

    Node *current = root;
    while (current != nullptr) {
        // if current > target go left
        if (i < current->info.linie || (i == current->info.linie && j < current->info.coloana))
            current = current->left;
            // if current < target go right
        else if (i > current->info.linie || (i == current->info.linie && j > current->info.coloana))
            current = current->right;
            // if current = target
        else
            return current->info.info;
    }
    return NULL_TELEM;
}
//// Best-case: Theta(1) Average-case:O(n) Worst-case: Theta(n)


TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= nrOfLines || j < 0 || j >= nrOfColumns)
        throw out_of_range("The line or column index is out of range!");

    Node *current = root;
    while (current != nullptr) {
        // if current > target, go left
        if (i < current->info.linie || (i == current->info.linie && j < current->info.coloana))
            current = current->left;
            // if current < target, go right
        else if (i > current->info.linie || (i == current->info.linie && j > current->info.coloana))
            current = current->right;
        else {
            // if current = target
            if (e == 0) {
                // case 1: delete the node
                TElem previous = current->info.info;
                deleteNode(current);
                return previous;
            }
            TElem previous = current->info.info;
            // case 2: update the current element
            current->info.info = e;
            return previous;
        }
    }

    // case 3: if the element doesn't exist
    tupleP tup{};
    tup.linie = i;
    tup.coloana = j;
    tup.info = e;
    Node *newNode = new Node(tup);

    // find parent
    Node *parent = nullptr;
    current = root;
    while (current != nullptr) {
        parent = current;
        if (i < current->info.linie || (i == current->info.linie && j < current->info.coloana))
            current = current->left;
        else
            current = current->right;
    }

    if (parent == nullptr) {
        // if empty
        root = newNode;
    } else if (i < parent->info.linie || (i == parent->info.linie && j < parent->info.coloana)) {
        // insert as left child
        parent->left = newNode;
        newNode->parent = parent;
    } else {
        // insert as the right child
        parent->right = newNode;
        newNode->parent = parent;
    }

    return NULL_TELEM;
}
//// Best-case: Theta(1) Average-case:O(n) Worst-case: Theta(n)


void Matrix::deleteNode(Node *node) {
    // case 1: no children
    if (node->left == nullptr && node->right == nullptr) {
        if (node->parent == nullptr) {
            root = nullptr;
        } else if (node->parent->left == node) {
            // left child of its parent
            node->parent->left = nullptr;
        } else {
            // right child of its parent
            node->parent->right = nullptr;
        }
        delete node;
    }
        // case 2: one child
    else if (node->left == nullptr) {
        if (node->parent == nullptr) {
            root = node->right;
            root->parent = nullptr;
        } else if (node->parent->left == node) {
            // left child of its parent
            node->parent->left = node->right;
            node->right->parent = node->parent;
        } else {
            // right child of its parent
            node->parent->right = node->right;
            node->right->parent = node->parent;
        }
        delete node;
    } else if (node->right == nullptr) {
        if (node->parent == nullptr) {
            root = node->left;
            root->parent = nullptr;
        } else if (node->parent->left == node) {
            // left child of its parent
            node->parent->left = node->left;
            node->left->parent = node->parent;
        } else {
            // right child of its parent
            node->parent->right = node->left;
            node->left->parent = node->parent;
        }
        delete node;
    }
        // case 3: two children
    else {
        //find successor (the smallest node in the right subtree)
        Node *successor = node->right;
        while (successor->left != nullptr)
            successor = successor->left;

        // node = successor
        node->info = successor->info;
        deleteNode(successor);
    }
}
//// Best-case: Theta(1) Average-case:O(n) Worst-case: Theta(n)


void Matrix::destroyTree(Node *root) {
    if (root == nullptr)
        return;

    destroyTree(root->left);
    destroyTree(root->right);

    delete root;
}
//// Best-case: Theta(n) Average-case:Theta(n) Worst-case: Theta(n)


Matrix::~Matrix() {
    destroyTree(root);
}
//// Best-case: Theta(1) Average-case:Theta(1) Worst-case: Theta(1)


Matrix Matrix::multiplyMatrices(const Matrix& matrix1) {
    if (matrix1.nrOfColumns != this->nrOfLines) {
        throw invalid_argument("Matrix dimension do not match!");
    }

    int resultNrLines = matrix1.nrOfLines;
    int resultNrColumns = this->nrOfColumns;
    Matrix resultMatrix(resultNrLines, resultNrColumns);

    for (int i = 0; i < resultNrLines; i++) {
        for (int j = 0; j < resultNrColumns; j++) {
            TElem sum = 0;
            for (int k = 0; k < matrix1.nrColumns(); k++) {
                sum += matrix1.element(i, k) * this->element(k, j);
            }
            resultMatrix.modify(i, j, sum);
        }
    }
    return resultMatrix;
}
//// Best-case: Theta(1) Average-case:Theta(n^3) Worst-case: Theta(n^3)