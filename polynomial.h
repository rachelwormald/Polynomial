
#ifndef SYDE223_A1_POLYNOMIAL_H
#define SYDE223_A1_POLYNOMIAL_H
#include "doubly-linked-list.h"

class Polynomial {

private:

    DoublyLinkedList* PolynomialList;


public:

    Polynomial(int A[], int size);

    ~Polynomial();

    void print() const;


// will take as input a second polynomial *rhs, apply the operation, on *this and *rhs, and will return the result as a new Polynomial instance
// won't change *this or *rhs
    Polynomial* add(Polynomial* rhs);
    Polynomial* sub(Polynomial* rhs);
    Polynomial* mul(Polynomial* rhs);

};


#endif
