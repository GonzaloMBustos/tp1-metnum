#include <iostream>
#include <iomanip>

#include <cmath>
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
    this->row = row - 1;
    this->col = col - 1;
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

Matrix::Matrix(vector<tuple<unsigned int, unsigned int>> values, double epsilon){
    if (values.size() <= 1){
        return;
    }
    this->rows = get<0>(values[0]);
    this->cols = get<0>(values[0]);
    this->epsilon = epsilon;
    for(unsigned int i = 1; i < values.size(); i++){
        unsigned int row = get<0>(values[i]);
        unsigned int col = get<1>(values[i]);
        (*this)[row][col] += 1;
    }
}

unsigned int Matrix::Columns()
{
    return this->cols;
}

unsigned int Matrix::Rows()
{
    return this->rows;
}

Matrix::MatrixRow Matrix::operator[](int row)
{
    return MatrixRow(this, row);
}

void Matrix::multiplyByScalar(double scalar)
{
    for (unsigned int i = 1; i <= this->rows; i++)
    {
        for (unsigned int j = 1; j <= this->cols; j++)
        {
            MatrixElement mij = (*this)[i][j];
            mij = mij * scalar;
        }
    }
}

void Matrix::operator*(Matrix &aMatrix)
{
    for (unsigned int i = 1; i <= this->rows; i++)
    {
        vector<double> tmp = vector<double>(this->cols, 0);
        for (unsigned int j = 1; j <= this->cols; j++)
        {
            tmp[j - 1] = 0;
            for (unsigned int k = 1; k <= this->rows; k++)
            {
                tmp[j - 1] += (*this)[i][k] * aMatrix[k][j];
            }
        }
        for (unsigned int j = 1; j <= this->cols; j++)
        {
            (*this)[i][j] = tmp[j - 1];
        }
    }
}

void Matrix::operator+(Matrix &aMatrix)
{
    for (unsigned int i = 1; i <= this->rows; i++)
    {
        for (unsigned int j = 1; j <= this->cols; j++)
        {
            (*this)[i][j] += aMatrix[i][j];
        }
    }
}

void Matrix::EG(vector<double> &B)
{
    for (unsigned int i = 1; i <= this->rows; i++)
    {
        double mii = (*this)[i][i];
        if (abs(mii) < this->epsilon)
        {
            cout << "there's a zero in the diagonal" << endl;
            return;
        }
        for (unsigned int j = i + 1; j <= this->rows; j++)
        {
            // printf("calculating m = %f / %f\n", double((*this)[j][i]), mii);
            // this->showMatrix(cout);
            double m = (*this)[j][i] / mii;
            for (unsigned int k = i; k <= this->rows; k++)
            {
                // this->showMatrix(cout);
                double value = (*this)[j][k] - m * (*this)[i][k];
                // printf("m=%f, Setting (%d, %d) = %f\n", m, j, k, value);
                // printf("%f = %f - %f * %f\n", value, double((*this)[j][k]), m, double((*this)[i][k]));
                (*this)[j][k] = value;
                // cout << "---------------setval------------------" << endl;
                // this->showMatrix(cout);
                // cout << "---------------------------------------" << endl;
            }
            B[j - 1] = B[j - 1] - m * B[i - 1];
            if (abs(B[j-1] < this->epsilon)){
                B[j-1] = 0;
            }
        }
    }
}

void Matrix::zero_fill()
{
    for (unsigned int i = 1; i <= this->rows; i++)
    {
        for (unsigned int j = 1; j <= this->cols; j++)
        {
            (*this)[i][j] = 0;
        }
    }
}

vector<double> Matrix::backwardSubstitution(vector<double>& B){
    vector<double> rta = vector<double>(B.size(),0);
    for(unsigned int i = this->rows; i > 0; i--){
        rta[i-1] = B[i-1];
        for(unsigned int j = i+1; j <= this->cols; j++){
            rta[i-1] -= (*this)[i][j] * rta[j-1];
        }
        rta[i-1] = rta[i-1]/(*this)[i][i];
        if (abs(rta[i-1]) < this->epsilon){
            rta[i-1] = 0;
        }
    }
    return rta;
}

