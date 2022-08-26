#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "matrix.h"


using namespace std;


class FileHandler {

    private:
	    string fileName;

    public:

	    //Constructor
	    FileHandler (string path);
	
	    //Lee del archivo y arma la matriz
	    SparseMatrix loadMatrix();
};

#endif /* FILEHANDLER_H */
