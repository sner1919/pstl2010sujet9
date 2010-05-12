#include "interfaces/IBlasLapackAdapter.hpp"
#include <cstdlib>
#include <dlfcn.h>

class IntelMKLAdapter : public virtual IBlasLapackAdapter {
	public:
		IntelMKLAdapter();

		~IntelMKLAdapter();

		// implémentation de IBlasLapackAdapter
		void dgemm(const enum CBLAS_ORDER_ Order, const enum CBLAS_TRANSPOSE_ TransA,
	               const enum CBLAS_TRANSPOSE_ TransB, const int M, const int N,
	               const int K, const double alpha, const double *A,
	               const int lda, const double *B, const int ldb,
	               const double beta, double *C, const int ldc) const;

		// implémentation de IBlasLapackAdapter
		void dscal(const int N, const double alpha, double *X, const int incX) const;

		// implémentation de IBlasLapackAdapter
		void daxpy(const int N, const double alpha, const double *X,
				   const int incX, double *Y, const int incY) const;

		// implémentation de IBlasLapackAdapter
		int dgetrf(int *m, int *n, double *a,
				   int *lda, int *ipiv, int *info) const;
};
