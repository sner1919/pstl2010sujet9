#pragma once
#include "../settings.hpp"
#include "IRowChecksumMatrix.hpp"
#include "IColumnChecksumMatrix.hpp"

template <class T> class IFullChecksumMatrix : public virtual IRowChecksumMatrix<T>, public virtual IColumnChecksumMatrix<T> {
    public:
		/*
		 * Effectue la correction d'erreurs de la matrice.
		 * @return false si une erreur a été detectée mais n'a pas pu être corrigée
		 */
		virtual bool errorCorrection() = 0;
};
