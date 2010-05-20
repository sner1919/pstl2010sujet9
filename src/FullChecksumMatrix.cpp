#include "FullChecksumMatrix.hpp"
#include <vector>

template <class T>
FullChecksumMatrix<T>::FullChecksumMatrix(IMatrix<T>& M) :
Matrix<T>(M.getData(), M.getM() + 1, M.getN() + 1),
ColumnChecksumMatrix<T>(*(new RowChecksumMatrix<T>(M))),
RowChecksumMatrix<T>(dynamic_cast<RowChecksumMatrix<T>&>(this->getColumnMatrix())) {}

template <class T>
FullChecksumMatrix<T>::~FullChecksumMatrix() {
	delete dynamic_cast<RowChecksumMatrix<T>*>(&this->getColumnMatrix());
}

template <class T>
PSTL_TYPE_UNION FullChecksumMatrix<T>::operator()(int i, int j) const {
	return ColumnChecksumMatrix<T>::operator()(i, j);
}

template <class T>
bool FullChecksumMatrix<T>::errorCorrection() {
	// Pour une ou deux erreurs.
	// des systèmes seront utilisés par la suite

	vector<int> r;
	vector<int> c;

	for(int i = 1; i <= this->getM(); i++){
		if(!equal(PSTL_TYPE_SUM_TO_DOUBLE(this->computeRowSum(i)), 0., EPS1, 0)) r.push_back(i);
	}

	for(int j = 1; j <= this->getN(); j++){
		if(!equal(PSTL_TYPE_SUM_TO_DOUBLE(this->computeColumnSum(j)), 0., EPS1, 0)) c.push_back(j);
	}

	if(r.size() + c.size() > 0){
		// une erreur :
		//     - 1 colonne et 1 ligne non valides.
		//     - 2 équations à 1 inconnue => OK
		if(r.size() == 1 && c.size() == 1){
			(*this)(r[0], c[0]) += (c[0] == this->getN() ? 1 : -1) * this->computeRowSum(r[0]);
			return true;
		}

		// deux erreurs même ligne (elles s'annulent)
		//     - 2 colonnes non valides.
		//     - 2 équations à 2m inconnue => infinité de solutions
		else if(r.size() == 0 && c.size() == 2){
			return false;
		}

		// deux erreurs même colonne (elles s'annulent)
		//     - 2 lignes non valides.
		//     - 2 équations à 2n inconnue => infinité de solutions
		else if(r.size() == 2 && c.size() == 0){
			return false;
		}

		// deux erreurs même ligne (elles ne s'annulent pas)
		//     - 2 colonnes et 1 ligne non valides.
		//     - 3 équations à 2 inconnue => OK
		else if(r.size() == 1 && c.size() == 2){
			for (vector<int>::iterator j = c.begin(); j != c.end(); j++) {
				(*this)(r[0], *j) += (r[0] == this->getM() ? 1 : -1) * this->computeColumnSum(*j);
			}
			return true;
		}

		// deux erreurs même colonne (elles ne s'annulent pas)
		//     - 2 lignes et 1 colonne non valides.
		//     - 3 équations à 2 inconnue => OK
		else if(r.size() == 2 && c.size() == 1){
			for (vector<int>::iterator i = r.begin(); i != r.end(); i++) {
				(*this)(*i, c[0]) += (c[0] == this->getN() ? 1 : -1) * this->computeRowSum(*i);
			}
			return true;
		}

		// deux erreurs non adjacentes
		//     - 2 colonnes et 2 lignes non valides (ici on suppose qu'il n'y a que 2 erreurs : il pourrait y en avoir 3 ou 4).
		//     - 4 équations à 2 inconnue, mais 2 possibilités pour les 2 inconnues => 2 solutions => on ne corrige pas
		else if(r.size() == 2 && c.size() == 2){
			return false;
		}

		return false;
	}

	return true;
}

template class FullChecksumMatrix<double>;
