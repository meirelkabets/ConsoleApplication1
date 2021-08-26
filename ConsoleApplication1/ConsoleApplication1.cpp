// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Test.h"
#include "SysConfig.h"
#include <Windows.h>
#include "Vector.h"

class base
{

public:
	base(void) {}
	~base(void) {}


	void Initialize()
	{

	}



};


class der : private base
{

	der(void)  {}
	~der(void) {}

public: 
	void init()
	{
		Initialize();

	}

};


int main()
{
	C3DVector<double> myobject1(12, 13, 14);
	C3DVector<double> myobject2(11, 12, 13);

	double uu = myobject2[2];

	C3DVector<double> cross = myobject1 * myobject2;

	C3DVector<double> myobject4(1, 2, 3);

	myobject4.RPYRotation(DEG2RAD(90.0), DEG2RAD(0.0), DEG2RAD(0.0));

	C3DVector<double> q = myobject2.CrossProduct(myobject1);
	C3DVector<double> q2 = myobject1 - myobject2;
	double q3 = myobject1.Distance(myobject2);


	C3DVector<double> row0(1, 2, 3);
	C3DVector<double> row1(4, 5, 6);
	C3DVector<double> row2(7, 2, 9);

	C3X3Matrix<double> mat1(row0, row1, row2);

	C3X3Matrix<double> mat1z = mat1.Inverse();

	C3X3Matrix<double> mat1z3 = mat1z * mat1;

	C3X3Matrix<double> mat1z11 = mat1.Transpose();

	C3X3Matrix<double> adj = mat1.Adjoint();

	double yy  = mat1.At(2, 2);

	double cc = mat1.Det();

	C3X3Matrix<double> mat2(row0, row1, row2);
	C3X3Matrix<double> mat3 = mat1*mat2;


	int x = 0;
	if (x++ == 1)
	{
		q3 = 2;
	}

	double y = myobject1.GetSize();

    std::cout << "Hello World!\n";

	CSysConfig sysCfg;

	sysCfg.Initialize("SysConfig.ini");

	CTest tst;
	tst.Initialize();

	while (true)
	{
		Sleep(100);
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
