#include "Set.h"
#include "SetIterator.h"
#include "newIterator.h"
#include <iostream>
#include <cmath>

Set::Set() {
    maxSize = 9;
    maxElem = 0;
    minElem = 0;
    this->nrElem = 0;
    set = new bool[maxSize];
    for (int i = 0; i < maxSize; i++)
        set[i] = false;
}

void Set::resizeUp() {
    int newSize = maxSize * 2;
    bool *newSet = new bool[newSize];
    for (int i = 0; i < newSize; i++)
        newSet[i] = false;
    for (int i = 0; i < maxSize; i++)
        newSet[i] = set[i];
    delete[] set;
    set = newSet;
    maxSize = newSize;
    maxElem = minElem + newSize - 1;
}
// Best case:theta(1)  Worst case: theta(n)  Average case:  theta(n)


void Set::resizeDown() {
    int currentSize = maxElem - minElem + 1;
    int newSize = currentSize;
    while (newSize > 10 && nrElem < newSize / 2) {
        newSize /= 2;
    }
    bool *newSet = new bool[newSize];
    for (int i = 0; i < currentSize; i++)
        newSet[i] = this->set[i];
    delete[] set;
    this->set = newSet;
    this->maxSize = newSize;
    maxElem = minElem + newSize - 1;
}
// Best case: theta(1)   Worst case:theta(n)  Average case: theta(n)

bool Set::add(int elem) {
    if (isEmpty()) {
        set[0] = true;
        minElem = elem;
        maxElem = elem;
        nrElem++;
        return true;
    }
    if (search(elem)) {
        return false;
    }
    if (elem < minElem) {
        int shift = abs(elem - minElem);
        if (shift >= maxSize) {
            resizeUp();
        }
        for (int i = maxSize - 1; i >= shift; i--)
            set[i] = set[i - shift];
        set[shift] = true;
        minElem = elem;
        nrElem++;
        return true;
    } else if (elem > maxElem) {
        int index = abs(elem - minElem);
        if (index >= maxSize) {
            resizeUp();
        }
        set[index] = true;
        maxElem = elem;
        nrElem++;
        return true;
    } else {
        set[elem - minElem] = true;
        nrElem++;
        return true;
    }
}
// Best case:theta(1)   Worst case:theta(n)  Average case:tetha(1)


bool Set::remove(int elem) {
    if (!search(elem))
        return false;
    set[elem - minElem] = false;
    nrElem--;
    if (nrElem == 0) {
        minElem = 0;
        maxElem = 0;
        resizeDown();
    } else {
        if (elem == minElem) {
            int i = 1;
            while (i <= maxSize && !set[i - 1]) {
                i++;
            }
            if (i > maxSize) {
                minElem = 0;
                resizeDown();
            } else {
                if (minElem != elem) {
                    minElem = minElem + i - 1;
                }
                if (i >= 5) {
                    resizeDown();
                }
            }
        } else if (elem == maxElem) {
            int i = maxSize;
            while (i >= 1 && !set[i - 1]) {
                i--;
            }
            if (i == 0) {
                maxElem = 0;
                resizeDown();
            } else {
                maxElem = minElem + i - 1;
                if (maxSize - i >= 5) {
                    resizeDown();
                }
            }
        }
    }
    return true;
}
// Best case:theta(1)   Worst case:theta(n) Average case:theta(1)


bool Set::search(int elem) const {
    if (elem < minElem || elem > maxElem)
        return false;
    return set[elem - minElem];
}
// Best case:theta(1)   Worst case:theta(1)  Average case:theta(1)


int Set::size() const {
    int count = 0;
    for (int i = 0; i < maxSize; i++) {
        if (set[i]) {
            count++;
        }
    }
    return count;
}
// Best case:theta(1)   Worst case:theta(n)  Average case:theta(1)


bool Set::isEmpty() const {
    if (this->nrElem == 0)
        return true;
    return false;
}
// Best case:theta(1)  Worst case:theta(1)  Average case:theta(1)

Set::~Set() {
    delete[] this->set;
}
// Best case:theta(1)  Worst case:theta(1)  Average theta:O(1)

SetIterator Set::iterator() const {
    return SetIterator(*this);
}
// Best case:theta(1)  Worst case:theta(1)  Average case:theta(1)

/*
newIterator Set::iterator() const {
    return newIterator(*this, 0);
}
*/