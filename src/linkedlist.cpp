#include "linkedlist.h"
#include <iostream>
using namespace std;

// MAIN:
int main(int argc, char *argv[])
{

	LinkedList l(6, 0.0001);
	l.setValue(1, 2);
	l.setValue(1, 3);
	l.setValue(1, 4);
	l.setValue(0, 5);

	// LinkedList l2(6, 0.0001);
	// l2.setValue(2, 1);
	// l2.setValue(1, 3);
	// // l2.setValue(2, 5);
	// l2.setValue(2, 6);
	// l2.multiplyByScalar(-1);

	// l + l2;
	l.display();
	l.setValue(0, 1);
	l.display();
	// cout << "l[5] = " << l[5] << endl;

	return 0;
}