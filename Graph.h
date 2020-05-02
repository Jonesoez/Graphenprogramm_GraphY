#pragma once

class Graph
{
	//Graph
	public:
		int Knoten;
		int Kanten;
		int Matrix[10][10]; //10x10 should be enough

	//Graph functions
	public:
		void drawGraph(int AnzahlKnoten, int AnzahlKanten);
		void matrixAdd(int matrix[2][2]);
		void matrixMultiply(int matrix[2][2]);
};