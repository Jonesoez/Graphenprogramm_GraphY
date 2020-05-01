#pragma once

class Graph
{
	//Graph
	public:
		int Knoten;
		int Kanten;
		int Matrix2D[10][10] = { 0 };

	//Graph functions
	public:
		void drawGraph(int AnzahlKnoten, int AnzahlKanten);
		void matrixAdd(int matrix[2][2]);
		void matrixMultiply(int matrix[2][2]);
};