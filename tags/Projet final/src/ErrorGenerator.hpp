#pragma once
#include "settings.hpp"
#include "interfaces/IErrorGenerator.hpp"

template <class T> class ErrorGenerator : public IErrorGenerator<T> {
	struct threadArg {
		IMatrix<T>* M; int nb; int iMin; int iMax; int jMin; int jMax;
	};

	static void* thread(void *);

public:
	/*
	 * Crée un générateur d'erreurs.
	 */
	ErrorGenerator();

	//Implémentation de IErrorGenerator
    pthread_t generateError(IMatrix<T>& M, int nb, int iMin, int iMax, int jMin, int jMax);

};
