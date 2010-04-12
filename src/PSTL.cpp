/* ++++++++++++++++++ librairies nécessaires (debian/ubuntu) ++++++++++++++++++
=================================== CppUnit ==============================
- libcppunit-dev
	Bibliothèque de test unitaire pour C++

	CppUnit est une structure simple pour incorporer des cas de test dans votre code C++. Il est semblable à xUnit et JUnit dont il s'est inspiré.

	Le paquet « libqttestrunner1 » est nécessaire pour utiliser l'interface graphique Qt d'exécution de test.

=================================== GMP ==================================
- libgmp3-dev
	Multiprecision arithmetic library developers tools

	This development package provides the header files and the symbolic links to allow compilation and linking of programs that use the libraries provided in the libgmp3 package.

	Both C and C++ bindings are present in this package. Package libstdc++-dev is required to use the C++ bindings.

	The MPFR library (multiple-precision floating-point) used to be included, but has since been moved to package libmpfr-dev.
	This development package provides the header files and the symbolic links to allow compilation and linking of programs that use the libraries provided in the libgmp3 package.

	Both C and C++ bindings are present in this package. Package libstdc++-dev is required to use the C++ bindings.

	The MPFR library (multiple-precision floating-point) used to be included, but has since been moved to package libmpfr-dev.

- libstdc++-dev
	Bibliotheque GNU C++ standard v3 (fichiers de développement)

	Ce paquet contient les en-têtes et les fichiers de bibliothèques statiques nécessaires pour construire des programmes C++ qui utilisent libstdc++.

	libstdc++-v3 est une réécriture complète de la précédente bibliothèque libstdc++-v2 qui était incluse jusqu'à g++-2.95. La première version de libstdc++-v3 est apparue dans g++-3.0.

------------ dépendances installées automatiquement ------------
- libgmp3c2
	Bibliothèque arithmétique à multi-précision

	GNU MP est une bibliothèque pour les programmes nécessitant une arithmétique à précision arbitraire (c’est-à-dire un paquet pour gérer les grands nombres). Elle peut travailler avec des entiers signés, des rationnels et des nombres à virgule flottante.

	Elle possède un grand nombre de fonctions, et les fonctions ont une interface normalisée.

- libgmpxx4ldbl
	Multiprecision arithmetic library (C++ bindings)

	GNU MP is a programmer's library for arbitrary precision arithmetic (ie, a bignum package). It can operate on signed integer, rational, and floating point numeric types.

=================================== ATLAS ================================
- libatlas-base-dev
	Automatically Tuned Linear Algebra Software,generic static

	ATLAS is an approach for the automatic generation and optimization of numerical software. Currently ATLAS supplies optimized versions for the complete set of linear algebra kernels known as the Basic Linear Algebra Subroutines (BLAS), and a subset of the linear algebra routines in the LAPACK library.

	This package includes the static libraries and symbolic links needed for program development.

------------ dépendances installées automatiquement ------------
- libatlas-headers
	Automatically Tuned Linear Algebra Software,C header files

	ATLAS is an approach for the automatic generation and optimization of numerical software. Currently ATLAS supplies optimized versions for the complete set of linear algebra kernels known as the Basic Linear Algebra Subroutines (BLAS), and a subset of the linear algebra routines in the LAPACK library.

	This package provides the headers needed to compile against the libraries provided by ATLAS.

- libatlas3gf-base
	Automatically Tuned Linear Algebra Software,generic shared

	ATLAS is an approach for the automatic generation and optimization of numerical software. Currently ATLAS supplies optimized versions for the complete set of linear algebra kernels known as the Basic Linear Algebra Subroutines (BLAS), and a subset of the linear algebra routines in the LAPACK library.

	The libraries in this package are built without any processor extension instructions, and should run on all processors of this general architecture, albeit less than optimally.

	On some architectures, multiple binary packages are provided to take advantage of certain commonly available processor instruction set extensions. The instruction extension set used is indicated in the package name, with 'base' denoting no extensions. In general, you will obtain the best performance by installing the package with the most advanced instruction extension set your machine is capable of running.
*/

