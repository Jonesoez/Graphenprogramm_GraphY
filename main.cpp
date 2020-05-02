#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
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

	int m2[5][5] =
	{
		0, 1, 1, 1, 0,
		1, 0, 0, 1, 1,
		1, 0, 0, 1, 0,
		1, 1, 1, 0, 0,
		0, 1, 0, 0, 0
	};

	system("pause");
	return 0;
}