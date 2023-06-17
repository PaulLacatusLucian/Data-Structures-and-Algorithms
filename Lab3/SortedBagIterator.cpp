#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <iostream>

using namespace std;

SortedBagIterator::SortedBagIterator(SortedBag &b) : bag(b) {
    //TODO - Implementation
    /** Complexity: Theta(1)**/
    currentElement = bag.head;
}

TComp SortedBagIterator::getCurrent() {
    //TODO - Implementation
    /** Complexity: Theta(1)**/
    if (!valid())
        throw invalid_argument("");
    return bag.nodes[currentElement].info;

}

void SortedBagIterator::changeCurrent(TComp elem) {
    //pre: currentElement is an iterator for the SortedBag
    //post: the element that is pointed by the currentElement will be changed to the

    int currentValue = bag.nodes[currentElement].info;
    int prevValue = bag.nodes[bag.nodes[currentElement].previous].info;
    int nextValue = bag.nodes[bag.nodes[currentElement].next].info;

    if (!bag.relation(currentValue, elem) && !bag.relation(elem, currentValue)) {
        bag.nodes[currentElement].info = elem;
        return;
    }

    if (currentElement == bag.head && bag.relation(elem, nextValue)) {
        bag.nodes[currentElement].info = elem;
        return;
    }

    if (currentElement == bag.tail && bag.relation(prevValue, elem)) {
        bag.nodes[currentElement].info = elem;
        return;
    }
    int current = bag.head;
    while(current != -1) {
         prevValue = bag.nodes[bag.nodes[currentElement].previous].info;
         nextValue = bag.nodes[bag.nodes[currentElement].next].info;
        if (bag.relation(prevValue, elem) && bag.relation(elem,nextValue)) {
            bag.nodes[currentElement].info = elem;
            return;
        }
        current = bag.nodes[current].next;
    }
}

bool SortedBagIterator::valid() {
    //TODO - Implementation
    /** Complexity: Theta(1)**/
    if (currentElement != -1)
        return true;
    return false;
}

void SortedBagIterator::next() {
    //TODO - Implementation
    /** Complexity: Theta(1)**/
    if (valid())
        currentElement = bag.nodes[currentElement].next;
    else {
        throw invalid_argument("");
    }
}

void SortedBagIterator::first() {
    //TODO - Implementation
    /** Complexity: Theta(1)**/
    if (bag.head != -1)
        currentElement = bag.head;
    else {
        throw invalid_argument("");
    }
}

