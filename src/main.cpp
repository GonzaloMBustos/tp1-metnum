// #include "matrix.h"
#include "sprse.h"
// #include "fileHandler.h"
#include <iostream>
using namespace std;

void basicTesting()
{
    SprseMatrix sm(2, 2, 0.0001);
    sm.setValue(2, 1, 1);
    sm.setValue(0, 1, 2);
    sm.setValue(0, 2, 1);
    sm.setValue(2, 2, 2);

    cout << "--------------Matriz 1 de 2x2--------------" << endl;
    sm.display();

    SprseMatrix sm2(2, 2, 0.0001);
    sm2.setValue(3, 1, 1);
    sm2.setValue(0, 1, 2);
    sm2.setValue(0, 2, 1);
    sm2.setValue(2, 2, 2);

    cout << "--------------Matriz 2 de 2x2--------------" << endl;
    sm2.display();

    cout << "--------------Matriz 1 * Matriz 2--------------" << endl;
    sm *sm2;
    sm.display();

    cout << "++++++++++++Actually stored values inside matrix+++++++++++++++" << endl;
    sm.getMatrix()[0].display();
    sm.getMatrix()[1].display();

    SprseMatrix sm3b31(3, 3, 0.0001);
    sm3b31.setValue(2, 1, 1);
    sm3b31.setValue(1, 1, 2);
    sm3b31.setValue(0, 1, 3);
    sm3b31.setValue(1, 2, 1);
    sm3b31.setValue(1, 2, 2);
    sm3b31.setValue(3, 2, 3);
    sm3b31.setValue(0, 3, 1);
    sm3b31.setValue(0, 3, 2);
    sm3b31.setValue(1, 3, 3);

    cout << "==============Matriz 1 de 3x3==============" << endl;
    sm3b31.display();

    SprseMatrix sm3b32(3, 3, 0.0001);
    sm3b32.setValue(2, 1, 1);
    sm3b32.setValue(1, 1, 2);
    sm3b32.setValue(0, 1, 3);
    sm3b32.setValue(1, 2, 1);
    sm3b32.setValue(1, 2, 2);
    sm3b32.setValue(3, 2, 3);
    sm3b32.setValue(0, 3, 1);
    sm3b32.setValue(0, 3, 2);
    sm3b32.setValue(1, 3, 3);

    cout << "==============Matriz 2 de 3x3==============" << endl;
    sm3b32.display();

    cout << "--------------Matriz 1 * Matriz 2--------------" << endl;
    sm3b31 *sm3b32;
    sm3b31.display();

    SprseMatrix sm4b41(4, 4, 0.0001);
    sm4b41.setValue(2, 1, 1);
    sm4b41.setValue(1, 1, 2);
    sm4b41.setValue(0, 1, 3);
    sm4b41.setValue(1, 1, 4);
    sm4b41.setValue(1, 2, 1);
    sm4b41.setValue(1, 2, 2);
    sm4b41.setValue(2, 2, 3);
    sm4b41.setValue(3, 2, 4);
    sm4b41.setValue(0, 3, 1);
    sm4b41.setValue(0, 3, 2);
    sm4b41.setValue(1, 3, 3);
    sm4b41.setValue(1, 3, 4);
    sm4b41.setValue(0, 4, 1);
    sm4b41.setValue(3, 4, 2);
    sm4b41.setValue(1, 4, 3);
    sm4b41.setValue(1, 4, 4);

    cout << "==============Matriz 1 de 4x4==============" << endl;
    sm4b41.display();

    SprseMatrix sm4b42(4, 4, 0.0001);
    sm4b42.setValue(2, 1, 1);
    sm4b42.setValue(1, 1, 2);
    sm4b42.setValue(0, 1, 3);
    sm4b42.setValue(2, 1, 4);
    sm4b42.setValue(1, 2, 1);
    sm4b42.setValue(1, 2, 2);
    sm4b42.setValue(3, 2, 3);
    sm4b42.setValue(3, 2, 4);
    sm4b42.setValue(0, 3, 1);
    sm4b42.setValue(4, 3, 2);
    sm4b42.setValue(1, 3, 3);
    sm4b42.setValue(1, 3, 4);
    sm4b42.setValue(0, 4, 1);
    sm4b42.setValue(1, 4, 2);
    sm4b42.setValue(2, 4, 3);
    sm4b42.setValue(1, 4, 4);

    cout << "==============Matriz 2 de 4x4==============" << endl;
    sm4b42.display();

    cout << "--------------Matriz 1 * Matriz 2--------------" << endl;
    sm4b41 *sm4b42;
    sm4b41.display();

    SprseMatrix sm2b2(2, 2, 0.0001);
    sm2b2.setValue(1, 1, 1);
    sm2b2.setValue(0, 1, 2);
    sm2b2.setValue(0, 2, 1);
    sm2b2.setValue(1, 2, 2);

    cout << "--------------Matriz 1 de 2x2--------------" << endl;
    sm2b2.display();

    SprseMatrix sm2b22(2, 2, 0.0001);
    sm2b22.setValue(1, 1, 1);
    sm2b22.setValue(1, 1, 2);
    sm2b22.setValue(1, 2, 1);
    sm2b22.setValue(1, 2, 2);

    cout << "--------------Matriz 2 de 2x2--------------" << endl;
    sm2b22.display();

    cout << "==============Matrix sum===================" << endl;
    sm2b2 + sm2b22;
    sm2b2.display();
}

