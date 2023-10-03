#include "Set.h"
#include <cassert>

// define constructor
Set :: Set(size_t n) {
    assert(n >= 1);
    this -> n = n; // set the maximum number of elements
    // use ceiling division to determine the number of integers needed to store the elements
    if (n % (this -> INT_BITS) == 0) {
        this -> a = n / (this -> INT_BITS);
    } else {
        this -> a = (n / (this -> INT_BITS)) + 1;
    }
    this -> bits = new unsigned int[this -> a];
    // initialize an empty array
    for (size_t i = 0; i < (this -> a); i++) {
        (this -> bits)[i] = 0; 
    }
}

// define destructor
Set :: ~Set() {
    delete []bits;
}

// define copy constructor
Set :: Set(const Set &s) {
    this -> n = s.n;
    this -> a = s.a;
    // deep copy
    this -> bits = new unsigned int[this -> a];
    for (size_t i = 0; i < (this -> a); i++) {
        (this -> bits)[i] = (s.bits)[i]; 
    }
}

// define assignment operator
Set &Set :: operator = (const Set &s) {
    this -> n = s.n;
    this -> a = s.a;
    // deep copy
    for (size_t i = 0; i < (this -> a); i++) {
        (this -> bits)[i] = (s.bits)[i]; 
    }
    return *this;
}

// define empty set method
void Set :: clear() {
    delete []bits;
    this -> n = 0;
    this -> a = 0;
}

// define complement method
void Set :: complement() {
    for (size_t i = 0; i < (this -> a); i++) {
        (this -> bits)[i] = ~((this -> bits)[i]);
    }
}

// define has method
bool Set :: has(size_t x) const {
    size_t i = x / (this -> INT_BITS);
    if ((1 << x) & ((this -> bits)[i])) {
        return true;
    } else {
        return false;
    }
}

// define add element x method
void Set :: add(size_t x) {
    unsigned int flipper = 1 << x;
    size_t i = x / (this -> INT_BITS);
    unsigned int y = (this -> bits)[i];
    (this -> bits)[i] = y | flipper;
}

// define remove element x method
void Set :: remove(size_t x) {
    unsigned int flipper = 1 << x;
    size_t i = x / (this -> INT_BITS);
    if (has(x)) {
        unsigned int y = (this -> bits)[i];
        (this -> bits)[i] = y ^ flipper;
    }
}

// define add elements of set s to set method
void Set :: add(const Set &s) {
    assert(s.n == (this -> n) && s.a == (this -> a));
    for (size_t i = 0; i < (this -> a); i++) {
        (this -> bits)[i] = ((this -> bits)[i]) | ((s.bits)[i]);
    }
}

// define remove all elements in s method
void Set :: remove(const Set &s) {
    assert(s.n == (this -> n) && s.a == (this -> a));
    for (size_t i = 0; i < (this -> a); i++) {
        unsigned int y = (this -> bits)[i];
        (this -> bits)[i] = (((this -> bits)[i]) ^ ((s.bits)[i])) & y;
    }
}

// define print method
void Set :: print(std::ostream &os) const {
    os << "[ ";
    for (size_t x = 0; x < (this -> n); x++) {
        if (has(x)) {
            os << x << " ";
        }
    }
    os << "]";
}