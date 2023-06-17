#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
    this->head = NULL;
    this->tail = NULL;
    this->length = 0;
}
// Complexitat  Theta(1) Theta(1) Theta(1)


void MultiMap::add(TKey c, TValue v) {
    // create new DllNode
    dllNode *newNode = new dllNode;
    newNode->elem = make_pair(c, v);
    newNode->prev = newNode->next = NULL;

    // if empty set head, tail
    if (head == NULL) {
        head = tail = newNode;
        length++;
    } else {
        // go through the list
        dllNode *current = head;
        while (current != NULL && current->elem.first < c) {
            current = current->next;
        }
        // change head
        if (current == head) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            // change tail
        } else if (current == NULL) {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        } else {
            // insert node
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
        }
        length++;
    }
}
// Complexitat  Theta(1) O(n) Theta(n)


bool MultiMap::remove(TKey c, TValue v) {
    // search
    dllNode *current = head;
    while (current != NULL && current->elem != make_pair(c, v)) {
        current = current->next;
    }

    // not found
    if (current == NULL) {
        return false;
    }

    // if head
    if (current == head) {
        head = current->next;
        if (head != NULL) {
            head->prev = NULL;
        } else {
            tail = NULL;
        }
    } else if (current == tail) {
        tail = current->prev;
        tail->next = NULL;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    // delete node
    delete current;
    length--;

    // if found
    return true;
}
// Complexitat  Theta(1) O(n) Theta(n)


vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> values;

    // go through the list
    dllNode *current = head;
    while (current != NULL) {
        if (current->elem.first == c) {
            values.push_back(current->elem.second);
        }
        current = current->next;
    }

    return values;
}
// Complexitat  Theta(1) O(n) Theta(n)


int MultiMap::size() const {
    return this->length;
}
// Complexitat  Theta(1) Theta(1) Theta(1)



bool MultiMap::isEmpty() const {
    if (this->length == 0)
        return true;
    return false;
}
// Complexitat  Theta(1) Theta(1) Theta(1)

MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}
// Complexitat  Theta(1) Theta(1) Theta(1)


MultiMap::~MultiMap() {
    dllNode *current = head;
    while (current != NULL) {
        dllNode *temp = current;
        current = current->next;
        delete temp;
    }
}
// Complexitat  Theta(1) O(n) Theta(n)

