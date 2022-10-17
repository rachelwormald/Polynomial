#include "polynomial.h"
#include<iostream>

Polynomial::Polynomial(int A[], int size ){

    // creating new doubly linked list to store polynomials in
    PolynomialList = new DoublyLinkedList();

    // iterating through each element in A and inserting it into PolynomialList
    for (int i = 0; i < size; i++)
    {
        PolynomialList->insert_back(A[i]);
    }
}
//destructor for new allocated memory
Polynomial::~Polynomial()
{
    delete PolynomialList;

}
// print last index first and then move towards the front of the list, printing the first index last
void Polynomial::print() const
{
    // counter
    int j = 0;

    for (int i = PolynomialList->size()-1; i >=0; i--)
    {
        // increasing counter when the coefficient is 0, and continuing so the function won't print 0
        if (PolynomialList->select(i) == 0)
        {
            j++;
            continue;
        }
        // if j == the last index minus i (the index being iterated through), that means every value so far has been 0 and the output doesn't need a plus sign in front
        // so when the opposite is true, we can include a plus sign
        if (j != PolynomialList->size()-1-i)
        {
            std::cout << " + ";
        }

        // for negative values to be put in brackets
        if (PolynomialList->select(i) < 0 )
        {
            std::cout << "(" << PolynomialList->select(i) << ")" << "x^" << i;
            continue;
        }

        // printing the coefficients with their index
        std::cout << PolynomialList->select(i) << "x^" << i;
    }
// if j == size, then it will have increased for every iteration, meaning every coefficient is 0, so the print function will output 0
    if (j == PolynomialList->size())
    {
        std::cout << "empty";
    }

    std::cout << "\n";

}

// will take as input a second polynomial *rhs, apply the operation, on *this and *rhs, and will return the result as a new Polynomial instance
// won't change *this or *rhs
// *this + *rhs
// when the index of both polynomials are the same, add the values at that index and put the result into the same index value in a new polynomial instance
// if size of rhs is bigger than PolynomialList,
Polynomial* Polynomial::add(Polynomial* rhs)
{
    // creating an array to initialize result polynomial with
    int a [] = {};
    // creating a result polynomial using the array just created, and initial size 0
    Polynomial* result = new Polynomial(a,0);

    // for loop to add polynomials will end when i is equal to or passes the size of either polynomial, meaning there aren't values to add from both polynomials
    for (int i = 0; i <= PolynomialList->size() || i <= rhs->PolynomialList->size(); i++)
    {
        // if the size of the PolynomialList is less than i, that means rhs is bigger than PolynomialList,
        // and the values from rhs should just be inserted into the result since there is nothing to add
        if (PolynomialList->size() < i)
        {
            result->PolynomialList->insert_back(rhs->PolynomialList->select(i));
            continue;
        }
        // opposite case - when PolynomialList is bigger than rhs
        if (i > rhs->PolynomialList->size())
        {
            result->PolynomialList->insert_back(PolynomialList->select(i));
            continue;
        }

        // when the indices are equal
        else
            result->PolynomialList->insert_back(PolynomialList->select(i) + rhs->PolynomialList->select(i));

    }
    return result;
}

// *this - *rhs
// essentially the same logic as add except the coefficients are being subtracted
// multiply rhs by -1 if it's the bigger polynomial since the subtraction sign will still be there
Polynomial* Polynomial::sub(Polynomial* rhs)
{
    int a [] = {};
    Polynomial* result = new Polynomial(a,0);

    for (int i = 0; i <= PolynomialList->size() || i <= rhs->PolynomialList->size(); i++)
    {
        if (PolynomialList->size() < i)
        {
            result->PolynomialList->insert_back(-1 * rhs->PolynomialList->select(i));
            continue;
        }

        if (rhs->PolynomialList->size() < i)
        {
            result->PolynomialList->insert_back(PolynomialList->select(i));
            continue;
        }

        else
            result->PolynomialList->insert_back(PolynomialList->select(i) - rhs->PolynomialList->select(i));
    }
    return result;
}

// *this * *rhs
// multiply the value at index 0 of the PolynomialList by every value in rhs
// repeat for next index of Polynomial List
// when those values are multiplied, their indices need to be added
Polynomial* Polynomial::mul(Polynomial* rhs)
{
    // creating an array to initialize result polynomial with
    int a [] = {};
    Polynomial* result = new Polynomial(a,0);

// have to use for loop to add zeros into the result since the results of the multiplication will be replacing the values
    for (int i = 0; i < PolynomialList->size() + rhs->PolynomialList->size() -1; i++)
    {
        result->PolynomialList->insert_front(0);
    }
// nested for loops to index through the polynomials being multiplied since their indices need to be added and then the result is inserted at that index
    for (int i = 0; i < PolynomialList->size(); i++)
    {

        for (int j = 0; j < rhs->PolynomialList->size(); j++ )
        {
            // if 2 results have the same index they need to be added together
            if (result->PolynomialList->select(i+j) != 0)
            {
                result->PolynomialList->replace(i+j, result->PolynomialList->select(i+j) + PolynomialList->select(i) * rhs->PolynomialList->select(j));
            }
            else
            result->PolynomialList->replace(i + j, PolynomialList->select(i) * rhs->PolynomialList->select(j));
        }
    }
    return result;

}





