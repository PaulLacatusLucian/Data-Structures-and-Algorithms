#include "MultiMapIterator.h"
#include "MultiMap.h"
#include "cassert"


MultiMapIterator::MultiMapIterator(const MultiMap &c) : col(const_cast<MultiMap &>(c)) {
    this->it = col.head;
}
// Complexitat  Theta(1) Theta(1) Theta(1)


TElem MultiMapIterator::getCurrent() const {
    if (it == nullptr)
        throw exception();
    return it->elem;
}
// Complexitat  Theta(1) Theta(1) Theta(1)


bool MultiMapIterator::valid() const {
    return it != nullptr;
}
// Complexitat  Theta(1) Theta(1) Theta(1)


void MultiMapIterator::next() {
    if (it == nullptr)
        throw exception();
    it = it->next;
}
// Complexitat  Theta(1) Theta(1) Theta(1)


void MultiMapIterator::first() {
    it = col.head;
}
// Complexitat  Theta(1) Theta(1) Theta(1)

bool MultiMapIterator::deleteCurrent() {
    if (!valid())
        return false;
    dllNode *current = it;

    // if head
    if (current == col.head) {
        col.head = current->next;
        if (col.head != NULL) {
            col.head->prev = NULL;
        } else {
            col.tail = NULL;
        }
        // if tail
    } else if (current == col.tail) {
        col.tail = current->prev;
        col.tail->next = NULL;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    // delete node
    delete current;
    col.length--;
    it = it->next;

    // if found
    return true;
}
// Complexitat  Theta(1) O(n) Theta(n)



