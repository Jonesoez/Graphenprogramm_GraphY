#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Graph.h"


//unicode character fuer unendlich ist \u221E

Graph G;

int main()
{
	std::cout << "GraphY v1.2\n\n";
	std::string CSVmatrix;
	std::string filename;
	std::string outputfilename = "graph_berechnet.txt";

	std::cout << "Please choose your .csv file: ";
	std::getline(std::cin, filename);

	std::ifstream GraphFile(filename);
	std::ofstream OutputFile(outputfilename);

	int m_temp[100] = { 0 };

	if (GraphFile.is_open())
	{
		std::cout << "Reading adjacency matrix from csv file...\n\n";
		while (std::getline(GraphFile, CSVmatrix, ','))
		{
			m_temp[G.MatrixSize] = std::stoi(CSVmatrix);
			G.MatrixInLines[G.MatrixSize] = std::stoi(CSVmatrix);
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
		OutputFile << "Knoten: " << G.Knoten << std::endl;


		//Print 2D Converted Matrix
		printf("\n\n\nAdjazenzmatrix:\n");
		OutputFile << "\nAdjazenzmatrix: \n";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			for (int j = 0; j < G.getGraphDimension(); j++)
			{
				std::cout << G.Matrix[i][j] << std::setw(5);
				OutputFile << G.Matrix[i][j] << "\t";
			}
			OutputFile << std::endl;
		}
		OutputFile << std::endl;
				

		printf("\n\n");


		G.creatDistanzMatrix();
		printf("\n\n\nDistanzmatrix:\n");
		OutputFile << "Distanzmatrix: \n";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			for (int j = 0; j < G.getGraphDimension(); j++)
			{
				if (G.checkInfinity(G.DistanzMatrix[i][j]))
				{
					OutputFile << "~" << "\t";
					std::cout << "~" << std::setw(5);
				}
				else
				{
					std::cout << G.DistanzMatrix[i][j] << std::setw(5);
					OutputFile << G.DistanzMatrix[i][j] << "\t";
				}
					
			}
			OutputFile << std::endl;
		}
		OutputFile << std::endl;
	
				


		printf("\n\n");

		G.calcExzentrizitaet();
		std::cout << "Exzentrizitäten: \n";
		OutputFile << "Exzentrizitäten: [ ";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			if (G.checkInfinity(G.Exzentrizitaeten[i]))
			{
				OutputFile << "~ ";
				std::cout << "~ " << std::endl;
			}
			else
			{
				std::cout << G.Exzentrizitaeten[i] << std::endl;
				OutputFile << G.Exzentrizitaeten[i] << " ";
			}
		}
		OutputFile << "]" << std::endl;


		G.calcDurchmesser();
		if (G.checkInfinity(G.Durchmesser))
		{
			OutputFile << "Durchmesser: kein Durchmesser" << std::endl;
			std::cout << "Durchmesser: kein Durchmesser" << std::endl;
		}
		else
		{
			std::cout << "Durchmesser: " << G.Durchmesser << std::endl;
			OutputFile << "Durchmesser: " << G.Durchmesser << std::endl;
		}

		G.calcRadius();
		if (G.checkInfinity(G.Radius))
		{
			OutputFile << "Radius: kein Radius" << std::endl;
			std::cout << "Radius: kein Radius" << std::endl;
		}
		else
		{
			std::cout << "Radius: " << G.Radius << std::endl;
			OutputFile << "Radius: " << G.Radius << std::endl;
		}



		G.calcZentren();
		std::cout << "Zentren: An den Knoten: [ ";
		OutputFile << "Zentren: An den Knoten: [ ";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			//alle knoten zum zentrum werden
			if (G.checkInfinity(G.Zentren[i]))
			{
				std::cout << "kein Zentrum ";
				OutputFile << "kein Zentrum ";
				break;
			}
			else if (G.Zentren[i] != 0)
			{
				std::cout << i + 1 << " ";
				OutputFile << i + 1 << " ";
			}
		}
		std::cout << "]";
		OutputFile << "]" << std::endl;

		
		std::cout << "\n";
		G.createWegMatrix();
		std::cout << "WegMatrix: \n\n";
		OutputFile << "\nWegmatrix: \n";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			for (int j = 0; j < G.getGraphDimension(); j++)
			{
				std::cout << G.WegMatrix[i][j] << std::setw(5);
				OutputFile << G.WegMatrix[i][j] << "\t";
			}
			OutputFile << std::endl;
		}
		OutputFile << std::endl;
		
		std::cout << "\n\n";

		G.calcKomponenten();
		std::cout << "Komponenten: ";
		std::cout << G.Komponenten << std::endl;
		OutputFile << "Komponenten: " << G.Komponenten << std::endl;

		
		/* 
		std::cout << "\n\n\Komponenten Zeilen: \n";
		for (int i = 0; i < G.getGraphDimension(); i++)
			std::cout << G.KomponentenZeilen[i] << std::endl;

		*/

		std::cout << "\n\nOutput file saved as " << outputfilename << std::endl;
		std::cout << "\n\n\n\n\n";


		OutputFile.close();
		GraphFile.close();
	}
	else
	{
		std::cout << "Error: Unable to open Graph file \"matrix.csv\"\n\n";
	}

	system("pause");
	return 0;
}