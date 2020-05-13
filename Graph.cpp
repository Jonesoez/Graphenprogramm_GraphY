#include "Graph.h"

int infinity = INT_MAX;

void Graph::creatDistanzMatrix()
{
	//init distance graph
	for (int i = 0; i < Knoten; i++)
	{
		for (int j = 0; j < Knoten; j++)
		{
			DistanzMatrix[i][j] = Matrix[i][j];; 
			if (i == j)
				DistanzMatrix[i][j] = 0;
			else if (Matrix[i][j] == 0)
				DistanzMatrix[i][j] = infinity; //eigentlich unendlich, aber da wir unendlich nicht als zahl darstellen koennen, nehmen wir einfach die max int laenge zur veranschaulichung
				
		}
	}

	for (int k = 0; k < Knoten; k++)
		for (int i = 0; i < Knoten; i++)
			for (int j = 0; j < Knoten; j++)
				if (DistanzMatrix[i][k] != infinity && DistanzMatrix[k][j] != infinity && DistanzMatrix[i][k] + DistanzMatrix[k][j] < DistanzMatrix[i][j])
					DistanzMatrix[i][j] = DistanzMatrix[i][k] + DistanzMatrix[k][j];

}

void Graph::matrixAdd(int m_t[15][15])
{
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			Matrix[i][j] += m_t[i][j];
}

void Graph::calcExzentrizitaet()
{
	int exz = 0;
	for (int i = 0; i < Knoten; i++)
	{
		for (int j = 0; j < Knoten; j++)
		{
			if (DistanzMatrix[i][j] > exz)
				Exzentrizitaeten[i] = DistanzMatrix[i][j];
			exz = Exzentrizitaeten[i];
		}
	}
}

void Graph::calcDurchmesser()
{
	int delta = 0;
	for (int i = 0; i < Knoten; i++)
	{
		if (Exzentrizitaeten[i] > delta)
		{
			delta = Exzentrizitaeten[i];
		}
	}
	Durchmesser = delta;
}

void Graph::calcRadius()
{
	int delta = INT_MAX;
	for (int i = 0; i < Knoten; i++)
	{
		if (Exzentrizitaeten[i] < delta)
		{
			delta = Exzentrizitaeten[i];
		}
	}
	Radius = delta;
}