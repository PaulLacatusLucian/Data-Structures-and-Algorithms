#pragma once

#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator {
    friend class SortedMap;

private:
    SortedMap &map;

    SMIterator(SortedMap &mapionar);

    int index;
    int sizeArray;
    Relation relation;

    TElem *sortedMap;

    void sortArray();

public:
    void first();

    void next();

    bool valid() const;

    TElem getCurrent() const;

    void removeCurrent();

};