void EG(SprseMatrix *A, vector<double> &b)
{
    vector<LinkedList> matrix = (*A).getMatrix();
    unsigned int rows = (*A).getRows();
    double e = (*A).getEpsilon();
    for (int i = 0; i < rows; i++)
    {
        double mii = matrix[i][i + 1];
        if (abs(mii) < e)
        {
            cout << "there's a zero in the diagonal" << endl;
            return;
        }
        for (int j = i + 1; j < rows; j++)
        {
            printf("calculating m = %f / %f\n", matrix[j][i + 1], mii);
            matrix[j].display();
            double m = matrix[j][i + 1] / mii;
            for (int k = i; k < rows; k++)
            {
                matrix[j].display();
                double value = matrix[j][k + 1] - m * matrix[i][k + 1];
                printf("m=%f, Setting (%d, %d) = %f\n", m, j + 1, k + 1, value);
                printf("%f = %f - %f * %f\n", value, matrix[j][k + 1], m, matrix[i][k + 1]);
                (*A).setValue(value, j + 1, k + 1);
                cout << "---------------setval------------------" << endl;
                (*A).display();
                cout << "---------------------------------------" << endl;
            }
            b[j] = b[j] - m * b[i];
        }
    }
}

void EGTesting()
{
    // SprseMatrix sm(4, 4, 0.0001);
    // sm.setValue(1, 1, 1);
    // sm.setValue(2, 1, 2);
    // sm.setValue(1, 1, 3);
    // sm.setValue(1, 1, 4);
    // sm.setValue(2, 2, 1);
    // sm.setValue(1, 2, 2);
    // sm.setValue(3, 2, 3);
    // sm.setValue(1, 2, 4);
    // sm.setValue(1, 3, 1);
    // sm.setValue(1, 3, 2);
    // sm.setValue(0, 3, 3);
    // sm.setValue(0, 3, 4);
    // sm.setValue(0, 4, 1);
    // sm.setValue(1, 4, 2);
    // sm.setValue(1, 4, 3);
    // sm.setValue(2, 4, 4);

    // SprseMatrix sm(3, 3, 0.0001);
    // sm.setValue(2, 1, 1);
    // sm.setValue(1, 1, 2);
    // sm.setValue(3, 1, 3);
    // sm.setValue(1, 2, 1);
    // sm.setValue(4, 2, 2);
    // sm.setValue(3, 2, 3);
    // sm.setValue(2, 3, 1);
    // sm.setValue(2, 3, 2);
    // sm.setValue(1, 3, 3);

    SprseMatrix sm(2, 2, 0.0001);
    sm.setValue(2, 1, 1);
    sm.setValue(1, 1, 2);
    sm.setValue(1, 2, 1);
    sm.setValue(4, 2, 2);

    cout << "==============matrix before triangulation==============" << endl;
    sm.display();
    sm.getMatrix()[1].display();

    // vector<LinkedList> matrix = sm.getMatrix();

    // double value = matrix[1][1] - 0.5 * matrix[0][1];
    // cout << "value:" << value << endl;
    // sm.setValue(value, 2, 1);
    // value = matrix[1][2] - 0.5 * matrix[0][2];
    // sm.setValue(value, 2, 2);
    // value = matrix[1][3] - 0.5 * matrix[0][3];
    // sm.setValue(value, 2, 3);

    // sm.display();

    // cout << "==============resulting vector before triangulation==============" << endl;
    vector<double> b(2, 2);
    // cout << "[";
    // for (int i = 0; i < b.size(); i++)
    // {
    //     cout << b[i] << ", ";
    // }
    // cout << "]" << endl;

    EG(&sm, b);

    cout << "==============matrix after triangulation==============" << endl;
    sm.display();

    // cout << "==============resulting vector after triangulation==============" << endl;
    // cout << "[";
    // for (int i = 0; i < b.size(); i++)
    // {
    //     cout << b[i] << ", ";
    // }
    // cout << "]" << endl;
}

// MAIN:
int main(int argc, char *argv[])
{

    // SparseMatrix testMatrix = SparseMatrix(2, 2);
    // testMatrix[0][0] = 1;
    // testMatrix[0][1] = 2;
    // testMatrix[1][0] = 3;
    // testMatrix[1][1] = 4;

    // cout << "Size: " << testMatrix.Columns() << " x " << testMatrix.Rows() << endl;

    // testMatrix.showMatrix(cout);

    // FileHandler myFile = FileHandler("../tests/test_aleatorio_desordenado.txt");
    // SparseMatrix testMatrix2 = myFile.loadMatrix();
    // testMatrix2.showMatrix(cout);

    // basicTesting();

    EGTesting();

    return 0;
}
