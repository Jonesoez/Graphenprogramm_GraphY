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
				DistanzMatrix[i][j] = infinity; //eigentlich unendlich, INT_MAX wird zur veranschaulichung genommen	
		}
	}

	for (int k = 0; k < Knoten; k++)
		for (int i = 0; i < Knoten; i++)
			for (int j = 0; j < Knoten; j++)
				if (DistanzMatrix[i][k] != infinity && DistanzMatrix[k][j] != infinity && DistanzMatrix[i][k] + DistanzMatrix[k][j] < DistanzMatrix[i][j])
					DistanzMatrix[i][j] = DistanzMatrix[i][k] + DistanzMatrix[k][j];
}

void Graph::matrixPower(int in_matrix[15][15], int out_matrix[15][15], int n)
{
	for (int i = 0; i < Knoten; ++i)
		for (int j = 0; j < Knoten; ++j)
			out_matrix[i][j] = (i == j);

	int temp[15][15];

	for (int w = 0; w < n; w++)
	{
		for (int i = 0; i < Knoten; i++)
		{
			for (int j = 0; j < Knoten; j++)
			{
				temp[i][j] = 0;
				for (int k = 0; k < Knoten; k++)
				{
					temp[i][j] += out_matrix[i][k] * in_matrix[k][j];
				}
			}
		}

		for (int i = 0; i < Knoten; i++) {
			for (int j = 0; j < Knoten; j++)
			{
				out_matrix[i][j] = temp[i][j];
			}
		}
	}
}

void Graph::creatDistanzMatrix2()
{
	//init distance graph
	for (int i = 0; i < Knoten; i++)
	{
		for (int j = 0; j < Knoten; j++)
		{
			DistanzMatrix2[i][j] = Matrix[i][j];;
			if (i == j)
				DistanzMatrix2[i][j] = 0;
			else if (Matrix[i][j] == 0)
				DistanzMatrix2[i][j] = infinity; //eigentlich unendlich, INT_MAX wird zur veranschaulichung genommen	
		}
	}

	bool cont;
	int potenzmatrix[15][15];
	/* 
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			potenzmatrix[i][j] = Matrix[i][j];
	*/

	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			potenzmatrix[i][j] = Matrix[i][j];


	//needs to be updated 
		

		for (int power = 1; power < Knoten; power++)
		{
			bool updated = false;
			bool completed = false;
			matrixPower(potenzmatrix, potenztestmatrix, power);

			// Wenn die Distanzmatrix kein unendlich mehr hat setze completed auf true
			for (int i = 0; i < Knoten; i++)
			{
				for (int j = 0; j < Knoten; j++)
				{
					if (DistanzMatrix2[i][j] == infinity)
					{
						completed = false;
					}
				}
			}
			for (int i = 0; i < Knoten; i++)
			{
				for (int j = 0; j < Knoten; j++)
				{
					if (potenzmatrix[i][j] != 0 && DistanzMatrix2[i][j] == infinity)
					{
						DistanzMatrix2[i][j] = power;
						// setze updated auf true wenn ein Wert gesetzt wurde
						updated = true;
					}
				}
			}
			// Wenn sich die matrix nicht mehr geändert hat breche ab
			if (!updated)
			{
				break;
			}
			// Wenn es nur mehr 1er gibt breche ab
			if (completed)
			{
				break;
			}
		}
		
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
	int delta = INT_MIN;
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

void Graph::calcZentren()
{
	for (int i = 0; i < Knoten; i++)
	{
		if (Exzentrizitaeten[i] == Radius)
		{
			Zentren[i] = Exzentrizitaeten[i];
		}
	}
}