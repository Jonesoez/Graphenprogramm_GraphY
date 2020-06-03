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
	std::cout << "GraphY v1.2\n\n";
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

		//Print Knoten
		printf("Knoten der Adjazenzmatrix: %d\n", G.getGraphDimension());
		G.Knoten = G.getGraphDimension();


		//Print 2D Converted Matrix
		printf("\n\n\nPrinting static Array Matrix:\n");
		for (int i = 0; i < G.getGraphDimension(); i++)
			for (int j = 0; j < G.getGraphDimension(); j++)
				std::cout << G.Matrix[i][j] << std::setw(5);

		printf("\n\n");


		G.creatDistanzMatrix();
		printf("\n\n\nDISTANZMATRIX:\n");
		for (int i = 0; i < G.getGraphDimension(); i++)
			for (int j = 0; j < G.getGraphDimension(); j++)
				std::cout << G.DistanzMatrix[i][j] << std::setw(5);


		printf("\n\n");

		G.calcExzentrizitaet();
		std::cout << "Exzentrizitaeten: \n";
		for (int i = 0; i < G.getGraphDimension(); i++)
			std::cout << G.Exzentrizitaeten[i] << std::endl;


		G.calcDurchmesser();
		std::cout << "Durchmesser: ";
		std::cout << G.Durchmesser << std::endl;

		G.calcRadius();
		std::cout << "Radius: ";
		std::cout << G.Radius << std::endl;

		G.calcZentren();
		std::cout << "Zentren: ";
		std::cout << "An den Knoten: [ ";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			if (G.Zentren[i] != 0)
				std::cout << i + 1 << " ";
		}
		std::cout << "]";


		std::cout << "\n\n" << std::endl;


		GraphFile.close();
	}
	else
	{
		std::cout << "Error: Unable to open Graph file \"matrix.csv\"\n\n";
	}

	system("pause");
	return 0;
}