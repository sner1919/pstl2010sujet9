#include "ErrorGenerator.hpp"
#include <pthread.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <limits>

template <class T>
ErrorGenerator<T>::ErrorGenerator() {
	srand(time(NULL));
}

template <class T>
void* ErrorGenerator<T>::thread(void* arg) {
	threadArg* tA = (threadArg*) arg;
	IMatrix<T>& M = *tA->M;
	int nb = tA->nb;
	int iMin = tA->iMin;
	int iMax = tA->iMax;
	int jMin = tA->jMin;
	int jMax = tA->jMax;

	int l, c, id;
	bool contains;
	vector<int> ids;
	T x;

	for(int i = 0; i < nb; i++){
		// recherche des indices
		do {
			l = rand() % (iMax - iMin + 1) + iMin;
			c = rand() % (jMax - jMin + 1) + jMin;
			id = M.locationId(l, c);

			contains = false;
			for(unsigned int i = 0; i < ids.size(); i++){
				if(ids[i] == id){
					contains = true;
					break;
				}
			}
		} while(contains);

		// modification d'une valeur
		do { x = ((float) rand() / (float) RAND_MAX - 0.5) * 2 * numeric_limits<double>::max(); } while(M(l, c) == x);
		M(l, c) = x;

		ids.push_back(id);
	}

	delete tA;
	return NULL;
}

template <class T>
pthread_t ErrorGenerator<T>::generateError(IMatrix<T>& M, int nb, int iMin, int iMax, int jMin, int jMax) {
	pthread_t th;

	threadArg* tA = new threadArg;
	tA->M = &M;
	tA->nb = nb;
	tA->iMin = iMin;
	tA->iMax = iMax;
	tA->jMin = jMin;
	tA->jMax = jMax;
	pthread_create(&th, NULL, thread, (void*) tA);

	return th;
}

template class ErrorGenerator<double>;

