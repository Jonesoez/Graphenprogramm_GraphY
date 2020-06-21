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
		int MatrixInLines[2500];	//Gesamte Adjazenzmatrix in einem 1D Array
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

		//Artikulation und Bruecken
		int Artikulation[50];
		std::string Bruecken[50];

		int ArtikulationenAnzahl;
		std::unordered_set<int> Artikulationen;




	//Graph Funktionen
	public:
		//Distanz- und Wegmatrix
		void creatDistanzMatrix();
		void createWegMatrix(int in_matrix[50][50], int (&out_matrix)[50][50]);

		//Komponenten
		void calcKomponenten(int wegmatrix[50][50], int &out_anzahl);

		//Eigenschaften
		void calcExzentrizitaet();
		void calcDurchmesser();
		void calcRadius();
		void calcZentren();

		//Artikulationen und Bruecken
		void calcArtikulation();
		void calcBruecken();

		//Ruft alle Berechnungen auf
		void initCalc(); 

		bool checkInfinity(int value);
		void matrixPower(int in_matrix[50][50], int (&out_matrix)[50][50], int n);

		void setAdjMatrix(int (&out_matrix)[50][50]);
		void setWegMatrix(int (&out_matrix)[50][50]);

		int	getGraphDimension() { return (int)sqrt(MatrixSize); };	//Durch die Wurzel der Laenge der Adjazenzmatrix erhaelt man die Zeilen und Spalten fuer den 2D Array
		
};

