#include "FullChecksumMatrix.hpp"

template <class T>
FullChecksumMatrix<T>::FullChecksumMatrix(IMatrix<T>& M) : Matrix<T>(M.getData(), M.getM() + 1, M.getN() + 1),
RCM(new RowChecksumMatrix<T>(M)), CCM(new ColumnChecksumMatrix<T>(*RCM)) {}

template <class T>
FullChecksumMatrix<T>::~FullChecksumMatrix() {
	delete RCM;
	delete CCM;
}

template <class T>
T& FullChecksumMatrix<T>::operator()(int i, int j) {
	return CCM->operator()(i, j);
}

template <class T>
IVector<T>& FullChecksumMatrix<T>::getRowSummationVector() {
	return RCM->getRowSummationVector();
}

template <class T>
T FullChecksumMatrix<T>::computeRowSum(int i) {
	// RCM ne contient pas la dernière ligne
	T sum = 0;

	for(int j = 1; j < this->getN(); j++) sum += (*this)(i, j);

	return sum - (*this)(i, this->getN());
}

template <class T>
IVector<T>& FullChecksumMatrix<T>::getColumnSummationVector() {
	return CCM->getColumnSummationVector();
}

template <class T>
T FullChecksumMatrix<T>::computeColumnSum(int j) {
	return CCM->computeColumnSum(j);
}

template <class T>
bool FullChecksumMatrix<T>::errorCorrection() {
	// Pour une ou deux erreurs.
	// des systèmes seront utilisés par la suite

	vector<int> r;
	vector<int> c;

	for(int i = 1; i <= this->getM(); i++){
		if(computeRowSum(i) != 0) r.push_back(i);
	}

	for(int j = 1; j <= this->getN(); j++){
		if(computeColumnSum(j) != 0) c.push_back(j);
	}

	if(r.size() + c.size() > 0){
		// une erreur :
		//     - 1 colonne et 1 ligne non valides.
		//     - 2 équations à 1 inconnue => OK
		if(r.size() == 1 && c.size() == 1){
			(*this)(r[0], c[0]) += (c[0] == this->getN() ? 1 : -1) * computeRowSum(r[0]);
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
				(*this)(r[0], *j) += (r[0] == this->getM() ? 1 : -1) * computeColumnSum(*j);
			}
			return true;
		}

		// deux erreurs même colonne (elles ne s'annulent pas)
		//     - 2 lignes et 1 colonne non valides.
		//     - 3 équations à 2 inconnue => OK
		else if(r.size() == 2 && c.size() == 1){
			for (vector<int>::iterator i = r.begin(); i != r.end(); i++) {
				(*this)(*i, c[0]) += (c[0] == this->getN() ? 1 : -1) * computeRowSum(*i);
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
