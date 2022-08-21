#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

using namespace std;


class Matrix {
    private:
		//ESTRUCTURA INTERNA:
    	vector<vector<double>> grid;
    	unsigned int rows;
	    unsigned int cols;
	    
    	//inicializo la matriz con ceros
    	void zero_fill();

	    
    public:
        //Constructor
    	Matrix(unsigned int rows, unsigned int columns);
    	
    	//Obtengo la cantidad de Columnas
	    unsigned int Columns();
	
	    //Obtengo la cantidad de Filas
	    unsigned int Rows();
	    
	    //Muestra la matriz
    	ostream& showMatrix(ostream&);
    	
    	//Operador []
    	vector<double>& operator [](int row);
	
    	
};
#endif /* MATRIX_H */
