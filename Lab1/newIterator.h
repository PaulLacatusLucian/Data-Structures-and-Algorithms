#pragma once
#include "Set.h"

class newIterator
{
    //DO NOT CHANGE THIS PART
    friend class Set;
private:
    //DO NOT CHANGE THIS PART
    const Set& set;

    int index;

public:
public:
    newIterator(const Set& m, int index=0);
    void first();
    void next(int amount);
    TElem getCurrent();
    void previous(int amount);
    bool valid() const;
};


