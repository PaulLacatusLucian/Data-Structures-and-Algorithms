#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include "math.h"
#include "vector"

using namespace std;

// best-case = Theta(1)  average-case = Theta(1)  worst-case = Theta(1)
SortedMap::SortedMap(Relation r) {
    relation = r;
    sizeArray = 0;
    capacity = 17;
    elems = new TElem[capacity];
    for (int i = 0; i < capacity; i++)
        elems[i] = NULL_TPAIR;
}

// best-case = Theta(1)  average-case = Theta(sqrt(n))  worst-case = Theta(sqrt(n))
bool isPrime(int number) {
    if (number < 2) {
        return false;
    }
    for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

// best-case = Theta(1)  average-case = Theta(n)  worst-case = Theta(n)
int getNextPrime(int number) {
    while (!isPrime(number)) {
        number++;
    }
    return number;
}

// best-case = Theta(n)  average-case = Theta(n*n)  worst-case = Theta(n*n)
void SortedMap::resizeUp() {
    int newCapacity = getNextPrime(capacity * 2);
    auto *newElems = new TElem[newCapacity];
    for (int i = 0; i < newCapacity; i++) {
        newElems[i] = NULL_TPAIR;
    }

    for (int i = 0; i < capacity; i++) {
        if (elems[i].first > NULL_TVALUE) {
            int j = 0;
            int poz = rehashFunction(elems[i].first, j);
            // find empty poz
            while (newElems[poz].first != NULL_TVALUE) {
                j++;
                poz = rehashFunction(elems[i].first, j);
            }
            newElems[poz] = elems[i];
        }
    }

    delete[] elems;
    elems = newElems;
    capacity = newCapacity;
}

// best-case = Theta(1)  average-case = Theta(1)  worst-case = Theta(n)
TValue SortedMap::add(TKey k, TValue v) {
    // resize
    if (size() == capacity)
        resizeUp();

    int i = 0;
    int poz = rehashFunction(k, i);

    // find empty poz
    while (elems[poz].first != NULL_TVALUE && elems[poz].first != k && i < capacity) {
        i++;
        poz = rehashFunction(k, i);
    }

    // change value
    if (elems[poz].first == k) {
        TValue before = elems[poz].second;
        elems[poz].second = v;
        return before;
    }

    // add
    elems[poz] = TElem(k, v);
    sizeArray++;

    return NULL_TVALUE;

}

// best-case = Theta(1)  average-case = O(n)  worst-case = Theta(n)
TValue SortedMap::search(TKey k) const {
    int i = 0;
    int poz = rehashFunction(k, i);

    // find empty poz
    while (i < capacity && elems[poz].first != NULL_TVALUE && elems[poz].first != k) {
        i++;
        poz = rehashFunction(k, i);
    }

    // check
    if (elems[poz].first == k)
        return elems[poz].second;
    else return NULL_TVALUE;
}

void SortedMap::print() {
    for (int i = 0; i<sizeArray; i++) {
        cout << "Key: " << elems[i].first << " Value:" << elems[i].second << endl;
    }
}

// best-case = Theta(1)  average-case = O(n)  worst-case = Theta(n)
TValue SortedMap::remove(TKey k) {
    int i = 0;
    int poz = rehashFunction(k, i);

    // find correct poz
    while (elems[poz].first != NULL_TVALUE && elems[poz].first != k && i < capacity) {
        i++;
        poz = rehashFunction(k, i);
    }

    // check
    if (elems[poz].first == NULL_TVALUE)
        return NULL_TVALUE;

    // remove
    int before = elems[poz].second;
    elems[poz].first = NULL_TVALUE - 1;
    elems[poz].second = NULL_TVALUE;
    sizeArray--;

    return before;
}

// best-case = Theta(1)  average-case = Theta(1)  worst-case = Theta(1)
int SortedMap::size() const {
    return sizeArray;
}

// best-case = Theta(1)  average-case = Theta(1)  worst-case = Theta(1)
bool SortedMap::isEmpty() const {
    return sizeArray == 0;
}

// best-case = Theta(1), average-case = Theta(1), worst-case = Theta(1)
int SortedMap::hashFunction1(TKey key) const {
    return abs(key) % capacity;
}

// best-case = Theta(1), average-case = Theta(1), worst-case = Theta(1)
int SortedMap::hashFunction2(TKey key) const {
    return 1 + (abs(key) % (capacity - 1));
}

// best-case = Theta(1), average-case = Theta(1), worst-case = Theta(1)
int SortedMap::rehashFunction(TKey key, int i) const {
    return (hashFunction1(key) + i * hashFunction2(key)) % capacity;
}


// best-case = Theta(1)  average-case = Theta(1)  worst-case = Theta(1)
SMIterator SortedMap::iterator() {
    return SMIterator(*this);
}

// best-case = Theta(1)  average-case = Theta(1)  worst-case = Theta(1)
SortedMap::~SortedMap() {
    if (elems != nullptr) {
        delete[] elems;
    }
}