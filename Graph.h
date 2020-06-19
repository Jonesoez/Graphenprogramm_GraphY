#pragma once
#include <vector>
#include <unordered_set>
#include <string>

class Graph
{
	//Graph
	public:
		//Allgemeines
		int Knoten;
		int Matrix[50][50];
		int MatrixInLines[2500];
		int MatrixSize;
		int DistanzMatrix[50][50];
		int WegMatrix[50][50];


		//Eigenschaften
		int Exzentrizitaeten[50];
		int Durchmesser, Radius;
		int Zentren[50];

		//Komponenten aus der main Adjazenzmatrix
		int Komponenten[50];
		std::unordered_set<std::string> KomponentenSetMain;

		//Artikulation und Brücken
		int Artikulation[50];
		std::string Bruecken[50];

		int ArtikulationenAnzahl;
		std::unordered_set<int> Artikulationen;




	//Graph Funktionen
	public:
		void creatDistanzMatrix();
		void createWegMatrix(int in_matrix[50][50], int (&out_matrix)[50][50]);
		void calcKomponenten(int wegmatrix[50][50], int &out_anzahl);
		void calcExzentrizitaet(); //noch nicht fertig
		void calcDurchmesser();
		void calcRadius();
		void calcZentren();
		void calcArtikulation();
		void calcBruecken();

		void initCalc();

		bool checkInfinity(int value);
		void matrixPower(int in_matrix[50][50], int (&out_matrix)[50][50], int n);
		void setAdjMatrix(int (&out_matrix)[50][50]);
		void setWegMatrix(int (&out_matrix)[50][50]);
		int	getGraphDimension() { return (int)sqrt(MatrixSize); };	//Durch die Wurzel der Länge der Adjazenzmatrix in der CSV Datei erhält man die Zeilen und Spalten für den 2D Array.
		//int getKomponenten() { return KomponentenSet.size(); };
};

