#pragma once
#include "IMatrix.hpp"
#include <sstream>
#include <stdexcept>

template <class T> class Matrix : public virtual IMatrix<T> {
        T* data;
        int m, n;
        bool dataAllocation;
        
    public:
        Matrix(int m, int n) {
            this->data = new T[m * n];
            this->m = m;
            this->n = n;
            dataAllocation = true;
        }

        Matrix(T* data, int m, int n) {
            this->data = data;
            this->m = m;
            this->n = n;
            dataAllocation = false;
        }
        
        ~Matrix() {
        	if(dataAllocation) delete [] data;
        }
        
        int getM() {
            return m;
        }
        
        int getN() {
            return n;
        }
        
        T* getData() {
            return data;
        }

        T& operator()(int i, int j) {
            return data[(i - 1) * n + (j - 1)];
        }
        
        string toString() {
            ostringstream oss;
            
            oss << "[" << endl;
            for(int i = 1; i <= getM(); i++){
                for(int j = 1; j <= getN(); j++){
                    oss << (*this)(i, j) << " ";
                }
                oss << endl;
            }
            oss << "]" << endl;
            
            return oss.str();
        }
};
