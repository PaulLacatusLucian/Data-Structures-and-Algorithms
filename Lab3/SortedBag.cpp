#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

using namespace std;

SortedBag::SortedBag(Relation r) {

    /* Complexity: Theta(n) */

    relation = r;
    capacity = 10;
    nodes = new dllaNode[capacity];
    sizeArray = 0;
    head = -1;
    tail = -1;
    firstEmpty = 0;
    for (int i = 0; i < capacity; i++) {
        nodes[i].previous = -1;
        nodes[i].next = i + 1;
    }
    nodes[capacity - 1].next = -1;
}

int SortedBag::allocate() {

    /* Complexity: Theta(1) */

    int position = firstEmpty;
    // Check if there is an empty node
    if (position != -1) {
        firstEmpty = nodes[firstEmpty].next;
        // Check if there is another empty node
        if (firstEmpty != -1)
            nodes[firstEmpty].previous = -1;

        // allocate the current position
        nodes[position].next = -1;
        nodes[position].previous = -1;
    }
    return position;
}

void SortedBag::free(int position) {

    /* Complexity: Theta(1) */

    nodes[position].next = firstEmpty;
    nodes[position].previous = -1;
    if (firstEmpty != -1)
        nodes[firstEmpty].previous = position;
    firstEmpty = position;
}

void SortedBag::resizeUp() {

    /* Complexity: Theta(n) */

    // duplicate the capacity
    int newCapacity = capacity * 2;
    dllaNode *newNodes = new dllaNode[newCapacity];
    // copy all elements
    for (int i = 0; i < capacity; i++) {
        newNodes[i].info = nodes[i].info;
        newNodes[i].next = nodes[i].next;
        newNodes[i].previous = nodes[i].previous;
    }
    // initialize the rest
    for (int i = capacity; i < newCapacity; i++) {
        newNodes[i].previous = -1;
        newNodes[i].next = i + 1;
    }
    newNodes[capacity].previous = -1;
    newNodes[newCapacity - 1].next = -1;
    firstEmpty = capacity;
    newNodes[firstEmpty].previous = -1;
    // delete the old ones  and make the change
    delete[] nodes;
    nodes = newNodes;
    capacity = newCapacity;
}

void SortedBag::resizeDown() {

    /* Complexity: Theta(n) */

    int newCapacity = capacity / 2;
    dllaNode *newNodes = new dllaNode[newCapacity];
    int current = head;
    int newNodesIndex = 0;
    while (current != -1) {
        newNodes[newNodesIndex] = nodes[current];
        newNodes[newNodesIndex].previous = newNodesIndex - 1;
        newNodes[newNodesIndex].next = newNodesIndex + 1;
        newNodesIndex++;
        current = nodes[current].next;
    }
    head = 0;
    tail = sizeArray - 1;
    firstEmpty = sizeArray;
    newNodes[0].previous = -1;
    newNodes[sizeArray - 1].next = -1;
    delete[] nodes;
    nodes = newNodes;
    capacity = newCapacity;
}

void SortedBag::add(TComp e) {

    /* Complexity: Theta(n) */

    // Check if the array is full
    if (sizeArray == capacity || firstEmpty == -1)
        resizeUp();

    int current = head; // Start from the head of the SortedBa
    int prev = -1;
    int newElement = allocate();
    nodes[newElement].info = e;
    // Find the right place
    while (current != -1 && relation(nodes[current].info, e)) {
        prev = current;
        current = nodes[current].next;
    }
    nodes[newElement].next = current; // Make the links to the next elem
    nodes[newElement].previous = prev;  // Make the links to the previous elem
    // Make the previous elem point to the new one or change the head if needed
    if (prev != -1) {
        nodes[prev].next = newElement;
    } else {
        head = newElement;
    }
    //  Make the next elem point to the new one or change the tail if needed
    if (current != -1) {
        nodes[current].previous = newElement;
    } else {
        tail = newElement;
    }
    // increase size
    sizeArray++;
}


bool SortedBag::remove(TComp e) {

    /** Complexity:
                    * Best-Case: Theta(1)
                    * Average-Case: Theta(n)
                    * Worst-Case: Theta(n) **/

    if (isEmpty())
        return false;
    if (sizeArray == capacity / 4)
        resizeDown();
    int current = head;
    while (current != -1) {
        if (nodes[current].info == e) {
            break;
        }
        current = nodes[current].next;
    }
    if (current == -1) {
        return false; // element not found
    }
    int nextNode = nodes[current].next;
    int prevNode = nodes[current].previous;
    if (prevNode == -1) { // if removing the head
        head = nextNode;
    } else {
        nodes[prevNode].next = nextNode;
    }
    if (nextNode == -1) { // if removing the tail
        tail = prevNode;
    } else {
        nodes[nextNode].previous = prevNode;
    }
    free(current);
    sizeArray--;
    return true;
}


bool SortedBag::search(TComp elem) const {

    /** Complexity:
                  * Best-Case: Theta(1)
                  * Average-Case: Theta(n)
                  * Worst-Case: Theta(n) **/

    if (isEmpty())
        return false;
    int current = head;
    while (current != -1) {
        if (nodes[current].info == elem) {
            return true;
        }
        current = nodes[current].next;
    }
    return false;
}


int SortedBag::nrOccurrences(TComp elem) const {

    /* Complexity: Theta(n) */

    int nrOccurrences = 0;
    int current = head;
    while (current != -1) {
        if (nodes[current].info == elem) {
            nrOccurrences++;
        }
        current = nodes[current].next;
    }
    return nrOccurrences;
}


int SortedBag::size() const {

    /* Complexity: Theta(1) */

    return sizeArray;
}

bool SortedBag::isEmpty() const {

    /* Complexity: Theta(1) */

    if (sizeArray == 0)
        return true;
    return false;
}


SortedBagIterator SortedBag::iterator()  {

    /** Complexity: Theta(1) **/

    return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {

    /* Complexity: Theta(1) */

    delete[] nodes;
}