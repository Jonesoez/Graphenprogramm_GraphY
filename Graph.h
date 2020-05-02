#pragma once

class Graph
{
	//Graph
	public:
		int Knoten;
		int Kanten;
		int Matrix[10][10]; //10x10 sollte fuer den anfang reichen, wird vielleicht noch zu einem dynamischen array geaendert

	//Graph Funktionen
	public:
		void drawGraph(int AnzahlKnoten, int AnzahlKanten);
		void matrixAdd(int matrix[2][2]);
		void matrixMultiply(int matrix[2][2]);
};