ostream &Matrix::showMatrix(ostream &out)
{
    for (unsigned int i = 1; i <= this->rows; i++)
    {
        for (unsigned int j = 1; j <= this->cols; j++)
        {
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

GridMatrix::GridMatrix(vector<tuple<unsigned int, unsigned int>> values, double epsilon): Matrix(values, epsilon){
    if (values.size() <= 1){
        return;
    }
    this->rows = get<0>(values[0]);
    this->cols = get<0>(values[0]);
    this->epsilon = epsilon;
    this->initialize();
    for(unsigned int i = 1; i < values.size(); i++){
        unsigned int row = get<0>(values[i]);
        unsigned int col = get<1>(values[i]);
        (*this)[row][col] += 1;
    }
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

SparseMatrix::SparseMatrix(vector<tuple<unsigned int, unsigned int>> values, double epsilon) : Matrix(values, epsilon){
    return;
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

SparseMatrixReloaded::SparseMatrixReloaded(vector<tuple<unsigned int, unsigned int>> values, double epsilon) : Matrix(0, 0, 0){
    if (values.size() <= 1){
        return;
    }
    this->rows = get<0>(values[0]);
    this->cols = get<0>(values[0]);
    this->epsilon = epsilon;
    this->initialize();
    for(unsigned int i = 1; i < values.size(); i++){
        unsigned int row = get<0>(values[i]);
        unsigned int col = get<1>(values[i]);
        (*this)[row][col] += 1;
    }
}

void SparseMatrixReloaded::initialize()
{
    this->matrix = vector<list<ListNode>>(this->rows);
}

list<SparseMatrixReloaded::ListNode>::iterator SparseMatrixReloaded::findNodePosition(unsigned int row, unsigned int column)
{
    for (list<SparseMatrixReloaded::ListNode>::iterator it = this->matrix[row].begin(); it != this->matrix[row].end(); it++)
    {
        if (column <= it->column)
        {
            return it;
        }
    }
    return this->matrix[row].end();
}

double SparseMatrixReloaded::getValue(unsigned int row, unsigned int col)
{
    list<ListNode>::iterator nodePosition = this->findNodePosition(row, col);
    if (nodePosition != this->matrix[row].end() && nodePosition->column == col)
    {
        return nodePosition->data;
    }
    return 0;
}

void SparseMatrixReloaded::setValue(unsigned int row, unsigned int col, double value)
{
    list<ListNode>::iterator nodePosition = this->findNodePosition(row, col);
    bool nodeExists = (nodePosition != this->matrix[row].end() && nodePosition->column == col);

    if (abs(value) < this->epsilon)
    {
        if (nodeExists)
        { // Existe y es 0: Lo borro
            this->matrix[row].erase(nodePosition);
        }
        return; // No existe y es 0: Chau
    }

    if (!nodeExists)
    { // No existe: Lo creo ANTES de nodePosition (y nodePosition queda apuntando al nuevo nodo)
        nodePosition = this->matrix[row].emplace(nodePosition, value, col);
    }
    nodePosition->data = value; // Existe (si o si!): Le asigno el valor (si lo cree recien agrega un MINIMO overhead)
}

void SparseMatrixReloaded::multiplyByScalar(double scalar)
{
    for (unsigned int row = 0; row < this->rows; row++)
    {
        list<SparseMatrixReloaded::ListNode>::iterator it = this->matrix[row].begin();
        while (it != this->matrix[row].end())
        {
            it->data *= scalar;
            if (abs(it->data) < this->epsilon)
            {
                it = this->matrix[row].erase(it);
            }
            else
            {
                it++;
            }
        }
    }
}

void SparseMatrixReloaded::operator+(SparseMatrixReloaded &aMatrix)
{
    for (unsigned int row = 0; row < this->rows; row++)
    { // Sumamos fila a fila
        list<SparseMatrixReloaded::ListNode>::iterator it1 = this->matrix[row].begin();
        list<SparseMatrixReloaded::ListNode>::iterator it2 = aMatrix.matrix[row].begin();

        while (it1 != this->matrix[row].end() && it2 != aMatrix.matrix[row].end())
        { // Mientras obtenga elementos de las filas de ambas matrices..
            if (it1->column > it2->column)
            { // Matriz 2 contiene un valor que no esta en Matriz 1: lo agrego y avanzo la columna (matriz 2)
                this->matrix[row].emplace(it1, it2->data, it2->column);
                it2++;
            }
            else if (it1->column < it2->column)
            { // Matriz 1 contiene un valor que no esta en Matriz 2: no me importa, avanzo la columna (matriz 1)
                it1++;
            }
            else
            {
                it1->data += it2->data; // Ambas matrices tienen un elemento en i,j, lo sumo y modifico la matriz 1, avanzo ambas columnas
                if (abs(it1->data) < this->epsilon)
                {
                    it1 = this->matrix[row].erase(it1); // Si el resultado es 0 (segun el epsilon) borro el elemento (matriz 1)
                }
                else
                {
                    it1++;
                }
                it2++;
            }
        }
        while (it2 != aMatrix.matrix[row].end())
        { // si termine de recorrer la fila de M1 pero quedan elementos de M2 los agrego (porque no estan)
            this->matrix[row].emplace(it1, it2->data, it2->column);
            it2++;
        }
    }
}

SparseMatrixReloaded SparseMatrixReloaded::getTransposedMatrix()
{
    // O(max(n, k)) | n = filas, k = elementos no nulos
    SparseMatrixReloaded transposed(this->cols, this->rows, this->epsilon);
    for (unsigned int row = 0; row < this->rows; row++)
    {
        for (list<SparseMatrixReloaded::ListNode>::iterator it = this->matrix[row].begin(); it != this->matrix[row].end(); it++)
        {
            transposed.matrix[it->column].emplace_back(it->data, row); // O(1)
        }
    }
    return transposed;
}

void SparseMatrixReloaded::operator*(SparseMatrixReloaded &aMatrix)
{
    SparseMatrixReloaded tMatrix = aMatrix.getTransposedMatrix();
    // Multiplico filaI(M1) * filaJ(M2t)
    for (unsigned int i = 0; i < this->rows; i++)
    {
        list<SparseMatrixReloaded::ListNode> tmp = list<SparseMatrixReloaded::ListNode>(); // Voy guardando la fila resultante
        for (unsigned int j = 0; j < this->cols; j++)
        {
            list<SparseMatrixReloaded::ListNode>::iterator it1 = this->matrix[i].begin();
            list<SparseMatrixReloaded::ListNode>::iterator it2 = tMatrix.matrix[j].begin();
            double partial = 0;
            while (it1 != this->matrix[i].end() && it2 != tMatrix.matrix[j].end())
            { // Esto seria la parte eficiente en matrices ralas!
                if (it1->column < it2->column)
                {
                    it1++;
                }
                else if (it1->column > it2->column)
                {
                    it2++;
                }
                else
                { // M1(ij) != 0 y M2(ij) != 0
                    partial += it1->data * it2->data;
                    if (abs(partial) < this->epsilon)
                    { // TODO: ESTO ESTA BIEN??
                        partial = 0;
                    }
                    it1++;
                    it2++;
                }
            }
            if (abs(partial) > epsilon)
            {
                tmp.emplace_back(partial, j);
            }
        }
        this->matrix[i] = tmp; // ( O(N)! Reemplazo la fila de M1 por la fila resultante
    }
}

void SparseMatrixReloaded::EG(vector<double> &B)
{
    for (unsigned int i = 0; i < this->rows; i++)
    {
        list<SparseMatrixReloaded::ListNode>::iterator miiIt = this->findNodePosition(i, i);
        if (miiIt == this->matrix[i].end() || miiIt->column != i) // No lo encontro => es 0
        {
            cout << "there's a zero in the diagonal" << endl;
            return;
        }
        double mii = miiIt->data;
        for (unsigned int j = i + 1; j < this->rows; j++)
        {
            list<SparseMatrixReloaded::ListNode>::iterator mjxIt = this->findNodePosition(j, i);
            list<SparseMatrixReloaded::ListNode>::iterator mixIt = miiIt;
            if (mjxIt == this->matrix[j].end() || mjxIt->column != i)
            { // Ya es 0 => 0/mii = 0 => filaJ - 0 * filaI = filaJ
                continue;
            }

            double m = mjxIt->data / mii;
            if (abs(m) < this->epsilon)
            { // m = 0, mismo razonamiento q arriba
                continue;
            }

            while (mixIt != this->matrix[i].end() && mjxIt != this->matrix[j].end())
            {
                if (mjxIt->column < mixIt->column)
                { // Si llego aca es porque mix = 0 => mjx = mjx - m * 0 = mjx, avanzo mjx
                    mjxIt++;
                    continue;
                }
                if (mjxIt->column > mixIt->column)
                { // Si llego aca, entonces mjx = 0 agrego un nuevo nodo en 0 (temporalmente en 0, mirar abajo!)
                    mjxIt = this->matrix[j].emplace(mjxIt, 0, mixIt->column);
                }
                double value = mjxIt->data - m * mixIt->data;
                if (abs(value) <= this->epsilon)
                { // Si el nuevo valor es 0 lo borro
                    mjxIt = this->matrix[j].erase(mjxIt);
                }
                else
                {
                    mjxIt->data = value; // Asigno el nuevo valor (mirar aca!)
                    mjxIt++;
                }
                mixIt++;
            }
            while (mixIt != this->matrix[i].end())
            { // Si llego aca es porque todos los demas mjx son 0 => mjx = 0 - m * mix
                double value = 0 - m * mixIt->data;
                if (abs(value) > this->epsilon)
                { // Siempre tengo que agregar un nodo al final (porque mjx es 0 y mix va en orden creciente)
                    this->matrix[j].emplace_back(value, mixIt->column);
                }
                mixIt++;
            }
            B[j] = B[j] - m * B[i];
        }
    }
}

vector<double> SparseMatrixReloaded::backwardSubstitution(vector<double>& B){
    vector<double> rta = vector<double>(B.size(),0);
    for(unsigned int i = this->rows; i-- > 0;){ //Chequea q i > 0, luego decrementa antes de entrar al loop (los unsigned no pueden ser < 0!)
        rta[i] = B[i];
        list<SparseMatrixReloaded::ListNode>::iterator it = this->findNodePosition(i,i);
        double mii = it->data;
        for(unsigned int j = i+1; j < this->cols && it != this->matrix[i].end();){
            if(it->column < j){
                it++;
                continue;
            }
            if (it->column == j){
                rta[i] -= it->data * rta[j];
                it++;
            }
            j++;
        }
        rta[i] = rta[i]/mii;
        if (abs(rta[i]) < this->epsilon){
            rta[i] = 0;
        }
    }
    return rta;
}


