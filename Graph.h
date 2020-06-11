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
		int Komponenten[100];
		int KompPlatz;

		//std::unordered_set<int> KompSetInt;

		//Artikulation und Brücken
		int Artikulation[100];
		int ArtikulationenAnzahl;
		std::unordered_set<int> Artikulationen;
		int TempWegMatrix[15][15];
		int CopyAdjMatrix[15][15];



	//Graph Funktionen
	public:
		void creatDistanzMatrix();
		void createWegMatrix(int in_matrix[15][15], int (&out_matrix)[15][15]);
		void calcKomponenten(int wegmatrix[15][15], int &out_anzahl);
		void calcExzentrizitaet(); //noch nicht fertig
		void calcDurchmesser();
		void calcRadius();
		void calcZentren();
		void calcArtikulation();

		void initCalc();
		void delKnoten(int matrix[15][15], int knoten);

		bool checkInfinity(int value);
		void matrixPower(int in_matrix[15][15], int (&out_matrix)[15][15], int n);
		void setAdjMatrix(int out_matrix[15][15]);
		void setWegMatrix(int out_matrix[15][15]);
		void setKomponenten(int value);
		int	getGraphDimension() { return (int)sqrt(MatrixSize); };	//Durch die Wurzel der Länge der Adjazenzmatrix in der CSV Datei erhält man die Zeilen und Spalten für den 2D Array.
		//int getKomponenten() { return KomponentenSet.size(); };
};

