#include "IntelMKLAdapter.hpp"
namespace {
	extern "C" {
		#include "../include/intelmkl/mkl_types.h"
		#include "../include/intelmkl/mkl_cblas.h"
		#include "../include/intelmkl/mkl_lapack.h"
	}

	typedef typeof(cblas_dgemm)* cblas_dgemm_t;
	typedef typeof(cblas_dscal)* cblas_dscal_t;
	typedef typeof(cblas_daxpy)* cblas_daxpy_t;
	typedef typeof(dgetrf_)* dgetrf__t;

	struct API {
		void* handle[3];
		cblas_dgemm_t cblas_dgemm;
		cblas_dscal_t cblas_dscal;
		cblas_daxpy_t cblas_daxpy;
		dgetrf__t dgetrf_;
	} api;
}

IntelMKLAdapter::IntelMKLAdapter() {
	// open the library
	api.handle[0] = dlopen("./lib/" MACRO_TO_STR(CPU) "/intelmkl/libmkl_core.so", RTLD_LAZY | RTLD_GLOBAL);
	api.handle[1] = dlopen("./lib/" MACRO_TO_STR(CPU) "/intelmkl/libmkl_sequential.so", RTLD_LAZY | RTLD_GLOBAL);
	api.handle[2] = dlopen("./lib/" MACRO_TO_STR(CPU) "/intelmkl/libmkl_intel.so", RTLD_LAZY | RTLD_GLOBAL);
	for(int i = 0; i < 3; i++){
		if (!api.handle[i]) {
			cerr << "Cannot open library : " << dlerror() << '\n';
			exit(1);
		}
	}

	// load symbols
	dlerror(); // reset errors
	api.cblas_dgemm = (cblas_dgemm_t) dlsym(api.handle[2], "cblas_dgemm");
	api.cblas_dscal = (cblas_dscal_t) dlsym(api.handle[2], "cblas_dscal");
	api.cblas_daxpy = (cblas_daxpy_t) dlsym(api.handle[2], "cblas_daxpy");
	api.dgetrf_ = (dgetrf__t) dlsym(api.handle[2], "dgetrf_");
	const char *dlsym_error = dlerror();
	if (dlsym_error) {
		cerr << "Cannot load symbols : " << dlsym_error << '\n';
		for(int i = 0; i < 3; i++) dlclose(api.handle[i]);
		exit(1);
	}
}

IntelMKLAdapter::~IntelMKLAdapter() {
	// close the library
	for(int i = 0; i < 3; i++) dlclose(api.handle[i]);
}

void IntelMKLAdapter::dgemm(const enum CBLAS_ORDER_ Order, const enum CBLAS_TRANSPOSE_ TransA,
                         const enum CBLAS_TRANSPOSE_ TransB, const int M, const int N,
                         const int K, const double alpha, const double *A,
                         const int lda, const double *B, const int ldb,
                         const double beta, double *C, const int ldc) const {
	api.cblas_dgemm((CBLAS_ORDER) Order, (CBLAS_TRANSPOSE) TransA,
				(CBLAS_TRANSPOSE) TransB, M, N,
				K, alpha, A,
				lda, B, ldb,
		        beta, C, ldc);
}

void IntelMKLAdapter::dscal(const int N, const double alpha, double *X, const int incX) const {
	api.cblas_dscal(N, alpha, X, incX);
}

void IntelMKLAdapter::daxpy(const int N, const double alpha, const double *X,
		                 const int incX, double *Y, const int incY) const {
	api.cblas_daxpy(N, alpha, X,
				incX, Y, incY);
}

int IntelMKLAdapter::dgetrf(int *m, int *n, double *a,
		                 int *lda, int *ipiv, int *info) const {
	api.dgetrf_(m, n, a, lda, ipiv, info);

	return *info;
}
