#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Graph.h"

//Durch die Wurzel der Länge der Adjazenzmatrix in der CSV Datei erhält man die Zeilen und Spalten für den 2D Array.
//Ein Check ob es tatsächlich um eine Adjazenzmatrix handelt kann mit einer simplen Überprüfung gemacht werden.
int getGraphDimension(int length)
{
	return sqrt(length);
}

int main()
{
	/*
	+ Auslesen der CSV Datei - Yes
	+ 1D Matrix (ausgelesene CSV) zu 2D Matrix - Yes
	+ Bestimmung der Distanzen und Exzentrizitäten aller Knoten - No
	+ Radius, Durchmesser, Zentrum - No
	+ Artikulationen, Brücken - No
	+ Komponenten - No
	*/
	Graph G;

	std::cout << "GraphY v1.1\n\n";
	std::string CSVmatrix;
	std::ifstream GraphFile("matrix.csv");
	int MatrixSize = 0;
	int m_temp[100] = { 0 };


	if (GraphFile.is_open())
	{
		std::cout << "\32Reading adjacency matrix from csv file...\n\n";
		while (std::getline(GraphFile, CSVmatrix, ','))
		{
			m_temp[MatrixSize] = std::stoi(CSVmatrix);
			MatrixSize++;
			std::cout << CSVmatrix << '\n';
		}

		//1D Matrix(Array) zu 2D Matrix(Array)
		int m_data = 0;
		for (int i = 0; i < getGraphDimension(MatrixSize); i++)
		{
			for (int j = 0; j < getGraphDimension(MatrixSize); j++)
			{
				G.Matrix[i][j] = m_temp[m_data++];
			}
		}

		GraphFile.close();
	}
	else
	{
		std::cout << "Error: Unable to open Graph file";
	}

	//Print Knoten
	printf("Knoten der Adjazenzmatrix: %d\n", getGraphDimension(MatrixSize));


	//Print 1D Temp Matrix
	for (int i = 0; i < MatrixSize; i++)
		printf("1D Temp Matrix[%d]: %d\n", i, m_temp[i]);

	//Print 2D Converted Matrix
	printf("\n\n\nPrinting Matrix:\n");
	for (int i = 0; i < getGraphDimension(MatrixSize); i++)
		for (int j = 0; j < getGraphDimension(MatrixSize); j++)
			printf("2D Converted Matrix[%d][%d]: %d\n", i, j, G.Matrix[i][j]);


	//Spielraum für mich
	int matrix[100][100];
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			std::cin >> matrix[i][j];


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