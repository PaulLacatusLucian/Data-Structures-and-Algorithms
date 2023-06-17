#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111
typedef int TElem;
class SetIterator;

class Set {
	//DO NOT CHANGE THIS PART
	friend class SetIterator;
    friend class newIterator;

    private:
        int minElem;
        int maxElem;
        int nrElem;
        int maxSize;
        bool *set;


    public:
        //implicit constructor
        Set();

        //adds an element to the set
		//returns true if the element was added, false otherwise (if the element was already in the set and it was not added)
        bool add(int e);

        //removes an element from the set
		//returns true if e was removed, false otherwise
        bool remove(int e);


        //checks whether an element belongs to the set or not
        bool search(int elem) const;

        //returns the number of elements;
        int size() const;

        //check whether the set is empty or not;
        bool isEmpty() const;

        //return an iterator for the set
        SetIterator iterator() const;


//        newIterator iterator() const;

        void resizeUp();

        void resizeDown();

        void printSet();

        void getInfo();
        // destructor
        ~Set();

};





