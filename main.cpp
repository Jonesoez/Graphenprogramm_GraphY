#include <stdio.h>
#include <iostream>
#include "Graph.h"



int main() 
{
	//tests
	g.Matrix2D[0][0] = 2;
	g.Matrix2D[0][1] = 2;
	g.Matrix2D[1][0] = 1000;
	g.Matrix2D[1][1] = 1000;


	int arr[2][2];
	arr[0][0] = 2;
	arr[0][1] = 2;
	arr[1][0] = 2;
	arr[1][1] = 9;

	matrixAdd(arr);
	std::cout << "Addition result in [1][1] ";
	std::cout << g.Matrix2D[1][1];
	std::cout << "\n\n";

	matrixMultiply(arr);
	std::cout << "Multiplication result [1][1] ";
	std::cout << g.Matrix2D[1][1];
	std::cout << "\n\n";

	system("pause");
	return 0;
}