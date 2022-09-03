#include "matrix.h"
#include "fileHandler.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

void basicTesting()
{
    SparseMatrixReloaded sm(2, 2, 0.0001);

    sm[1][1] = 2;
    sm[1][2] = 0;
    sm[2][1] = 0;
    sm[2][2] = 2;

    cout << "--------------Matriz 1 de 2x2--------------" << endl;
    sm.showMatrix(cout);

    SparseMatrixReloaded sm2(2, 2, 0.0001);
    sm2[1][1] = 3;
    sm2[1][2] = 0;
    sm2[2][1] = 0;
    sm2[2][2] = 2;

    cout << "--------------Matriz 2 de 2x2--------------" << endl;
    sm2.showMatrix(cout);

    cout << "--------------Matriz 1 * Matriz 2--------------" << endl;
    sm *sm2;

    sm.showMatrix(cout);

    SparseMatrixReloaded sm3b31(3, 3, 0.0001);
    sm3b31[1][1] = 2;
    sm3b31[1][2] = 1;
    sm3b31[1][3] = 0;
    sm3b31[2][1] = 1;
    sm3b31[2][2] = 1;
    sm3b31[2][3] = 3;
    sm3b31[3][1] = 0;
    sm3b31[3][2] = 0;
    sm3b31[3][3] = 1;

    cout << "==============Matriz 1 de 3x3==============" << endl;
    sm3b31.showMatrix(cout);
    ;

    SparseMatrixReloaded sm3b32(3, 3, 0.0001);
    sm3b32[1][1] = 2;
    sm3b32[1][2] = 1;
    sm3b32[1][3] = 0;
    sm3b32[2][1] = 1;
    sm3b32[2][2] = 1;
    sm3b32[2][3] = 3;
    sm3b32[3][1] = 0;
    sm3b32[3][2] = 0;
    sm3b32[3][3] = 1;

    cout << "==============Matriz 2 de 3x3==============" << endl;
    sm3b32.showMatrix(cout);
    ;

    cout << "--------------Matriz 1 * Matriz 2--------------" << endl;
    sm3b31 *sm3b32;
    sm3b31.showMatrix(cout);

    SparseMatrixReloaded sm4b41(4, 4, 0.0001);
    sm4b41[1][1] = 2;
    sm4b41[1][2] = 1;
    sm4b41[1][3] = 0;
    sm4b41[1][4] = 1;
    sm4b41[2][1] = 1;
    sm4b41[2][2] = 1;
    sm4b41[2][3] = 2;
    sm4b41[2][4] = 3;
    sm4b41[3][1] = 0;
    sm4b41[3][2] = 0;
    sm4b41[3][3] = 1;
    sm4b41[3][4] = 1;
    sm4b41[4][1] = 1;
    sm4b41[4][2] = 0;
    sm4b41[4][3] = 3;
    sm4b41[4][4] = 1;

    cout << "==============Matriz 1 de 4x4==============" << endl;
    sm4b41.showMatrix(cout);

    SparseMatrixReloaded sm4b42(4, 4, 0.0001);
    sm4b42[1][1] = 2;
    sm4b42[1][2] = 1;
    sm4b42[1][3] = 0;
    sm4b42[1][4] = 2;
    sm4b42[2][1] = 1;
    sm4b42[2][2] = 1;
    sm4b42[2][3] = 3;
    sm4b42[2][4] = 3;
    sm4b42[3][1] = 0;
    sm4b42[3][2] = 4;
    sm4b42[3][3] = 1;
    sm4b42[3][4] = 1;
    sm4b42[4][1] = 0;
    sm4b42[4][2] = 1;
    sm4b42[4][3] = 2;
    sm4b42[4][4] = 1;

    cout << "==============Matriz 2 de 4x4==============" << endl;
    sm4b42.showMatrix(cout);

    cout << "--------------Matriz 1 * Matriz 2--------------" << endl;
    sm4b41 *sm4b42;
    sm4b41.showMatrix(cout);
    // vector<double> b = {0,0,0,0};
    // sm4b41.EG(b);

    SparseMatrixReloaded sm2b2(2, 2, 0.0001);
    sm2b2[1][1] = 1;
    sm2b2[1][2] = 0;
    sm2b2[2][1] = 0;
    sm2b2[2][2] = 1;

    cout << "--------------Matriz 1 de 2x2--------------" << endl;
    sm2b2.showMatrix(cout);

    SparseMatrixReloaded sm2b22(2, 2, 0.0001);
    sm2b22[1][1] = 2;
    sm2b22[1][2] = 1;
    sm2b22[2][1] = 1;
    sm2b22[2][2] = 4;

    cout << "--------------Matriz 2 de 2x2--------------" << endl;
    sm2b22.showMatrix(cout);

    vector<double> b = {0, 0};
    sm2b22.EG(b);
    sm2b22.showMatrix(cout);

    cout << "==============Matrix sum===================" << endl;
    sm2b2 + sm2b22;
    sm2b2.showMatrix(cout);

    cout << "==============Matriz de 4x4===================" << endl;
    sm4b42[1][1] = 1;
    sm4b42[1][2] = 2;
    sm4b42[1][3] = 1;
    sm4b42[1][4] = -1;
    sm4b42[2][1] = 3;
    sm4b42[2][2] = 2;
    sm4b42[2][3] = 4;
    sm4b42[2][4] = 4;
    sm4b42[3][1] = 4;
    sm4b42[3][2] = 4;
    sm4b42[3][3] = 3;
    sm4b42[3][4] = 4;
    sm4b42[4][1] = 2;
    sm4b42[4][2] = 0;
    sm4b42[4][3] = 1;
    sm4b42[4][4] = 5;
    sm4b42.showMatrix(cout);

    vector<double> b2 = {5, 16, 22, 15};
    cout << "============== B original ===================" << endl;
    cout << "[" << b2[0] << ", " << b2[1] << ", " << b2[2] << ", " << b2[3] << "]" << endl;
    cout << "==============EG===================" << endl;
    sm4b42.EG(b2);
    sm4b42.showMatrix(cout);
    cout << "============== B post EG ===================" << endl;
    cout << "[" << b2[0] << ", " << b2[1] << ", " << b2[2] << ", " << b2[3] << "]" << endl;
    cout << "==============BackSubst===================" << endl;
    vector<double> rta = sm4b42.backwardSubstitution(b2);
    cout << "[" << rta[0] << ", " << rta[1] << ", " << rta[2] << ", " << rta[3] << "]" << endl;

    cout << "==============Multiply by scalar===================" << endl;
    sm4b42.multiplyByScalar(2);
    sm4b42.showMatrix(cout);
}

