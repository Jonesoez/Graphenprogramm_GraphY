#pragma once
#include <vector>
#include <unordered_set>
#include <string>

class Graph
{
	//Graph
	public:
		int Knoten;
		//int Kanten;
		int Matrix[15][15]; //15x15 sollte fuer den anfang reichen, wird vielleicht noch zu einem dynamischen array geaendert fuer mehr size
		int MatrixInLines[100];
		int MatrixSize;
		int DistanzMatrix[15][15];
		int WegMatrix[15][15];

		
		//Eigenschaften
		int Exzentrizitaeten[100];
		int Durchmesser, Radius;
		int Zentren[100];

		int Komponenten;
		std::string KomponentenZeilen[100];
		std::unordered_set<std::string> KomponentenSet;
		std::vector<std::vector<int>> matrixv;


	//Graph Funktionen
	public:
		void creatDistanzMatrix();
		void createWegMatrix();
		void calcKomponenten();
		void calcExzentrizitaet(); //noch nicht fertig
		void calcDurchmesser();
		void calcRadius();
		void calcZentren();

		void matrixPower(int in_matrix[15][15], int out_matrix[15][15], int n);
		void matrixAdd(int add_matrix[15][15], int out_matrix[15][15]);
		int	getGraphDimension() { return (int)sqrt(MatrixSize); };	//Durch die Wurzel der Länge der Adjazenzmatrix in der CSV Datei erhält man die Zeilen und Spalten für den 2D Array.

};

