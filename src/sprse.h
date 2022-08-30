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
	// PRECOND: R == C
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
		if (row > rows || col > columns)
		{
			cout << "row or column out of matrix range" << endl;
			return;
		}

		matrix[row - 1].setValue(value, col);
	}

	void display()
	{
		for (int i = 0; i < rows; i++)
		{
			LinkedList r = matrix[i];
			cout << "[";
			for (int col = 0; col < columns; col++)
			{
				if (col == columns - 1)
				{
					cout << r[col + 1];
				}
				else
				{
					cout << r[col + 1] << ", ";
				}
			}
			cout << "]" << endl;
		}
	}

	unsigned int getRows()
	{
		return rows;
	}

	vector<LinkedList> getMatrix()
	{
		return matrix;
	}

	void operator*(SprseMatrix m2)
	{
		if (columns != m2.getRows())
		{
			return;
		}
		vector<LinkedList> matrix2 = m2.getMatrix();
		for (int row = 0; row < rows; row++)
		{
			// we use the vector to store the result of all positions of the current row
			// and avoid modifying the row before internal product is done
			vector<double> res(columns, 0);
			for (int col = 0; col < columns; col++)
			{
				double sum = 0;
				for (int elem = 0; elem < rows; elem++)
				{
					sum += matrix[row][elem + 1] * matrix2[elem][col + 1];
				}
				res[col] = sum;
			}
			for (int i = 0; i < columns; i++)
			{
				setValue(res[i], row + 1, i + 1);
			}
		}
	}
};