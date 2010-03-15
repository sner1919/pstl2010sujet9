#include "ErrorGenerator.hpp"

template <class T>
void ErrorGenerator<T>::generateError(IMatrix<T>& M, int nb, int iMin, int iMax, int jMin, int jMax){
	int iErreur, jErreur;
	srand(time(NULL));

	for(int i = 0; i < nb; i++){
		iErreur = rand() % (iMax - iMin) + iMin;
		jErreur = rand() % (jMax - jMin) + jMin;
		M(iErreur, jErreur) = rand() / RAND_MAX;
	}
}

template class ErrorGenerator<double>;

