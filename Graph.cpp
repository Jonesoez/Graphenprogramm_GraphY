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


void Graph::createWegMatrix(int in_matrix[15][15], int out_matrix[15][15], int knoten)
{
	//init wegmatrix
	for (int i = 0; i < knoten; i++)
		for (int j = 0; j < knoten; j++)
		{
			if (i == j)
				in_matrix[i][j] = 1;
		}

	int potenz_temp_matrix[15][15];
	int potenzierte_matrix[15][15];

	for (int i = 0; i < knoten; i++)
		for (int j = 0; j < knoten; j++)
			potenz_temp_matrix[i][j] = in_matrix[i][j];

	for (int k = 1; k < Knoten; k++)
	{
		matrixPower(potenz_temp_matrix, potenzierte_matrix, k);
		for (int i = 0; i < knoten; i++)
			for (int j = 0; j < knoten; j++)
				if (potenzierte_matrix[i][j] != 0)
					in_matrix[i][j] = 1;
	}

	for (int i = 0; i < knoten; i++)
		for (int j = 0; j < knoten; j++)
			out_matrix[i][j] = in_matrix[i][j];
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

void Graph::calcKomponenten(int wegmatrix[15][15], int out_anzahl, int knoten)
{
	//speichere 2d array wegmatrix in einem 1d array
	int temp_matrix[100] = { 0 };
	int m_data = 0;
	for (int i = 0; i < knoten; i++)
		for (int j = 0; j < knoten; j++)
			temp_matrix[m_data++] = wegmatrix[i][j];

	int zeile = 0;
	int spalte = 0;

	//vectorsssss for tests
	//std::vector<int> Komponenten[100];

	std::string KomponentenZeilen[100];

	for (int i = 0; i < knoten*knoten; i++)
	{
		KomponentenZeilen[zeile].append(std::to_string(temp_matrix[i]));
		//Komponenten[zeile].push_back(temp_matrix[i]);
		spalte++;

		//big brain
		if (spalte % knoten == 0)
			zeile++;
	}

	//unordered_set speichert nur einziartiges zeug
	for (int i = 0; i < knoten; i++)
	{
		KomponentenSet.emplace(KomponentenZeilen[i]);
		//KompSetInt.emplace(std::stoi(KomponentenZeilen[i]));
	}

	out_anzahl = KomponentenSet.size();
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

void Graph::setAdjMatrix(int out_matrix[15][15], int knoten)
{
	for (int i = 0; i < knoten; i++)
		for (int j = 0; j < knoten; j++)
			out_matrix[i][j] = Matrix[i][j];
}

//not working yet
void Graph::calcArtikulation()
{
	int copy_adj_matrix[15][15];
	int temp_wegmatrix[15][15];

	int akt_komponentenAnzahl = KomponentenAnzahl;
	int aft_KomponentenAnzahl = 0;
	int rm_knoten = Knoten;

	for (int i = 0; i < rm_knoten; i++)
		for (int j = 0; j < rm_knoten; j++)
			copy_adj_matrix[i][j] = Matrix[i][j];

	printf("\ncopy_adj_matrix: \n");
	for (int i = 0; i < Knoten; i++)
	{
		for (int j = 0; j < Knoten; j++)
			printf("%d ", copy_adj_matrix[i][j]);

		printf("\n");
	}
	printf("\n\n");

	for (int durchlauf = 0; durchlauf < Knoten; durchlauf++)
	{

		createWegMatrix(copy_adj_matrix, temp_wegmatrix, rm_knoten-durchlauf);
		calcKomponenten(temp_wegmatrix, aft_KomponentenAnzahl, rm_knoten-durchlauf);

		if (akt_komponentenAnzahl - 1> aft_KomponentenAnzahl)
			Artikulation[durchlauf] = durchlauf+1;


	}
}

bool Graph::checkInfinity(int value)
{
	if (value == INT_MAX)
		return true;
	else
		return false;
}

void Graph::setKomponenten(int value)
{
	KomponentenAnzahl = value;
}

void Graph::initCalc()
{
	int copy_adj_matrix[15][15];
	setAdjMatrix(copy_adj_matrix, Knoten);
	creatDistanzMatrix();

	createWegMatrix(copy_adj_matrix, WegMatrix, Knoten);
	calcKomponenten(WegMatrix, KomponentenAnzahl, Knoten);


	calcExzentrizitaet();
	calcDurchmesser();
	calcRadius();
	calcZentren();
	//calcArtikulation();
}