#include <iostream>
#include <cstdlib>

using namespace std;

struct Node
{
	double data;
	unsigned int column;
	Node *next;
};

class LinkedList
{
private:
	Node *head, *tail;
	int maxSize;
	double epsilon;

public:
	LinkedList(int ms, double e)
	{
		head = NULL;
		tail = NULL;
		maxSize = ms;
		epsilon = e;
	}

	void setValue(double d, unsigned int c)
	{
		if (c > maxSize)
		{
			cout << "out of range" << endl;
			return;
		}

		Node *tmp = new Node;
		tmp->data = d;
		tmp->column = c;
		tmp->next = NULL;

		Node *current = head;
		Node *prev = NULL;
		if (current == NULL)
		{
			head = tmp;
			tail = tmp;
		}
		else
		{
			// podria reemplazarlo por un while current != null
			for (int i = 0; i < maxSize; i++)
			{
				if (current->column > tmp->column)
				{
					if (abs(d) < epsilon)
					{
						return;
					}
					if (prev == NULL)
					{
						head = tmp;
						tmp->next = current;
					}
					else
					{
						tmp->next = current;
						prev->next = tmp;
					}
					return;
				}
				else if (current->column == tmp->column)
				{
					if (abs(d) < epsilon)
					{
						remove(current, prev);
					}
					else
					{
						current->data = d;
						return;
					}
				}
				else
				{
					if (current->next == NULL)
					{
						if (abs(d) < epsilon)
						{
							return;
						}
						current->next = tmp;
						tail = tmp;
						return;
					}
					else
					{
						prev = current;
						current = prev->next;
					}
				}
			}
		}
	}

	Node *getHead()
	{
		return head;
	}

	int getMaxSize()
	{
		return maxSize;
	}

	void updateEpsilon(double d)
	{
		epsilon = d;
	}

	void remove(Node *curr, Node *prev)
	{
		if (prev == NULL && curr->next == NULL)
		{
			head = NULL;
			tail = NULL;
		}
		else if (prev == NULL)
		{
			head = curr->next;
		}
		else if (curr->next == NULL)
		{
			prev->next = NULL;
			tail = prev;
		}
		else
		{
			prev->next = curr->next;
		}
		delete curr;
	}

	void display()
	{
		Node *current = head;

		cout << "[";
		while (current != NULL)
		{
			cout << "(data: " << current->data << ", column:" << current->column << ")" << endl;
			current = current->next;
		}
		cout << "]" << endl;

		cout << "Finished printing list" << endl;
	}

	void multiplyByScalar(double s)
	{
		Node *curr = head;
		while (curr != NULL)
		{
			double d = curr->data * s;
			curr->data = d;
			curr = curr->next;
		}
	}

	// Operador +
	void operator+(LinkedList l)
	{
		if (l.getMaxSize() != maxSize)
		{
			cout << "Matrix rows are of different length" << endl;
			return;
		}
		Node *it1 = head;
		Node *it2 = l.getHead();

		while (it2 != NULL)
		{
			if (it1 == NULL || it2->column < it1->column)
			{
				setValue(it2->data, it2->column);
				it2 = it2->next;
			}
			else if (it2->column == it1->column)
			{
				double itemSum = it1->data + it2->data;
				setValue(itemSum, it1->column);
				it1 = it1->next;
				it2 = it2->next;
			}
			else if (it2->column > it1->column)
			{
				it1 = it1->next;
			}
		}
	}

	// este operador tiene la precondicion de que c tiene que estar dentro del rango de columnas posibles
	double operator[](unsigned int c)
	{
		Node *curr = head;
		while (curr != NULL)
		{
			if (curr->column == c)
			{
				return curr->data;
			}
			curr = curr->next;
		}
		return 0;
	}
};