#include <iostream>
#include "matrix.h"

//TODO: ESTA MATRIZ NO ES EFICIENTE CON TODOS LOS CEROS QUE VAMOS A TENER (PENSAR USAR MATRIZ DE ADYACENCIA??, TIENE Q PODER MULTIPLICARSE EN WxD)
Matrix::Matrix(unsigned int n, unsigned int m){
	this->rows=n;
	this->cols=m;

	this->grid.resize(n);
	for(unsigned int i=0; i<n; i++){
		this->grid[i].resize(m);	
	}
	this->zero_fill();
}

unsigned int Matrix::Columns(){
	return this->cols;
}


unsigned int Matrix::Rows(){
	return this->rows;
}


vector<double>& Matrix::operator [](int row){
	return this->grid[row];
}

void Matrix::zero_fill(){
    for (unsigned int i = 0; i < this->rows; i++){
        for (unsigned int j = 0; j < this->cols; j++){
            this->grid[i][j] = 0;
        }
    }
}


ostream& Matrix::showMatrix(ostream& out){
	for (unsigned int i = 0; i < this->rows; i++)
	{
		for (unsigned int j = 0; j < this->cols; j++)
		{
		    if (j == 0){
		        out << "|";
		    }
			out << this->grid[i][j];
			out << "|";
		}
		out << endl;
	}
	out << endl;
	return out;
}

