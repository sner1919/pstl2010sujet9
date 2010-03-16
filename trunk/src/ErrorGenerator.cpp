#include "ErrorGenerator.hpp"

template <class T>
void ErrorGenerator<T>::generateError(IMatrix<T>& M, int nb, int iMin, int iMax, int jMin, int jMax){
	int l, c, id;
	bool contains;
	vector<int> ids;
	srand(time(NULL));

	for(int i = 0; i < nb; i++){
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

		M(l, c) = rand();
		ids.push_back(id);
	}
}

template class ErrorGenerator<double>;

