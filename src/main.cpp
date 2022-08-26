#include "matrix.h"
#include "fileHandler.h"
#include <iostream>
using namespace std;

//MAIN:
int main(int argc, char* argv[]) {

    SparseMatrix testMatrix = SparseMatrix(2,2);
    testMatrix[0][0] = 1;
    testMatrix[0][1] = 2;
    testMatrix[1][0] = 3;
    testMatrix[1][1] = 4;
    
    cout << "Size: " << testMatrix.Columns() << " x " <<  testMatrix.Rows() << endl;
    
    testMatrix.showMatrix(cout);

    FileHandler myFile = FileHandler("../tests/test_aleatorio_desordenado.txt");
    SparseMatrix testMatrix2 = myFile.loadMatrix();
    testMatrix2.showMatrix(cout);
}
