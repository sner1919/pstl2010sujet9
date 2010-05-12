#include "AtlasAdapter.hpp"
namespace {
	extern "C" {
		#include "../include/atlas/cblas.h"
		#include "../include/atlas/clapack.h"
	}

	typedef typeof(cblas_dgemm)* cblas_dgemm_t;
	typedef typeof(cblas_dscal)* cblas_dscal_t;
	typedef typeof(cblas_daxpy)* cblas_daxpy_t;
	typedef typeof(clapack_dgetrf)* clapack_dgetrf_t;

	struct API {
		void* handle[3];
		cblas_dgemm_t cblas_dgemm;
		cblas_dscal_t cblas_dscal;
		cblas_daxpy_t cblas_daxpy;
		clapack_dgetrf_t clapack_dgetrf;
	} api;
}

AtlasAdapter::AtlasAdapter() {
	// open the library
	api.handle[0] = dlopen("./lib/" macroToStr(CPU) "/atlas/libatlas.so", RTLD_LAZY | RTLD_GLOBAL);
	api.handle[1] = dlopen("./lib/" macroToStr(CPU) "/atlas/libcblas.so", RTLD_LAZY | RTLD_GLOBAL);
	api.handle[2] = dlopen("./lib/" macroToStr(CPU) "/atlas/libclapack.so", RTLD_LAZY | RTLD_GLOBAL);
	for(int i = 0; i < 3; i++){
		if (!api.handle[i]) {
			cerr << "Cannot open library : " << dlerror() << '\n';
			exit(1);
		}
	}

	// load symbols
	dlerror(); // reset errors
	api.cblas_dgemm = (cblas_dgemm_t) dlsym(api.handle[1], "cblas_dgemm");
	api.cblas_dscal = (cblas_dscal_t) dlsym(api.handle[1], "cblas_dscal");
	api.cblas_daxpy = (cblas_daxpy_t) dlsym(api.handle[1], "cblas_daxpy");
	api.clapack_dgetrf = (clapack_dgetrf_t) dlsym(api.handle[2], "clapack_dgetrf");
	const char *dlsym_error = dlerror();
	if (dlsym_error) {
		cerr << "Cannot load symbols : " << dlsym_error << '\n';
		for(int i = 0; i < 3; i++) dlclose(api.handle[i]);
		exit(1);
	}
}

AtlasAdapter::~AtlasAdapter() {
	// close the library
	for(int i = 0; i < 3; i++) dlclose(api.handle[i]);
}

void AtlasAdapter::dgemm(const enum CBLAS_ORDER_ Order, const enum CBLAS_TRANSPOSE_ TransA,
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

void AtlasAdapter::dscal(const int N, const double alpha, double *X, const int incX) const {
	api.cblas_dscal(N, alpha, X, incX);
}

void AtlasAdapter::daxpy(const int N, const double alpha, const double *X,
		                 const int incX, double *Y, const int incY) const {
	api.cblas_daxpy(N, alpha, X,
				incX, Y, incY);
}

int AtlasAdapter::dgetrf(int *m, int *n, double *a,
		                 int *lda, int *ipiv, int *info) const {
	*info = api.clapack_dgetrf(CblasColMajor, *m, *n, a, *lda, ipiv);

	for(int i = 0; i < *m; i++) ipiv[i]++;

	return *info;
}
