#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
    friend class MultiMap;

private:
    MultiMap& col;
    dllNode* it;

    MultiMapIterator(const MultiMap& c);

public:
    TElem getCurrent()const;
    bool valid() const;
    void next();
    void first();
    bool deleteCurrent();
};

