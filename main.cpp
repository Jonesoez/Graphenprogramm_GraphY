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
		std::cout << "Knoten der Adjazenzmatrix: " << G.getGraphDimension() << std::endl;
		G.Knoten = G.getGraphDimension();
		OutputFile << "Knoten: " << G.Knoten << std::endl;


		//Print 2D Converted Matrix
		std::cout << "\nAdjazenzmatrix: " << std::endl;
		OutputFile << "\nAdjazenzmatrix: \n";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			for (int j = 0; j < G.getGraphDimension(); j++)
			{
				std::cout << G.Matrix[i][j] << " ";
				OutputFile << G.Matrix[i][j] << "\t";
			}
			std::cout << std::endl;
			OutputFile << std::endl;
		}
		OutputFile << std::endl;

		G.initCalc();


		std::cout << "\nDistanzmatrix: " << std::endl;
		OutputFile << "Distanzmatrix: \n";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			for (int j = 0; j < G.getGraphDimension(); j++)
			{
				if (G.checkInfinity(G.DistanzMatrix[i][j]))
				{
					OutputFile << "~" << "\t";
					std::cout << "~" << " ";
				}
				else
				{
					std::cout << G.DistanzMatrix[i][j] << " ";
					OutputFile << G.DistanzMatrix[i][j] << "\t";
				}
			}
			std::cout << std::endl;
			OutputFile << std::endl;
		}
		OutputFile << std::endl;
		std::cout << std::endl;
	

		std::cout << "Exzentrizit�ten: [ ";
		OutputFile << "Exzentrizit�ten: [ ";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			if (G.checkInfinity(G.Exzentrizitaeten[i]))
			{
				OutputFile << "~ ";
				std::cout << "~ ";
			}
			else
			{
				std::cout << G.Exzentrizitaeten[i] << " ";
				OutputFile << G.Exzentrizitaeten[i] << " ";
			}
		}
		OutputFile << "]" << std::endl;
		std::cout << "]" << std::endl;


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
		std::cout << "]" << std::endl << std::endl;
		OutputFile << "]" << std::endl;


		std::cout << "Wegmatrix: \n";
		OutputFile << "\nWegmatrix: \n";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			for (int j = 0; j < G.getGraphDimension(); j++)
			{
				std::cout << G.WegMatrix[i][j] << " ";
				OutputFile << G.WegMatrix[i][j] << "\t";
			}
			std::cout << std::endl;
			OutputFile << std::endl;
		}
		OutputFile << std::endl;
		
		std::cout << "\n\n";


		//std::cout << "Anzahl der Komponenten: ";
		//std::cout << G.KomponentenAnzahl << std::endl;
		//OutputFile << "Anzahl der Komponenten: " << G.KomponentenAnzahl << std::endl;

		/* 
		std::cout << "\n\n\Komponenten Zeilen: \n";
		for (int i = 0; i < G.getGraphDimension(); i++)
			std::cout << G.KomponentenZeilen[i] << std::endl;

		*/

		std::cout << "Anzahl der Komponenten: ";
		std::cout << G.Komponenten[0] << std::endl;
		OutputFile << "Anzahl der Komponenten: " << G.Komponenten[0] << std::endl;


		/*
		//Komponenten Array
		std::cout << "Komponenten Array: \n";
		for (int i = 0; i < G.getGraphDimension(); i++)
			std::cout << G.Komponenten[i] << std::endl;
		
		std::cout << "Komponenten \n";
		for (auto& elements : G.KomponentenSet)
		{
			std::cout << elements << std::endl;
		}
		*/

		std::cout << "Artikulationen an den Knoten: [ ";

		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			if (G.Artikulation[i] != 0)
				std::cout << G.Artikulation[i] << " ";
		}
		std::cout << "]" << std::endl << std::endl;

		std::cout << "Artikulationen Anzahl: ";
		std::cout << G.ArtikulationenAnzahl << std::endl;


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