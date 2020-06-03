#pragma once
#include <vector>

class Graph
{
	//Graph
	public:
		int Knoten;
		//int Kanten;
		int Matrix[15][15]; //15x15 sollte fuer den anfang reichen, wird vielleicht noch zu einem dynamischen array geaendert fuer mehr size
		int MatrixSize;
		int DistanzMatrix[15][15];
		int DistanzMatrix2[15][15];

		int potenztestmatrix[15][15];
		
		//Eigenschaften
		int Exzentrizitaeten[15];
		int Durchmesser, Radius;
		int Zentren[15];
		std::vector<std::vector<int>> matrixv;


	//Graph Funktionen
	public:
		void creatDistanzMatrix();
		void creatDistanzMatrix2();
		void calcExzentrizitaet(); //noch nicht fertig
		void calcDurchmesser();
		void calcRadius();
		void calcZentren();

		void matrixPower(int in_matrix[15][15], int out_matrix[15][15], int n);
		void matrixAdd(int matrix_t[15][15]);
		void matrixMultiply(int matrix[15][15]);
		int	getGraphDimension() { return (int)sqrt(MatrixSize); };	//Durch die Wurzel der Länge der Adjazenzmatrix in der CSV Datei erhält man die Zeilen und Spalten für den 2D Array.

};

