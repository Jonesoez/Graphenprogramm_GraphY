#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include "Graph.h"

Graph G;



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
	

	std::cout << "GraphY v1.1\n\n";
	std::string CSVmatrix;
	std::ifstream GraphFile("matrix.csv");
	
	int m_temp[100] = { 0 };


	if (GraphFile.is_open())
	{
		std::cout << "\32Reading adjacency matrix from csv file...\n\n";
		while (std::getline(GraphFile, CSVmatrix, ','))
		{
			m_temp[G.MatrixSize] = std::stoi(CSVmatrix);
			G.MatrixSize++;
			//std::cout << CSVmatrix << '\n';
		}

		//1D Matrix(Array) zu 2D Matrix(Array)
		int m_data = 0;
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			for (int j = 0; j < G.getGraphDimension(); j++)
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
	printf("Knoten der Adjazenzmatrix: %d\n", G.getGraphDimension());
	G.Knoten = G.getGraphDimension();


	//Print 2D Converted Matrix
	printf("\n\n\nPrinting static Array Matrix:\n");
	for (int i = 0; i < G.getGraphDimension(); i++)
		for (int j = 0; j < G.getGraphDimension(); j++)
			std::cout << G.Matrix[i][j] << std::setw(5);

	printf("\n\n");

	/*
	int m1[15][15] =
	{
		1,2,3,4,5,
		6,7,8,9,10,
		11,12,13,14,15,
		16,17,18,19,20,
		21,22,23,24,25
	};

	
	G.matrixAdd(m1);

	printf("\n\n\nPrinting ADDED static Array Matrix:\n");
	for (int i = 0; i < G.getGraphDimension(); i++)
		for (int j = 0; j < G.getGraphDimension(); j++)
			printf("2D Converted Matrix[%d][%d]: %d\n", i, j, G.Matrix[i][j]);
	*/

	G.creatDistanzMatrix();
	printf("\n\n\nDISTANZMATRIX:\n");
	for (int i = 0; i < G.getGraphDimension(); i++)
		for (int j = 0; j < G.getGraphDimension(); j++)
			std::cout << G.DistanzMatrix[i][j] << std::setw(5);

	

	printf("\n\n");

	G.calcExzentrizitaet();
	std::cout << "Exzentrizitaeten: \n";
	for(int i = 0; i < G.getGraphDimension(); i++)
		std::cout << G.Exzentrizitaeten[i] << std::endl;

	G.calcDurchmesser();
	std::cout << "Durchmesser: \n";
	std::cout << G.Durchmesser << std::endl;

	G.calcRadius();
	std::cout << "Radius: \n";
	std::cout << G.Radius << std::endl;

	system("pause");
	return 0;
}