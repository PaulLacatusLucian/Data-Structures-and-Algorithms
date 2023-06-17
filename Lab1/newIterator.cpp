#include "newIterator.h"
#include "Set.h"
#include "exception"


newIterator::newIterator(const Set &s, int randPoz) : set(s) {
    int i = 0;
        for (int j = 0; j < set.maxSize; j++) {
            if (set.set[j]) {
                if (i == randPoz) {
                    this->index = j;
                    return;
                } else
                    i++;
            }
        }
    }
// Best case:O(1)   Worst case:O(n)  Average case:O(n)

void newIterator::first() {
    for (int i = 0; i < set.maxSize; i++) {
        if (set.set[i]) {
            this->index = i;
            return;
        }
    }
}
// Best case:theta(1)   Worst case:theta(n)  Average case:O(n)


void newIterator::next(int amount) {
    if (amount == 0 || set.nrElem < amount)
        throw std::exception();
    int i = 0;
    while (i<amount) {
        if (valid()) {
            this->index++;
            while (index < set.maxSize && !set.set[index]) {
                this->index++;
                i++;
            }
        } else {
            throw std::exception();
        }
    }
}
// Best case:theta(1)   Worst case:theta(n)  Average case:O(n)


TElem newIterator::getCurrent() {
    if (valid()) {
        return this->index + set.minElem;
    }
    throw std::exception();
}
// Best case:theta(1)  Worst case:theta(1)  Average case:theta(1)


bool newIterator::valid() const {
    if (this->index >= 0 && this->index < set.maxSize && set.set[this->index])
        return true;
    return false;
}
// Best case:theta(1)  Worst case:theta(1)  Average case:theta(1)

void newIterator::previous(int amount) {
    if (amount == 0 || amount > set.nrElem)
        throw std::exception();
    int i = 0;
    while (i<amount) {
        if (valid()) {
            this->index--;
            while (index < set.maxSize && !set.set[index]) {
                this->index--;
                i++;
            }
        } else {
            throw std::exception();
        }
    }
}
// Best case:theta(1)   Worst case:theta(n)  Average case:O(n)





