#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

struct tupleP {
    int linie;
    int coloana;
    TElem info;
};

struct Node {
    tupleP info{};
    Node *left;
    Node *right;
    Node *parent;

    Node(tupleP tup);
    Node();
};

class Matrix {
private:
    int nrOfLines;
    int nrOfColumns;
    Node* root;

public:
    //constructor
    Matrix(int nrLines, int nrCols);

    int nrLines() const;

    int nrColumns() const;

    //returns the element from line i and column j (indexing starts from 0)
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    //modifies the value from line i and column j
    //returns the previous value from the position
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);

    // destructor
    ~Matrix();


    void deleteNode(Node *node);

    void destroyTree(Node *node);

    Matrix multiplyMatrices(const Matrix &matrix1);
};
