#include "Matrix.hpp"
#include "Vector.hpp"
#include "RowChecksumMatrix.hpp"
#include "ColumnChecksumMatrix.hpp"
#include "FullChecksumMatrix.hpp"
#include "Calculator.hpp"
#include "Processor.hpp"
#include "ErrorGenerator.hpp"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    try{
    	Calculator<double> calculator;
    	ErrorGenerator<double> generator;
    	Processor<double> proc(calculator);
        /* ---------- allocation statique de mémoire ---------- */
        double LData[2][2] = {{1., 0.}, {1.5, 1.}};
        double UData[2][2] = {{4., 3.}, {0., -1.5}};
        /* ---------------------------------------------------- */
        Matrix<double> L(LData[0], 2, 2);
        Matrix<double> U(UData[0], 2, 2);
        Matrix<double> A(2, 2);

        cout << "L = " << L.toString() << endl;
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

        ColumnChecksumMatrix<double> Uc(U);
        cout << "Uc = " << Uc.toString();

        RowChecksumMatrix<double> Ur(U);
        cout << "Ur = " << Ur.toString();

        ColumnChecksumMatrix<double> Urc(Ur);
        cout << "Urc = " << Urc.toString();

        FullChecksumMatrix<double> Uf(U);
        cout << "Uf = " << Uf.toString() << endl;

        cout << "generateError()" << endl;
        generator.generateError(Uf, 1, 1, Uf.getM(), 1, Uf.getN());
        cout << "Uf = " << Uf.toString();
        cout << "Uf.errorCorrection()" << endl;
        Uf.errorCorrection();
        cout << "Uf = " << Uf.toString() << endl;

        cout << "Uf.getRowSummationVector() = " << Uf.getRowSummationVector().toString() << endl;

        cout << "CLOCKS_PER_SEC :" << CLOCKS_PER_SEC << endl;
    }
    catch(const std::exception& e)
    {
      std::cerr << "ERREUR : " << e.what() << std::endl;
    }

    return 0;
}
