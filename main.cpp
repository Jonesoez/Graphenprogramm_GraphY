#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Graph.h"

Graph G;

int main()
{
	std::cout << "GraphY v1.3 by Yunus Oeztuerk 4AKIF\n\n";
	std::string CSVmatrix;
	std::string filename;
	std::string outputfilename = "graph_berechnet.txt";

	std::cout << "Please choose your .csv file e.g. \"graph/g1.csv\": ";
	std::getline(std::cin, filename);

	std::ifstream GraphFile(filename);
	std::ofstream OutputFile(outputfilename);

	int m_temp[2500] = { 0 };

	if (GraphFile.is_open())
	{
		std::cout << "Reading adjacency matrix from csv file...\n\n";
		while (std::getline(GraphFile, CSVmatrix, ','))
		{
			m_temp[G.MatrixSize] = std::stoi(CSVmatrix);
			G.MatrixInLines[G.MatrixSize] = std::stoi(CSVmatrix);
			G.MatrixSize++;
		}

		//1D Matrix(Array) zu 2D Matrix(Array)
		int m_data = 0;
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			for (int j = 0; j < G.getGraphDimension(); j++)
			{
				G.Matrix[i][j] = m_temp[m_data];
				m_data++;
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
				OutputFile << G.Matrix[i][j] << " ";
			}
			std::cout << std::endl;
			OutputFile << std::endl;
		}
		OutputFile << std::endl;


		// Alle berechnungen durchfuehren
		G.initCalc();

		// Distanzmatrix
		std::cout << "\nDistanzmatrix: " << std::endl;
		OutputFile << "Distanzmatrix: \n";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			for (int j = 0; j < G.getGraphDimension(); j++)
			{
				if (G.checkInfinity(G.DistanzMatrix[i][j]))
				{
					OutputFile << "~" << " ";
					std::cout << "~" << " ";
				}
				else
				{
					std::cout << G.DistanzMatrix[i][j] << " ";
					OutputFile << G.DistanzMatrix[i][j] << " ";
				}
			}
			std::cout << std::endl;
			OutputFile << std::endl;
		}
		OutputFile << std::endl;
		std::cout << std::endl;
	

		// Exzentrizitaeten
		std::cout << "Exzentrizitaeten: [ ";
		OutputFile << "Exzentrizitäten: [ ";
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


		// Durchmesser
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


		// Radius
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


		// Zentren
		std::cout << "Zentren: An den Knoten: [ ";
		OutputFile << "Zentren: An den Knoten: [ ";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
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


		// Wegmatrix
		std::cout << "Wegmatrix: \n";
		OutputFile << "\nWegmatrix: \n";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			for (int j = 0; j < G.getGraphDimension(); j++)
			{
				std::cout << G.WegMatrix[i][j] << " ";
				OutputFile << G.WegMatrix[i][j] << " ";
			}
			std::cout << std::endl;
			OutputFile << std::endl;
		}
		OutputFile << std::endl;
		
		std::cout << "\n\n";


		// Komponenten
		std::cout << "Komponenten: ";
		std::cout << G.Komponenten[0] << std::endl;
		OutputFile << "Komponenten: " << G.Komponenten[0] << std::endl;


		// Artikulationen
		std::cout << "Artikulationen an den Knoten: [ ";
		OutputFile << "Artikulationen an den Knoten: [ ";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			if (G.Artikulation[i] != 0)
			{
				std::cout << G.Artikulation[i] << " ";
				OutputFile << G.Artikulation[i] << " ";
			}
			else
			{
				std::cout << "~ ";
				OutputFile << "~ ";
			}
		}
		std::cout << "]" << std::endl;
		OutputFile << "]" << std::endl;


		// Bruecken
		std::cout << "Bruecken zwischen Knoten: [ ";
		OutputFile << "Brücken zwischen Knoten: [ ";
		for (int i = 0; i < G.getGraphDimension(); i++)
		{
			if (!G.Bruecken[i].empty())
			{
				std::cout << G.Bruecken[i];
				OutputFile << G.Bruecken[i];
			}
			else
			{
				std::cout << "~ ";
				OutputFile << "~ ";
			}
			
		}
		std::cout << "]" << std::endl << std::endl;
		OutputFile << "]" << std::endl;


		std::cout << "\n\nOutput file saved as " << outputfilename << std::endl;
		std::cout << "\n\n\n\n\n";

	
		OutputFile.close();
		GraphFile.close();
	}
	else
	{
	std::cout << "Error: Unable to open Graph file \"" << filename << "\"" << std::endl;
	}

	system("pause");
	return 0;
}