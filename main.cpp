#include <stdio.h>
#include <iostream>
#include "Graph.h"


//i don't like this but bear with me, its just for testing
const int MAX_GRAPHEN_GROESSE = 20;
const int MIN_GRAPHEN_GROESSE = 1;

int KnotenEingabe = 2;
int KantenEingabe = 2;
Graph g;

void matrixAdd(int matrix[2][2])
{
	for (int i = 0; i < KnotenEingabe; i++)
	{
		for (int j = 0; j < KnotenEingabe; j++)
		{
			g.Matrix2D[i][j] += matrix[i][j];
		}
	}
}

void matrixMultiply(int matrix[2][2])
{
	for (int i = 0; i < KnotenEingabe; i++)
	{
		for (int j = 0; j < KnotenEingabe; j++)
		{
			g.Matrix2D[i][j] *= matrix[i][j];
		}
	}
}

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