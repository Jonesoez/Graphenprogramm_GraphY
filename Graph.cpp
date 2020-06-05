#include "Graph.h"

int infinity = INT_MAX;

void Graph::creatDistanzMatrix()
{
	//init distance graph
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
		{
			DistanzMatrix[i][j] = Matrix[i][j];;
			if (i == j)
				DistanzMatrix[i][j] = 0;
			else if (Matrix[i][j] == 0)
				DistanzMatrix[i][j] = infinity; //eigentlich unendlich, INT_MAX wird zur veranschaulichung genommen	
		}

	int temp_matrix[15][15];
	int potenzierte_matrix[15][15];

	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			temp_matrix[i][j] = Matrix[i][j];


	for (int k = 1; k < Knoten; k++)
	{
		matrixPower(temp_matrix, potenzierte_matrix, k);
		for (int i = 0; i < Knoten; i++)
			for (int j = 0; j < Knoten; j++)
				if (potenzierte_matrix[i][j] != 0 && DistanzMatrix[i][j] == infinity)
					DistanzMatrix[i][j] = k;
	}
}


void Graph::createWegMatrix()
{
	//init wegmatrix
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
		{
			WegMatrix[i][j] = Matrix[i][j];;
			if (i == j)
				WegMatrix[i][j] = 1;
		}

	int potenz_temp_matrix[15][15];
	int potenzierte_matrix[15][15];

	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			potenz_temp_matrix[i][j] = Matrix[i][j];


	for (int k = 1; k < Knoten; k++)
	{
		matrixPower(potenz_temp_matrix, potenzierte_matrix, k);
		for (int i = 0; i < Knoten; i++)
			for (int j = 0; j < Knoten; j++)
				if (potenzierte_matrix[i][j] != 0)
					WegMatrix[i][j] = 1;
	}
}


//potenziere matrix mit parameter n als exponent
void Graph::matrixPower(int in_matrix[15][15], int out_matrix[15][15], int n)
{
	for (int i = 0; i < Knoten; ++i)
		for (int j = 0; j < Knoten; ++j)
			out_matrix[i][j] = (i == j);

	int temp[15][15];

	for (int w = 0; w < n; w++)
	{
		for (int i = 0; i < Knoten; i++)
			for (int j = 0; j < Knoten; j++)
			{
				temp[i][j] = 0;
				for (int k = 0; k < Knoten; k++)
					temp[i][j] += out_matrix[i][k] * in_matrix[k][j];
			}
		
		for (int i = 0; i < Knoten; i++) 
			for (int j = 0; j < Knoten; j++)
				out_matrix[i][j] = temp[i][j];
	}
}

//idee: speichere die wegmatrix in einem string array welches mit der wegmatrix befüllt wird
void Graph::calcKomponenten()
{
	//not working right now

	int temp_matrix[100];


	//speichere 2d array wegmatrix in einem 1d array
	int m_data = 0;
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			temp_matrix[m_data++] = WegMatrix[i][j];

	int zeile = 0;
	int counter = 0;
	std::string KompZeilen[100];


	for (int i = 0; i < MatrixSize; i++)
	{
		KomponentenZeilen[zeile].append(std::to_string(temp_matrix[i]));
		counter++;

		//da die matrix immer quadratisch ist können wir einfach per 
		if (counter % Knoten == 0)
			zeile++;
	}

	//unordered_set speichert nur einziartiges zeug
	for (int i = 0; i < Knoten; i++)
	{
		KomponentenSet.emplace(KomponentenZeilen[i]);
	}

	Komponenten = KomponentenSet.size();
}

void Graph::matrixAdd(int add_matrix[15][15], int out_matrix[15][15])
{
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			out_matrix[i][j] += add_matrix[i][j];
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