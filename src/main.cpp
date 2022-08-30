// #include "matrix.h"
#include "sprse.h"
// #include "fileHandler.h"
#include <iostream>
using namespace std;

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

    return 0;
}
