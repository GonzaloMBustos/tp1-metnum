#include <iostream>
#include <iomanip>
#include "matrix.h"

// LO QUE ESTA ABAJO ES PARA QUE FUNCIONEN LOS BRACKETS CON CUALQUIER IMPLEMENTACION INTERNA (Matriz[i][j])
Matrix::MatrixRow::MatrixRow(Matrix *aMatrix, unsigned int row)
{
    this->ParentMatrix = aMatrix;
    this->row = row;
}

Matrix::MatrixElement Matrix::MatrixRow::operator[](int col)
{
    return Matrix::MatrixElement(this->ParentMatrix, this->row, col);
}

Matrix::MatrixElement::MatrixElement(Matrix *aMatrix, unsigned int row, unsigned int col)
{
    this->ParentMatrix = aMatrix;
    this->row = row-1;
    this->col = col-1;
}

double Matrix::MatrixElement::getValue(void)
{
    return this->ParentMatrix->getValue(this->row, this->col);
}

Matrix::MatrixElement &Matrix::MatrixElement::operator=(double aDouble)
{
    this->ParentMatrix->setValue(this->row, this->col, aDouble);
    return *this;
}

Matrix::MatrixElement &Matrix::MatrixElement::operator+=(double aDouble)
{
    this->ParentMatrix->setValue(this->row, this->col, this->getValue() + aDouble);
    return *this;
}

Matrix::MatrixElement::operator double()
{
    return this->ParentMatrix->getValue(this->row, this->col);
}

// FIN DE COSAS LOCAS

// IMPLEMENTACION ABSTRACTA DE MATRIX (SIN ESTRUCTURA INTERNA DEFINIDA POR AHORA)
Matrix::Matrix(unsigned int n, unsigned int m, double epsilon)
{
    this->rows = n;
    this->cols = m;
    this->epsilon = epsilon;
}

unsigned int Matrix::Columns()
{
    return this->cols;
}

unsigned int Matrix::Rows()
{
    return this->rows;
}

Matrix::MatrixRow Matrix::operator[](int row){
    return MatrixRow(this, row);
}

void Matrix::operator*(Matrix& aMatrix){
    for (unsigned int i = 1; i <= this->rows; i++)
    {
        vector<double> tmp = vector<double>(this->cols, 0);
        for (unsigned int j = 1; j <= this->cols; j++){
            tmp[j-1] = 0;
            for (unsigned int k = 1; k <= this->rows; k++){
                tmp[j-1] += (*this)[i][k] * aMatrix[k][j];
            }
        }
        for (unsigned int j = 1; j <= this->cols; j++){
            (*this)[i][j] = tmp[j-1];
        }
    }
    
}

void Matrix::operator+(Matrix& aMatrix){
    for (unsigned int i = 1; i <= this->rows; i++){
        for (unsigned int j = 1; j <= this->cols; j++){
            (*this)[i][j] += aMatrix[i][j];
        }
    }
}

void Matrix::zero_fill(){
    for (unsigned int i = 1; i <= this->rows; i++)
    {
        for (unsigned int j = 1; j <= this->cols; j++)
        {
            (*this)[i][j] = 0;
        }
    }
}

ostream &Matrix::showMatrix(ostream &out)
{
    for (unsigned int i = 1; i <= this->rows; i++)
    {
        for (unsigned int j = 1; j <= this->cols; j++){
            if (j == 1)
            {
                out << "|";
            }
            out << setfill(' ') << setw(3) << (*this)[i][j];
            out << "|";
        }
        out << endl;
    }
    out << endl;
    return out;
}

// FIN MATRIZ ABSTRACTA

GridMatrix::GridMatrix(unsigned int rows, unsigned int cols, double epsilon) : Matrix(rows, cols, epsilon)
{
    this->initialize();
}

void GridMatrix::initialize()
{
    this->grid.resize(this->rows);
    for (unsigned int i = 0; i < this->rows; i++)
    {
        this->grid[i].resize(this->cols);
    }
    this->zero_fill();
}

double GridMatrix::getValue(unsigned int row, unsigned int col)
{
    return this->grid[row][col];
}

void GridMatrix::setValue(unsigned int row, unsigned int col, double value)
{
    this->grid[row][col] = value;
}

SparseMatrix::SparseMatrix(unsigned int rows, unsigned int cols, double epsilon) : Matrix(rows, cols, epsilon)
{
    this->initialize();
}

void SparseMatrix::initialize()
{
    return;
}

int SparseMatrix::getItemIndex(unsigned int row, unsigned int col)
{
    for (unsigned int i = 0; i < this->items.size(); i++)
    {
        SparseMatrix::item &currentItem = this->items[i];
        if (currentItem.row == row && currentItem.col == col)
        {
            return i;
        }
    }
    return -1;
}

double SparseMatrix::getValue(unsigned int row, unsigned int col)
{
    int itemIndex = this->getItemIndex(row, col);
    if (itemIndex < 0)
    {
        return 0;
    }
    return this->items[itemIndex].value;
}

void SparseMatrix::setValue(unsigned int row, unsigned int col, double value)
{
    int itemIndex = this->getItemIndex(row, col);
    if (itemIndex < 0)
    { // ITEM NUEVO
        if (value == 0)
        { // Quiero agregar un 0, por defecto lo q no esta definido es 0, listo!
            return;
        }
        // Agrego un item diferente de 0
        SparseMatrix::item newValue = {row, col, value};
        this->items.push_back(newValue);
        return;
    }
    else
    { // ITEM EXISTENTE
        if (value == 0)
        {
            // Quiero agregar un 0, como por defecto todo es 0 entonces no hace falta tener este item, lo borro!
            this->items.erase(this->items.begin() + itemIndex);
            return;
        }
        // Modifico mi item a un valor distinto de 0
        this->items[itemIndex].value = value;
    }
}


