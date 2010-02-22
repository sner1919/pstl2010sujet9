#pragma once
#include <iostream>
using namespace std;

template <class T> class IMatrix {
    public:
        virtual int getM() = 0;
        virtual int getN() = 0;
        virtual T* getData() = 0;
        virtual T& operator()(int i, int j) = 0;
        virtual string toString() = 0;
};
