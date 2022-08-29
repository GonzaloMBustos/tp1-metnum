#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
protected:
    class MatrixElement
    {
    private:
        unsigned int row;
        unsigned int col;
        Matrix *ParentMatrix;

    public:
        MatrixElement(Matrix *aMatrix, unsigned int row, unsigned int col);
        double getValue(void);
        MatrixElement &operator=(double);
        MatrixElement &operator+=(double);
        operator double();
    };
    class MatrixRow
    {
    private:
        unsigned int row;
        Matrix *ParentMatrix;

    public:
        MatrixRow(Matrix *aMatrix, unsigned int row);
        MatrixElement operator[](int col);
    };
    // ESTRUCTURA INTERNA:
    vector<vector<double>> grid;
    unsigned int rows;
    unsigned int cols;

    // inicializo la matriz con ceros
    void zero_fill();

    // inicializo la matriz
    virtual void initialize() = 0;

public:
    // Constructor
    Matrix(unsigned int rows, unsigned int columns);

    virtual double getValue(unsigned int row, unsigned int col) = 0;
    virtual void setValue(unsigned int row, unsigned int col, double value) = 0;

    // Obtengo la cantidad de Columnas
    unsigned int Columns();

    // Obtengo la cantidad de Filas
    unsigned int Rows();

    // Muestra la matriz
    ostream &showMatrix(ostream &);

    // Operador []
    MatrixRow operator[](int row);
};
// IMPLEMENTACION "CLASICA" DE MATRIZ
class GridMatrix : public Matrix
{
protected:
    vector<vector<double>> grid;
    void initialize() override;

public:
    virtual double getValue(unsigned int row, unsigned int col) override;
    virtual void setValue(unsigned int row, unsigned int col, double value) override;
    GridMatrix(unsigned int rows, unsigned int cols);
};

// IMPLEMENTACION PARA MATRICES RALAS, FUNCIONA SIMILAR AL FORMATO DE LOS ARCHIVOS (SOLO GUARDA INFORMACION DE LAS CELDAS OCUPADAS)
// TODO PENSAR COMO IMPLEMENTAR ALGORITMOS MAS EFICIENTES PARA ESTE TIPO DE MATRICES
// TODO PENSAR EN UN TIPO DE ORDENAMIENTO DE LOS VALORES (PARA AGILIZAR LA INSERCION/BUSQUEDA/DELETE)
class SparseMatrix : public Matrix
{
protected:
    struct item
    {
        unsigned int row;
        unsigned int col;
        double value;
    };
    vector<item> items;
    virtual void initialize() override;
    virtual int getItemIndex(unsigned int row, unsigned int col);

public:
    virtual double getValue(unsigned int row, unsigned int col) override;
    virtual void setValue(unsigned int row, unsigned int col, double value) override;
    SparseMatrix(unsigned int rows, unsigned int cols);
};

#endif /* MATRIX_H */