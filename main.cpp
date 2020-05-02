#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Graph.h"


int main()
{
	/*
	immer noch am testen mit matrizen, noch nichts fertig bis auf das auslesen der csv datei in eine 1d matrix
	die konvertierung zu einer 2d matrix steht noch offen
	aber wenn das mal geschafft ist, wird der rest einfach zu implementieren sein
	*/
	Graph G;

	std::cout << "GraphY v1.0\n\n";
	std::string CSVmatrix;
	std::ifstream GraphFile("matrix.csv");
	int MatrixSize = 0;
	int row = 0;
	int m_temp[100] = { 0 };

	if (GraphFile.is_open())
	{
		while (std::getline(GraphFile, CSVmatrix, ','))
		{
			MatrixSize++;
			std::cout << CSVmatrix << '\n';

			//graph mit 5 fixem knotengrad
			if (MatrixSize % 5 == 0)
				row++;

			for(int cols = 0; cols < 5; cols++)
				G.Matrix[row][cols] = std::stoi(CSVmatrix);
		}
		GraphFile.close();
	}
	else
	{
		std::cout << "Error: Unable to open Graph file";
	}


	printf("\n\n\nPrinting Matrix:\n");
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			printf("Matrix[%d][%d]: %d\n", i, j, G.Matrix[i][j]);


	//Input a Matrix with fixed size;
	int matrix[100][100];
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			std::cin >> matrix[i][j];


	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::cout << "Matrix: ";
			std::cout << matrix[i][j] << std::endl;
		}
	}
	int m1[5][5] =
	{
		0, 1, 1, 1, 0,
		1, 0, 0, 1, 1,
		1, 0, 0, 1, 0,
		1, 1, 1, 0, 0,
		0, 1, 0, 0, 0
	};

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