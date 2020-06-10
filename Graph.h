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

		//Komponenten aus der main Adjazenzmatrix
		int KomponentenAnzahl;

		//std::unordered_set<int> KompSetInt;
		std::unordered_set<std::string> KomponentenSet;

		//Artikulation und Br�cken
		int Artikulation[100];
		int TempWegMatrix[15][15];
		int CopyAdjMatrix[15][15];



	//Graph Funktionen
	public:
		void creatDistanzMatrix();
		void createWegMatrix(int in_matrix[15][15], int out_matrix[15][15], int knoten);
		void calcKomponenten(int wegmatrix[15][15], int out_anzahl, int knoten);
		void calcExzentrizitaet(); //noch nicht fertig
		void calcDurchmesser();
		void calcRadius();
		void calcZentren();
		void calcArtikulation();

		void initCalc();

		bool checkInfinity(int value);
		void matrixPower(int in_matrix[15][15], int out_matrix[15][15], int n);
		void matrixAdd(int add_matrix[15][15], int out_matrix[15][15]);
		void setAdjMatrix(int out_matrix[15][15], int knoten);
		void setKomponenten(int value);
		int	getGraphDimension() { return (int)sqrt(MatrixSize); };	//Durch die Wurzel der L�nge der Adjazenzmatrix in der CSV Datei erh�lt man die Zeilen und Spalten f�r den 2D Array.
		int getKomponenten() { return KomponentenSet.size(); };
};

