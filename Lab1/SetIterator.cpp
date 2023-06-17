#include "SetIterator.h"
#include "Set.h"
#include "exception"


SetIterator::SetIterator(const Set &m) : set(m) {
    for (int i = 0; i < set.maxSize; i++) {
        if (set.set[i]) {
            this->index = i;
            return;
        }
    }
}
// Best case:theta(1)   Worst case:theta(n)  Average case:theta(n)

void SetIterator::first() {
    for (int i = 0; i < set.maxSize; i++) {
        if (set.set[i]) {
            this->index = i;
            return;
        }
    }
}
// Best case:theta(1)   Worst case:theta(n)  Average case:O(n)


void SetIterator::next() {
    if (valid()) {
        this->index++;
        while (index < set.maxSize && !set.set[index]) {
            this->index++;
        }
    }
    else {
        throw std::exception();
    }
}
// Best case:theta(1)   Worst case:theta(n)  Average case:O(n)


TElem SetIterator::getCurrent() {
    if (valid()) {
        return this->index + set.minElem;
    }
    throw std::exception();
}
// Best case:theta(1)  Worst case:theta(1)  Average case:theta(1)


bool SetIterator::valid() const {
    if (this->index >= 0 && this->index < set.maxSize && set.set[this->index])
        return true;
    return false;
}
// Best case:theta(1)  Worst case:theta(1)  Average case:theta(1)