SparseMatrixReloaded::SparseMatrixReloaded(unsigned int rows, unsigned int cols, double epsilon) : Matrix(rows, cols, epsilon)
{
    this->initialize();
}

void SparseMatrixReloaded::initialize()
{
    this->matrix = vector<list<ListNode>>(this->rows);
}

list<SparseMatrixReloaded::ListNode>::iterator SparseMatrixReloaded::findNodePosition(unsigned int row, unsigned int column){

    for (list<SparseMatrixReloaded::ListNode>::iterator it = this->matrix[row].begin(); it != this->matrix[row].end(); it++){
        if (column <= it->column){
            return it;
        }
    }
    return this->matrix[row].end();
}

double SparseMatrixReloaded::getValue(unsigned int row, unsigned int col)
{
    list<ListNode>::iterator nodePosition = this->findNodePosition(row, col);
    if (nodePosition != this->matrix[row].end() && nodePosition->column == col){
        return nodePosition->data;
    }
    return 0;
}


void SparseMatrixReloaded::setValue(unsigned int row, unsigned int col, double value)
{
    list<ListNode>::iterator nodePosition = this->findNodePosition(row, col);
    bool nodeExists = (nodePosition != this->matrix[row].end() && nodePosition->column == col);

    if (value < this->epsilon){
        if (nodeExists){	// Existe y es 0: Lo borro
            this->matrix[row].erase(nodePosition);
        }
        return;	// No existe y es 0: Chau
    }

    if (!nodeExists){	// No existe: Lo creo ANTES de nodePosition (y nodePosition queda apuntando al nuevo nodo)
        nodePosition = this->matrix[row].emplace(nodePosition, value, col);
    }
    nodePosition->data = value;	//Existe (si o si!): Le asigno el valor (si lo cree recien agrega un MINIMO overhead)
}

void SparseMatrixReloaded::operator+(SparseMatrixReloaded& aMatrix)
{
    for (unsigned int row = 0; row < this->rows; row++){    // Sumamos fila a fila
        list<SparseMatrixReloaded::ListNode>::iterator it1 = this->matrix[row].begin();
        list<SparseMatrixReloaded::ListNode>::iterator it2 = aMatrix.matrix[row].begin();

        while (it1 != this->matrix[row].end() && it2 != aMatrix.matrix[row].end()){     // Mientras obtenga elementos de las filas de ambas matrices..
            if (it1->column > it2->column){     // Matriz 2 contiene un valor que no esta en Matriz 1: lo agrego y avanzo la columna (matriz 2)
                this->matrix[row].emplace(it1, it2->data, it2->column);
                it2++;
            }else if (it1->column < it2->column){   // Matriz 1 contiene un valor que no esta en Matriz 2: no me importa, avanzo la columna (matriz 1)
                it1++;
            }else{
                it1->data += it2->data;     // Ambas matrices tienen un elemento en i,j, lo sumo y modifico la matriz 1, avanzo ambas columnas
                if (it1->data < this->epsilon){
                    it1 = this->matrix[row].erase(it1); // Si el resultado es 0 (segun el epsilon) borro el elemento (matriz 1)
                }else{
                    it1++;
                }
                it2++;
            }
        }
        while (it2 != aMatrix.matrix[row].end()){   // si termine de recorrer la fila de M1 pero quedan elementos de M2 los agrego (porque no estan)
            this->matrix[row].emplace(it1, it2->data, it2->column);
            it2++;
        }
    }
}

SparseMatrixReloaded SparseMatrixReloaded::getTransposedMatrix(){
    // O(max(n, k)) | n = filas, k = elementos no nulos
    SparseMatrixReloaded transposed (this->cols, this->rows, this->epsilon);
    for (unsigned int row = 0; row < this->rows; row++){ 
        for (list<SparseMatrixReloaded::ListNode>::iterator it = this->matrix[row].begin(); it != this->matrix[row].end(); it++){
            transposed.matrix[it->column].emplace_back(it->data, row);  //O(1)
        }
    }
    return transposed;
}

void SparseMatrixReloaded::operator*(SparseMatrixReloaded& aMatrix){
    SparseMatrixReloaded tMatrix = aMatrix.getTransposedMatrix();
    // Multiplico filaI(M1) * filaJ(M2t)
    for (unsigned int i = 0; i < this->rows; i++){ 
        list<SparseMatrixReloaded::ListNode> tmp = list<SparseMatrixReloaded::ListNode>(); // Voy guardando la fila resultante
        for (unsigned int j = 0; j < this->cols; j++){ 
            list<SparseMatrixReloaded::ListNode>::iterator it1 = this->matrix[i].begin();
            list<SparseMatrixReloaded::ListNode>::iterator it2 = tMatrix.matrix[j].begin();
            double partial = 0;
            while (it1 != this->matrix[i].end() && it2 != tMatrix.matrix[j].end()){ // Esto seria la parte eficiente en matrices ralas!
                if (it1->column < it2->column){
                    it1++;
                }else if (it1->column > it2->column){
                    it2++;
                }else{  // M1(ij) != 0 y M2(ij) != 0
                    partial += it1->data * it2->data;
                    if (partial < this->epsilon){   // TODO: ESTO ESTA BIEN??
                        partial = 0;
                    }
                    it1++;
                    it2++;
                }
            }
            if (partial > epsilon){
                tmp.emplace_back(partial, j);
            }
        }
        this->matrix[i] = tmp;    // ( O(N)! Reemplazo la fila de M1 por la fila resultante
    }
}

