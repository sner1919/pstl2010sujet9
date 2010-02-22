#include "Calculator.cpp"
#include "Processor.cpp"
#include "RowChecksumMatrix.cpp"
#include "ColumnChecksumMatrix.cpp"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    try{
    	Processor<double> proc(new Calculator<double>());
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

        cout << "A Faire : implémenter LU()" << endl;
        proc.mult(A, L, U);
        proc.mult(L, A, 0.);
        proc.mult(U, A, 0.);
        proc.LU(L, U, A);
        cout << "A = L * U" << endl;
        cout << "avec A = " << A.toString();
        cout << "=>" << endl;
        cout << "L = " << L.toString();
        cout << "U = " << U.toString() << endl;

        RowChecksumMatrix<double> Ur(U);
        cout << "Ur = " << Ur.toString();
        Ur(1, 2) = 10;
        cout << "Ur(1, 2) = 10" << endl;
        cout << "Ur = " << Ur.toString() << endl;
        cout << "Ur.getRowSummationVector() = " << Ur.getRowSummationVector().toString() << endl;

        ColumnChecksumMatrix<double> Lc(L);
        cout << "Lc = " << Lc.toString();

        ColumnChecksumMatrix<double> Urc(Ur);
        cout << "Urc = " << Urc.toString();
    }
    catch(const std::exception& e)
    {
      std::cerr << "ERREUR : " << e.what() << std::endl;
    }

    return 0;
}
