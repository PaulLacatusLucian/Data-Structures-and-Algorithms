#pragma once

#include "SortedBag.h"

class SortedBag;

class SortedBagIterator {
    friend class SortedBag;

private:
    SortedBag &bag;

    SortedBagIterator( SortedBag &b);

    int currentElement;

    //TODO - Representation

public:
    TComp getCurrent();

    bool valid();

    void changeCurrent(TComp elem);
    void next();

    void first();
};

