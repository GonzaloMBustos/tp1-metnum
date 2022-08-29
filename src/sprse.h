#include <iostream>
#include <cstdlib>
#include <vector>
#include "linkedlist.h"

using namespace std;

class SprseMatrix
{
private:
	vector<LinkedList> matrix;
	unsigned int rows;
	unsigned int columns;
	int epsilon;

public:
	// ESTO NO FUNCIONA, HAY QUE ARREGLAR COMO NOS PASAMOS LA MATRIZ
	SprseMatrix(unsigned int r, unsigned int c, int e)
	{
		rows = r;
		columns = c;
		epsilon = e;
		LinkedList l = LinkedList(c, e);
		vector<LinkedList> m(r, l);
		matrix = m;
	}

	void setValue(double value, unsigned int row, unsigned int col)
	{
		matrix[row].setValue(value, col);
	}

	void display()
	{
		for (int i = 0; i < rows; i++)
		{
			LinkedList r = matrix[i];
			r.display();
		}
	}
};