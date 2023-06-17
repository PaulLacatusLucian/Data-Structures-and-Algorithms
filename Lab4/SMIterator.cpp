#include "SMIterator.h"
#include "SortedMap.h"

// best-case = Theta(1)  average-case = Theta(1)  worst-case = Theta(1)
SMIterator::SMIterator(SortedMap &m) : map(m) {
    index = 0;
    sizeArray = m.size();
    relation = m.relation;
    sortedMap = new TElem[sizeArray];
    sortArray();
}

// best-case = Theta(n*n)  average-case = Theta(n*n)  worst-case = Theta(n*n)
void SMIterator::sortArray() {
    for (int i = 0; i < sizeArray - 1; i++) {
        for (int j = i + 1; j < sizeArray; j++) {
            if (relation(sortedMap[j].first, sortedMap[i].first)) {
                std::swap(sortedMap[i], sortedMap[j]);
            }
        }
    }
}

// best-case = Theta(1)  average-case = Theta(1)  worst-case = Theta(1)
void SMIterator::first() {
    index = 0;
}

// best-case = Theta(1)  average-case = Theta(1)  worst-case = Theta(1)
void SMIterator::next() {
    if (!valid())
        throw std::exception();
    index++;
}

// best-case = Theta(1)  average-case = Theta(1)  worst-case = Theta(1)
bool SMIterator::valid() const {
    return index < sizeArray;
}

// best-case = Theta(1)  average-case = Theta(1)  worst-case = Theta(1)
TElem SMIterator::getCurrent() const {
    if (!valid()) {
        throw std::exception();
    }
    return sortedMap[index];
}

// best-case = Theta(1)  average-case = Theta(n)  worst-case = Theta(n)
void SMIterator::removeCurrent() {
    // check if valid
    if (valid()) {
        // delete the element in the map
        map.elems[index].first = NULL_TVALUE;
        map.elems[index].second = NULL_TVALUE;
        map.sizeArray--;

        // delete the element in the sortedMap
        sortedMap[index].first = NULL_TVALUE;
        sortedMap[index].second = NULL_TVALUE;

        // change the positions
        for (int poz = index + 1; poz < sizeArray - 1; poz++)
            sortedMap[poz-1] = sortedMap[poz];

        sizeArray--;
    }
    else
        throw std::exception();
}

