#pragma once
#include "IRowChecksumMatrix.hpp"
#include "IColumnChecksumMatrix.hpp"

template <class T> class IFullChecksumMatrix : public virtual IRowChecksumMatrix<T>, public virtual IColumnChecksumMatrix<T> {
    public:
		/*
		 * Effectue la correction d'erreurs de la matrice.
		 */
		virtual void errorCorrection() = 0;
};
