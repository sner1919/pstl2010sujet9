#include "ErrorGenerator.hpp"
#include <stdlib.h>
#include <time.h>

template <class T>
void ErrorGenerator::generateError(IMatrix<T> M, int nb, int iMin, int iMax, int jMin, int jMax){
	for(int i = 0; i < nb; i++){
		srand ( time(NULL) );
		iErreur = rand() % (iMax - iMin) + iMin;
		jErreur = rand() % (jMax - jMin) + jMin;
		M(iErreur,jErreur) = rand()/(T)RAND_MAX;
	}
}

template class ErrorGenerator<double>;

