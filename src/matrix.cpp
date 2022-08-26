#include <iostream>
#include "matrix.h"

// LO QUE ESTA ABAJO ES PARA QUE FUNCIONEN LOS BRACKETS CON CUALQUIER IMPLEMENTACION INTERNA (Matriz[i][j])
Matrix::MatrixRow::MatrixRow(Matrix * aMatrix, unsigned int row){
    this->ParentMatrix = aMatrix;
    this->row = row;
}

Matrix::MatrixElement Matrix::MatrixRow::operator [](int col){
    return Matrix::MatrixElement(this->ParentMatrix, this->row, col);
}

Matrix::MatrixElement::MatrixElement(Matrix * aMatrix, unsigned int row, unsigned int col){
    this->ParentMatrix = aMatrix;
    this->row = row;
    this->col = col;
}

double Matrix::MatrixElement::getValue(void){
    return this->ParentMatrix->getValue(this->row, this->col);
}

Matrix::MatrixElement& Matrix::MatrixElement::operator=(double aDouble){
    this->ParentMatrix->setValue(this->row, this->col, aDouble);
    return *this;
}

Matrix::MatrixElement& Matrix::MatrixElement::operator+=(double aDouble){
    this->ParentMatrix->setValue(this->row, this->col, this->getValue() + aDouble);
    return *this;
}

Matrix::MatrixElement::operator double(){
    return this->ParentMatrix->getValue(this->row, this->col);
}


// FIN DE COSAS LOCAS

// IMPLEMENTACION ABSTRACTA DE MATRIX (SIN ESTRUCTURA INTERNA DEFINIDA POR AHORA)
Matrix::Matrix(unsigned int n, unsigned int m){
	this->rows=n;
	this->cols=m;
}

unsigned int Matrix::Columns(){
	return this->cols;
}


unsigned int Matrix::Rows(){
	return this->rows;
}


Matrix::MatrixRow Matrix::operator [](int row){
	return MatrixRow(this, row);
}


void Matrix::zero_fill(){
    for (unsigned int i = 0; i < this->rows; i++){
        for (unsigned int j = 0; j < this->cols; j++){
            (*this)[i][j] = 0;
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
			out << (*this)[i][j];
			out << "|";
		}
		out << endl;
	}
	out << endl;
	return out;
}

// FIN MATRIZ ABSTRACTA

GridMatrix::GridMatrix(unsigned int rows, unsigned int cols): Matrix(rows, cols){
    this->initialize();
}

void GridMatrix::initialize(){
    this->grid.resize(this->rows);
    for(unsigned int i=0; i<this->rows; i++){
        this->grid[i].resize(this->cols);        
    }
    this->zero_fill();
}

double GridMatrix::getValue(unsigned int row, unsigned int col){
    return this->grid[row][col];
}

void GridMatrix::setValue(unsigned int row, unsigned int col, double value){
    this->grid[row][col] = value;
}


SparseMatrix::SparseMatrix(unsigned int rows, unsigned int cols): Matrix(rows, cols){
    this->initialize();
}

void SparseMatrix::initialize(){
    return;
}

int SparseMatrix::getItemIndex(unsigned int row, unsigned int col){
    for (unsigned int i=0; i<this->items.size(); i++){
        SparseMatrix::item &currentItem = this->items[i];
        if (currentItem.row == row && currentItem.col == col){
            return i;
        }
    }
    return -1;
}

double SparseMatrix::getValue(unsigned int row, unsigned int col){
    int itemIndex = this->getItemIndex(row, col);
    if (itemIndex < 0){
        return 0;
    }
    return this->items[itemIndex].value;
}

void SparseMatrix::setValue(unsigned int row, unsigned int col, double value){
    int itemIndex = this->getItemIndex(row, col);
    if (itemIndex < 0) {    // ITEM NUEVO
        if (value == 0){    // Quiero agregar un 0, por defecto lo q no esta definido es 0, listo!
            return;
        }
        // Agrego un item diferente de 0
        SparseMatrix::item newValue = {row, col, value};
        this->items.push_back(newValue);
        return;
    }else{                  // ITEM EXISTENTE
        if (value == 0){
            // Quiero agregar un 0, como por defecto todo es 0 entonces no hace falta tener este item, lo borro!
            this->items.erase(this->items.begin()+itemIndex);
            return;
        }
        // Modifico mi item a un valor distinto de 0
        this->items[itemIndex].value = value;
    }
}

