#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "matrix.h"
#include <tuple>
#include <vector>

using namespace std;

class FileHandler
{

private:
	string fileName;

public:
	// Constructor
	FileHandler(string path);

	// Lee del archivo y arma la matriz
	SparseMatrixReloaded loadMatrix();
	vector<tuple<unsigned int, unsigned int>> readContents();
	void writeOutResult(vector<double> result);
};

#endif /* FILEHANDLER_H */