SparseMatrixReloaded buildIdentity(unsigned int n)
{
    SparseMatrixReloaded identity(n, n, 0.0001);
    for (unsigned int i = 0; i < n; i++)
    {
        identity.setValue(i, i, 1);
    }
    return identity;
}

SparseMatrixReloaded buildD(SparseMatrixReloaded W)
{
    unsigned int n = W.Columns();
    SparseMatrixReloaded D(n, n, 0.0001);
    vector<double> cjs(n, 0);
    for (unsigned int j = 0; j < n; j++)
    {
        for (unsigned int i = 0; i < n; i++)
        {
            cjs[j] += W.getValue(i, j);
        }
    }
    for (unsigned int i = 0; i < n; i++)
    {
        if (abs(cjs[i]) > W.Epsilon())
        {
            D.setValue(i, i, (1 / cjs[i]));
        }
    }
    return D;
}

vector<double> PageRank(SparseMatrixReloaded I, SparseMatrixReloaded W, SparseMatrixReloaded D, double p, vector<double> e)
{
    W *D;
    W.multiplyByScalar((-1 * p));
    W + I;
    W.EG(e);
    vector<double> x = W.backwardSubstitution(e);
    return x;
}

void NormalizeResult(vector<double> *x)
{
    double sum = 0;
    for (int i = 0; i < (*x).size(); i++)
    {
        sum += (*x)[i];
    }
    for (int i = 0; i < (*x).size(); i++)
    {
        (*x)[i] = (*x)[i] / sum;
    }
}

// MAIN:
int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        cout << argc << endl;
        basicTesting();
        cout << "Parametros invalido (especificar 'p' y archivo de entrada), por lo tanto se corrieron tests de debug";
        return 0;
    }

    double p = atof(argv[2]);
    cout << "P = " << p << endl;
    // SparseMatrix testMatrix = SparseMatrix(2, 2);
    // testMatrix[0][0] = 1;
    // testMatrix[0][1] = 2;
    // testMatrix[1][0] = 3;
    // testMatrix[1][1] = 4;

    // cout << "Size: " << testMatrix.Columns() << " x " << testMatrix.Rows() << endl;

    // testMatrix.showMatrix(cout);
    cout << "Archivo: " << argv[1] << endl;
    FileHandler myFile = FileHandler(argv[1]);

    cout << "===== Matriz Input ====" << endl;
    vector<tuple<unsigned int, unsigned int>> contents = myFile.readContents();
    SparseMatrixReloaded W(contents, 0.0001);
    W.showMatrix(cout);

    cout << "===== Matriz Identidad ====" << endl;
    SparseMatrixReloaded identity = buildIdentity(get<0>(contents[0]));
    identity.showMatrix(cout);

    cout << "===== Matriz D ====" << endl;
    SparseMatrixReloaded D = buildD(W);
    D.showMatrix(cout);

    vector<double> e(get<0>(contents[0]), 1);

    vector<double> res = PageRank(identity, W, D, p, e);
    cout << "===== PageRank result ====" << endl;
    cout << "[";
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << ", ";
    }
    cout << "]" << endl;

    NormalizeResult(&res);
    cout << "===== Normalized result ====" << endl;
    cout << "[";
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << ", ";
    }
    cout << "]" << endl;

    return 0;
}
