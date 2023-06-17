#include <assert.h>
#include "Matrix.h"
#include <iostream>

using namespace std;

void testAll() {
    Matrix m(4, 4);
    assert(m.nrLines() == 4);
    assert(m.nrColumns() == 4);
    m.modify(1, 1, 5);
    assert(m.element(1, 1) == 5);
    m.modify(1, 1, 6);
    assert(m.element(1, 2) == NULL_TELEM);

    Matrix m1(4,4);
    Matrix m2(4,4);
    m1.modify(1,1,1);
    m1.modify(1,2,1);
    m1.modify(1,3,1);
    m2.modify(1,1,1);
    m2.modify(2,1,1);
    m2.modify(3,1,1);
    auto aux = m2.multiplyMatrices(m1);
    assert (aux.element(1,1) == 3);

    Matrix m3(4,4);
    Matrix m4(4,4);
    m3.modify(1,1,2);
    m3.modify(1,2,2);
    m3.modify(1,3,2);
    m4.modify(1,1,2);
    m4.modify(2,1,2);
    m4.modify(3,1,2);
    auto aux1 = m4.multiplyMatrices(m3);
    assert (aux1.element(1,1) == 12);
}