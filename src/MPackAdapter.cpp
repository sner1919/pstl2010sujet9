#include "MPackAdapter.hpp"
#include <cstdlib>
#include <dlfcn.h>
#include <cmath>

#include "../include/mpack/mblas_double.h"
#include "../include/mpack/mlapack_double.h"

typedef typeof(Rgemm)* Rgemm_t;
typedef typeof(Rscal)* Rscal_t;
typedef typeof(Raxpy)* Raxpy_t;
typedef typeof(Rgetrf)* Rgetrf_t;

struct API {
	void* handle[2];
	Rgemm_t Rgemm;
	Rscal_t Rscal;
	Raxpy_t Raxpy;
	Rgetrf_t Rgetrf;
} api;

MPackAdapter::MPackAdapter() {
	// open the library
	string libs[] = {"libmblas_double.so", "libmlapack_double.so"};
	for(int i = 0; i < 2; i++){
		string path = ((string) ("./lib/" MACRO_TO_STR(CPU) "/mpack/")).append(libs[i]);
		api.handle[i] = (dlopen(path.data(), RTLD_LAZY | RTLD_GLOBAL));
		if (!api.handle[i]) {
			cerr << "Cannot open library : " << dlerror() << '\n';
			exit(1);
		}
	}

	// load symbols
	dlerror(); // reset errors
	api.Rgemm = (Rgemm_t) dlsym(api.handle[0], "_Z5RgemmPKcS0_llldPdlS1_ldS1_l");
	api.Rscal = (Rscal_t) dlsym(api.handle[0], "_Z5RscalldPdl");
	api.Raxpy = (Raxpy_t) dlsym(api.handle[0], "_Z5RaxpyldPdlS_l");
	api.Rgetrf = (Rgetrf_t) dlsym(api.handle[1], "_Z6RgetrfllPdlPlS0_");
	const char *dlsym_error = dlerror();
	if (dlsym_error) {
		cerr << "Cannot load symbols : " << dlsym_error << '\n';
		for(unsigned int i = 0; i < 2; i++) dlclose(api.handle[i]);
		exit(1);
	}
}

MPackAdapter::~MPackAdapter() {
	// close the library
	for(unsigned int i = 0; i < 2; i++) dlclose(api.handle[i]);
}

void MPackAdapter::dgemm(const enum CBLAS_ORDER_ Order, const enum CBLAS_TRANSPOSE_ TransA,
                            const enum CBLAS_TRANSPOSE_ TransB, const int M, const int N,
                            const int K, const double alpha, const double *A,
                            const int lda, const double *B, const int ldb,
                            const double beta, double *C, const int ldc) const {
	api.Rgemm((TransA == CblasTrans_ ? "Transpose" : "NoTranspose"),
			(TransB == CblasTrans_ ? "Transpose" : "NoTranspose"), (mpackint) M, (mpackint) N,
			  (mpackint) K, (double) alpha, (double *) A,
			  (mpackint) lda, (double *) B, (mpackint) ldb,
			  (double) beta, (double *) C, (mpackint) ldc);
}

void MPackAdapter::dscal(const int N, const double alpha, double *X, const int incX) const {
	api.Rscal((mpackint) N, (double) alpha, X, (mpackint) incX);
}

void MPackAdapter::daxpy(const int N, const double alpha, const double *X,
		                    const int incX, double *Y, const int incY) const {
	api.Raxpy((mpackint) N, (double) alpha, (double *) X,
			  (mpackint) incX, Y, (mpackint) incY);
}

int MPackAdapter::dgetrf(int *m, int *n, double *a,
		                    int *lda, int *ipiv, int *info) const {
	api.Rgetrf((mpackint) *m, (mpackint) *n, a,
					  (mpackint) *lda, (mpackint*) ipiv, (mpackint*) info);

	return *info;
}
