#include "MPackAdapter.hpp"
#include <cstdlib>
#include <dlfcn.h>

namespace {
	extern "C" {
		#include "../include/gotoblas/cblas.h"
		#include "../include/gotoblas/f2c.h"
		#include "../include/gotoblas/clapack.h"
	}

	typedef typeof(cblas_dgemm)* cblas_dgemm_t;
	typedef typeof(cblas_dscal)* cblas_dscal_t;
	typedef typeof(cblas_daxpy)* cblas_daxpy_t;
	typedef typeof(dgetrf_)* dgetrf__t;

	struct API {
		void* handle;
		cblas_dgemm_t cblas_dgemm;
		cblas_dscal_t cblas_dscal;
		cblas_daxpy_t cblas_daxpy;
		dgetrf__t dgetrf_;
	} api;
}

MPackAdapter::MPackAdapter() {
	// open the library
	api.handle = dlopen("./lib/" MACRO_TO_STR(CPU) "/gotoblas/libgoto2.so", RTLD_LAZY);
	if (!api.handle) {
		cerr << "Cannot open library : " << dlerror() << '\n';
		exit(1);
	}

	// load symbols
	dlerror(); // reset errors
	api.cblas_dgemm = (cblas_dgemm_t) dlsym(api.handle, "cblas_dgemm");
	api.cblas_dscal = (cblas_dscal_t) dlsym(api.handle, "cblas_dscal");
	api.cblas_daxpy = (cblas_daxpy_t) dlsym(api.handle, "cblas_daxpy");
	api.dgetrf_ = (dgetrf__t) dlsym(api.handle, "dgetrf_");
	const char *dlsym_error = dlerror();
	if (dlsym_error) {
		cerr << "Cannot load symbols : " << dlsym_error << '\n';
		dlclose(api.handle);
		exit(1);
	}
}

MPackAdapter::~MPackAdapter() {
	// close the library
	dlclose(api.handle);
}

void MPackAdapter::dgemm(const enum CBLAS_ORDER_ Order, const enum CBLAS_TRANSPOSE_ TransA,
                            const enum CBLAS_TRANSPOSE_ TransB, const int M, const int N,
                            const int K, const double alpha, const double *A,
                            const int lda, const double *B, const int ldb,
                            const double beta, double *C, const int ldc) const {
	api.cblas_dgemm((CBLAS_ORDER) Order, (CBLAS_TRANSPOSE) TransA,
				(CBLAS_TRANSPOSE) TransB, M, N,
				K, alpha, (double *) A,
				lda, (double *) B, ldb,
		        beta, C, ldc);
}

void MPackAdapter::dscal(const int N, const double alpha, double *X, const int incX) const {
	api.cblas_dscal(N, alpha, X, incX);
}

void MPackAdapter::daxpy(const int N, const double alpha, const double *X,
		                    const int incX, double *Y, const int incY) const {
	api.cblas_daxpy(N, alpha, (double *) X,
				incX, Y, incY);
}

int MPackAdapter::dgetrf(int *m, int *n, double *a,
		                    int *lda, int *ipiv, int *info) const {
	return api.dgetrf_(m, n, a, lda, ipiv, info);
}