#include "Matrix.hpp"
#include "Vector.hpp"
#include "RowChecksumMatrix.hpp"
#include "ColumnChecksumMatrix.hpp"
#include "FullChecksumMatrix.hpp"
#include "CalculatorNaive.hpp"
#include "Processor.hpp"
#include "ErrorGenerator.hpp"
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    try{
    	CalculatorNaive<PSTL_TYPE> calc;
    	ErrorGenerator<PSTL_TYPE> gen;
    	Processor<PSTL_TYPE> proc(calc, gen);
        /* ---------- allocation statique de mémoire ---------- */
        PSTL_TYPE LData[2][2] = {{1., 0.}, {1.5, 1.}};
        PSTL_TYPE UData[2][2] = {{4., 3.}, {0., -1.5}};
        /* ---------------------------------------------------- */
        Matrix<PSTL_TYPE> L(LData[0], 2, 2);
        Matrix<PSTL_TYPE> LBis(L);
        Matrix<PSTL_TYPE> U(UData[0], 2, 2);
        Matrix<PSTL_TYPE> A(2, 2);

        cout << "L = " << L.toString() << endl;
        cout << "LBis = " << LBis.toString() << endl;
        cout << "U = " << U.toString() << endl;

        // opérations
        proc.mult(A, L, U);
        cout << "L * U = " << A.toString() << endl;

        proc.mult(A, L, 2.);
        cout << "L * 2 = " << A.toString() << endl;

        proc.add(A, L, U);
        cout << "L + U = " << A.toString() << endl;

        proc.transpose(A, L);
        cout << "Lt = " << A.toString() << endl;

        proc.mult(A, L, U);
        proc.mult(L, A, 0.);
        proc.mult(U, A, 0.);
        proc.LU(L, U, A);
        cout << "A = L * U" << endl;
        cout << "avec A = " << A.toString();
        cout << "=>" << endl;
        cout << "L = " << L.toString();
        cout << "U = " << U.toString() << endl;

        ColumnChecksumMatrix<PSTL_TYPE> Uc(U);
        cout << "Uc = " << Uc.toString();

        RowChecksumMatrix<PSTL_TYPE> Ur(U);
        cout << "Ur = " << Ur.toString();
        cout << "U = " << U.toString() << endl;

        ColumnChecksumMatrix<PSTL_TYPE> Urc(Ur);
        cout << "Urc = " << Urc.toString();

        FullChecksumMatrix<PSTL_TYPE> Uf(U);
        cout << "Uf = " << Uf.toString() << endl;
        cout << "Uf.getRowSummationVector() = " << Uf.getRowSummationVector().toString() << endl;
        cout << "Uf.getColumnSummationVector() = " << Uf.getColumnSummationVector().toString() << endl;

        cout << "generateError()" << endl;
        gen.generateError(Uf, 1, 1, Uf.getM(), 1, Uf.getN());
        cout << "Uf = " << Uf.toString();
        cout << "Uf.errorCorrection()" << endl;
        Uf.errorCorrection();
        cout << "Uf = " << Uf.toString() << endl;

        cout << "CLOCKS_PER_SEC :" << CLOCKS_PER_SEC << endl;

        cout << "The maximum value for type float is:  "
             << numeric_limits<float>::max( )
             << endl;
        cout << "The maximum value for type double is:  "
             << numeric_limits<double>::max( )
             << endl;
        cout << "The maximum value for type int is:  "
             << numeric_limits<int>::max( )
             << endl;
        cout << "The maximum value for type short int is:  "
             << numeric_limits<short int>::max( )
             << endl;

        double x1 = pow(2, 60);
        x1 += 1;
        x1 -= pow(2, 60);
        cout << "x1 : " << x1 << endl;

        mpf_class x2 = pow(2, 60);
        x2 += 1;
        x2 -= pow(2, 60);
        cout << "x2 : " << x2 << endl;

    }
    catch(const std::exception& e)
    {
      std::cerr << "ERREUR : " << e.what() << std::endl;
    }

    return 0;
}
