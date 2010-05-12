#pragma once
#include "../settings.hpp"

enum CBLAS_ORDER_ {CblasRowMajor_=101, CblasColMajor_=102 };
enum CBLAS_TRANSPOSE_ {CblasNoTrans_=111, CblasTrans_=112, CblasConjTrans_=113, AtlasConj_=114};

class IBlasLapackAdapter {
    public:
		/*
		 * Voir documentation CBLAS
		 */
        virtual void dgemm(const enum CBLAS_ORDER_ Order, const enum CBLAS_TRANSPOSE_ TransA,
						   const enum CBLAS_TRANSPOSE_ TransB, const int M, const int N,
						   const int K, const double alpha, const double *A,
						   const int lda, const double *B, const int ldb,
						   const double beta, double *C, const int ldc) const = 0;

		/*
		 * Voir documentation CBLAS
		 */
        virtual void dscal(const int N, const double alpha, double *X, const int incX) const = 0;

		/*
		 * Voir documentation CBLAS
		 */
        virtual void daxpy(const int N, const double alpha, const double *X,
                           const int incX, double *Y, const int incY) const = 0;

		/*
		 * Voir documentation LAPACK
		 */
        virtual int dgetrf(int *m, int *n, double *a,
        		           int *lda, int *ipiv, int *info) const = 0;
};
