#include <fstream>
#include <iostream>
#include "matrix.h"
#include "fileHandler.h"
using namespace std;

FileHandler::FileHandler(string path)
{
    fileName = path;
}

// Lee del archivo y arma la matriz
SparseMatrix FileHandler::loadMatrix()
{
    ifstream myFile(fileName.c_str());
    if (!myFile.is_open())
    {
        cout << "Error leyendo el archivo" << endl;
        exit(0);
    }
    int matrixSize, linkCount;
    myFile >> matrixSize >> linkCount;

    SparseMatrix outMatrix = SparseMatrix(matrixSize, matrixSize);
    int fromNode, toNode;
    while (myFile >> fromNode >> toNode)
    {
        outMatrix[toNode - 1][fromNode - 1] += 1;
    }

    myFile.close();
    return outMatrix;
}
