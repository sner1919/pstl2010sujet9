#include "interfaces/IErrorGenerator.hpp"
#include <stdexcept>

template <class T> class ErrorGenerator : public IErrorGenerator<T> {
public:
	//Implémentation de IErrorGenerator
	void generateError(IMatrix<T> M, int nb, int iMin, int iMax, int jMin, int jMax);

};