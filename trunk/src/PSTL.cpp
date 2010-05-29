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
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    try{
    	/* ----------------------------------- */
        cout.precision(STREAM_PRECISION);
        mpf_set_default_prec(512);
    	/* ----------------------------------- */

    	CalculatorNaive<double> calc;
    	ErrorGenerator<double> gen;
    	Processor<double> proc(calc, gen);
        /* ---------- allocation statique de mémoire ---------- */
    	double LData[2][2] = {{1., 0.}, {1.5, 1.}};
    	double UData[2][2] = {{4., 3.}, {0., -1.5}};
        /* ---------------------------------------------------- */
        Matrix<double> P(2, 2);
        Matrix<double> L(LData[0], 2, 2);
        Matrix<double> LBis(L);
        Matrix<double> U(UData[0], 2, 2);
        Matrix<double> A(2, 2);

        cout << "L = " << L.toString() << endl;
    	cout << "coucou" << endl;
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
        proc.LU(P, L, U, A);
        cout << "A = P * L * U" << endl;
        cout << "avec A = " << A.toString();
        cout << "=>" << endl;
        cout << "P = " << P.toString();
        cout << "L = " << L.toString();
        cout << "U = " << U.toString() << endl;

        ColumnChecksumMatrix<double> Uc(U);
        cout << "Uc = " << Uc.toString();

        RowChecksumMatrix<double> Ur(U);
        cout << "Ur = " << Ur.toString();
        cout << "U = " << U.toString() << endl;

        ColumnChecksumMatrix<double> Urc(Ur);
        cout << "Urc = " << Urc.toString();

        FullChecksumMatrix<double> Uf(U);
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

        if (0.1 + 0.2 != 0.3) cout << "0.1 + 0.2 != 0.3 !!!!" << endl;

       cout << "numeric_limits<float>::min() : " << numeric_limits<float>::min() << endl;
       cout << "numeric_limits<float>::max() : " << numeric_limits<float>::max() << endl;
       cout << "numeric_limits<float>::epsilon() : " << numeric_limits<float>::epsilon() << endl;
       cout << "numeric_limits<float>::round_error() : " << numeric_limits<float>::round_error() << endl;
       cout << "numeric_limits<double>::min() : " << numeric_limits<double>::min() << endl;
       cout << "numeric_limits<double>::max() : " << numeric_limits<double>::max() << endl;
       cout << "numeric_limits<double>::epsilon() : " << numeric_limits<double>::epsilon() << endl;
       cout << "numeric_limits<double>::round_error() : " << numeric_limits<double>::round_error() << endl;

        double x1 = pow(2, 60);
        x1 += 1;
        x1 -= pow(2, 60);
        cout << "x1 : " << x1 << endl;

        mpf_class x2 = pow(2, 60);
        x2 += 1;
        x2 -= pow(2, 60);
        cout << "x2 : " << x2 << endl;

        /* ---------------- Test d'égalité ---------------
			utilise la représentation binaire des flottants :
				- chaque float correspond à un int et chaque double correspond à deux int !!!!!!!!!!
				=> mieux que les tests d'égalité avec un epsilon absolu ou même relatif
        */


        cout << "--------------------------" << endl;
        for(int i = -3; i <= 3; i++) {
			cout << "*********************" << endl;
			cout << "i : " << i << endl;
        	float f = indexToFloat(i);
			cout << "f = indexToFloat(i) : " << f << endl;
			cout << "floatToIndex(f) : " << floatToIndex(f) << endl;
    	}

        int ind[3][2];
        ind[0][0] = numeric_limits<int>::min();
        ind[0][1] = 3;
        ind[1][0] = -2;
        ind[1][1] = 5;
        ind[2][0] = numeric_limits<int>::max() - 2;
        ind[2][1] = 3;
        for(int i = -2; i <= 2; i++) {
			for(int k = 0; k < 3; k++) {
				for(int j = ind[k][0], l = 0; l < ind[k][1]; j++, l++) {
					cout << "++++++++++++++++++++++++" << endl;
					cout << "i : " << i << endl;
					cout << "j : " << j << endl;
					double d = indexToDouble(i, j);
					cout << "d = indexToDouble(i, j) : " << d << endl;
					int a1, a0;
					doubleToIndex(d, &a1, &a0);
					cout << "doubleToIndex(d, &a1, &a0)" << endl;
					cout << "a1 : " << a1 << endl;
					cout << "a0 : " << a0 << endl;
				}
			}
        }

		cout << "--------------------------" << endl;

		double a = 0.1 + 0.2;
		double b = 0.3;
		cout << endl << endl << "a = 0.1 + 0.2 : " << a << endl;
		int a0, a1;
		doubleToIndex(a, &a1, &a0);
		cout << "doubleToIndex(a, &a1, &a0)" << endl;
		cout << "a1 : " << a1 << endl;
		cout << "a0 : " << a0 << endl;
		cout << "indexToDouble(a1, a0) : " << indexToDouble(a1, a0) << endl;

		cout << "b = 0.3 : " << b << endl;
		int b0, b1;
		doubleToIndex(b, &b1, &b0);
		cout << "doubleToIndex(b, &b1, &b0)" << endl;
		cout << "b1 : " << b1 << endl;
		cout << "b0 : " << b0 << endl;
		cout << "indexToDouble(b1, b0) : " << indexToDouble(b1, b0) << endl;

		cout << "a == b : " << (a == b) << endl;
		cout << "a - b : " << a - b << endl;

		cout << "--------------------------" << endl;
		int i0 = a0;
		int i1 = a1;
		for(int i = -2; i <= 2; i++){
			a1 = i1 + i;
			for(int j = -2; j <= 2; j++){
				a0 = i0 + j;
				cout << "a1 : " << a1 << endl;
				cout << "a0 : " << a0 << endl;
				cout << "indexToDouble(a1, a0) : " << indexToDouble(a1, a0) << endl;
			}
		}

		cout << "--------------------------" << endl;
		double max = numeric_limits<double>::max();
	    cout << "max = numeric_limits<double>::max() : " << max << endl;
		doubleToIndex(max, &a1, &a0);
		cout << "doubleToIndex(max, &a1, &a0)" << endl;
		cout << "a1 : " << a1 << endl;
		cout << "a0 : " << a0 << endl;
		cout << "indexToDouble(a1, a0) : " << indexToDouble(a1, a0) << endl;
		cout << "indexToDouble(a1, a0-1):" << indexToDouble(a1, a0 - 1) << endl;
		cout << "--------------------------" << endl;


		TYPE_SUM a2 = 0.1;
		a2 += 0.2;
		TYPE_SUM b2 = 0.3;
		cout << "a2 : " << a2 << endl;
		cout << "b2 : " << b2 << endl;
		cout << "a2 - b2 : " << a2 - b2 << endl;
		cout << "a2.get_d() - b2 : " << a2.get_d() - b2 << endl;
		TYPE_SUM res1 = a2.get_d() - b2;
		TYPE_SUM res2 = a2 - b2;
		cout << "res1.get_d() : " << res1.get_d() << endl;
		cout << "res2.get_d() : " << res2.get_d() << endl;

    }
    catch(const std::exception& e)
    {
      std::cerr << "ERREUR : " << e.what() << std::endl;
    }

    return 0;
}
