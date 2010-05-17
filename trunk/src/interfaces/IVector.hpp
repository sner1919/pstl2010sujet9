#pragma once
#include "../settings.hpp"
#include "IMatrix.hpp"

template <class T> class IVector : public virtual IMatrix<T> {
    public:
		/*
		 * Donne un élément contenu dans le vecteur.
		 * remarque : surcharge de l'opérateur "()"
		 * @param i l'indice
		 * @return l'élément à l'indice i
		 */
		virtual PSTL_TYPE_UNION operator()(int i) const = 0;
};
