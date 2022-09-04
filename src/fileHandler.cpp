#include <fstream>
#include <iostream>
#include "matrix.h"
#include "fileHandler.h"
using namespace std;

FileHandler::FileHandler(string path)
{
    fileName = path;
}

vector<tuple<unsigned int, unsigned int>> FileHandler::readContents()
{
    ifstream myFile(fileName.c_str());
    if (!myFile.is_open())
    {
        cout << "Error leyendo el archivo" << endl;
        exit(0);
    }
    vector<tuple<unsigned int, unsigned int>> contents = vector<tuple<unsigned int, unsigned int>>();
    unsigned int matrixSize, linkCount;
    myFile >> matrixSize >> linkCount;

    contents.emplace_back(matrixSize, linkCount);

    int fromNode, toNode;
    while (myFile >> fromNode >> toNode)
    {
        contents.emplace_back(toNode, fromNode);
    }

    myFile.close();
    return contents;
}

// Lee del archivo y arma la matriz
SparseMatrixReloaded FileHandler::loadMatrix()
{
    ifstream myFile(fileName.c_str());
    if (!myFile.is_open())
    {
        cout << "Error leyendo el archivo" << endl;
        exit(0);
    }
    int matrixSize, linkCount;
    myFile >> matrixSize >> linkCount;

    SparseMatrixReloaded outMatrix = SparseMatrixReloaded(matrixSize, matrixSize, 0.0001);
    int fromNode, toNode;
    while (myFile >> fromNode >> toNode)
    {
        outMatrix[toNode - 1][fromNode - 1] += 1;
    }

    myFile.close();
    return outMatrix;
}

void FileHandler::writeOutResult(vector<double> result)
{
    string outputFile = fileName + ".out";
    ofstream myFile(outputFile);
    for (long unsigned int i = 0; i < result.size(); i++)
    {
        myFile << result[i];
        if (i < result.size() - 1)
        {
            myFile << "\n";
        }
    }

    myFile.close();
}
