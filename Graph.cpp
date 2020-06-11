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


void Graph::createWegMatrix(int in_matrix[15][15], int (&out_matrix)[15][15])
{
	//init wegmatrix
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
		{
			if (i == j)
				in_matrix[i][j] = 1;
		}

	int potenz_temp_matrix[15][15];
	int potenzierte_matrix[15][15];

	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			potenz_temp_matrix[i][j] = in_matrix[i][j];

	for (int k = 1; k < Knoten; k++)
	{
		matrixPower(potenz_temp_matrix, potenzierte_matrix, k);
		for (int i = 0; i < Knoten; i++)
			for (int j = 0; j < Knoten; j++)
				if (potenzierte_matrix[i][j] != 0)
					in_matrix[i][j] = 1;
	}


	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			out_matrix[i][j] = in_matrix[i][j];


}

//potenziere matrix mit parameter n als exponent
void Graph::matrixPower(int in_matrix[15][15], int (&out_matrix)[15][15], int n)
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

void Graph::setKomponenten(int value)
{
	Komponenten[0] = value;
}

void Graph::calcKomponenten(int wegmatrix[15][15], int &out_anzahl)
{

	//speichere 2d array wegmatrix in einem 1d array
	int temp_matrix[100] = { 0 };
	int m_data = 0;
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
		{	
			temp_matrix[m_data] = wegmatrix[i][j];
			m_data++;
		}
			

	std::unordered_set<std::string> KomponentenSet;
	KomponentenSet.clear();

	int zeile = 0;
	int spalte = 0;

	//vectorsssss for tests
	//std::vector<int> Komponenten[100];

	std::string KomponentenZeilen[100];

	for (int i = 0; i < MatrixSize; i++)
	{
		KomponentenZeilen[zeile].append(std::to_string(temp_matrix[i]));
		//Komponenten[zeile].push_back(temp_matrix[i]);
		spalte++;

		//big brain
		if (spalte == Knoten)
		{
			zeile++;
			spalte = 0;
		}
	}

	//unordered_set speichert nur einziartiges zeug
	for (int i = 0; i < Knoten; i++)
	{
		KomponentenSet.emplace(KomponentenZeilen[i]);
		//KompSetInt.emplace(std::stoi(KomponentenZeilen[i]));
	}

	int size = KomponentenSet.size();
	out_anzahl = size;
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

void Graph::setAdjMatrix(int (&out_matrix)[15][15])
{
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			out_matrix[i][j] = Matrix[i][j];
}

void Graph::delKnoten(int matrix[15][15], int knoten)
{
	for (int i = knoten; i < Knoten; i++)
		for (int j = knoten; j < Knoten; j++)
			matrix[i][j] = 0;
}

//working yet
void Graph::calcArtikulation()
{
	for (int durchlauf = 0; durchlauf < Knoten; durchlauf++)
	{
		int copy_adj_matrix[15][15] = { 0 };
		int komponenten[100];

		int temp_wegmatrix[15][15] = { 0 };
		setAdjMatrix(copy_adj_matrix);
		int gespeicherte_zeile[100];
		for (int i = 0; i < Knoten; i++)
		{
			gespeicherte_zeile[durchlauf] = copy_adj_matrix[durchlauf][i];
			copy_adj_matrix[durchlauf][i] = 0;
		}

		createWegMatrix(copy_adj_matrix, temp_wegmatrix);
		calcKomponenten(temp_wegmatrix, Komponenten[durchlauf + 1]);

		//überorüfe ob sich die neu berechneten komponenten mit der originalen adjazenzmatrix unterscheiden Komponenten[0] -> adjazenzmatrix full
		if (Komponenten[0] < Komponenten[durchlauf + 1] - 1)
		{
			Artikulation[durchlauf] = durchlauf + 1;
			ArtikulationenAnzahl++;
		}

		//gelöschten Knoten wieder hinzufügen
		for (int i = 0; i < Knoten; i++)
		{
			copy_adj_matrix[durchlauf][i] = gespeicherte_zeile[i];

		}
	}
}

void Graph::calcBruecken()
{
	int komponenten[100];
	int copy_adj_matrix[15][15] = { 0 };
	int temp_wegmatrix[15][15] = { 0 };
	setAdjMatrix(copy_adj_matrix);

	for (int durchlauf = 0; durchlauf < Knoten; durchlauf++)
	{

		for (int i = durchlauf+1; i < Knoten; i++)
		{
			if (copy_adj_matrix[durchlauf][i] == 1)
			{
				copy_adj_matrix[durchlauf][i] = 0;
			}

			createWegMatrix(copy_adj_matrix, temp_wegmatrix);
			calcKomponenten(temp_wegmatrix, komponenten[durchlauf]);


			//überprüfe ob sich die neu berechneten komponenten mit der originalen adjazenzmatrix unterscheiden Komponenten[0] -> adjazenzmatrix full
			if (Komponenten[0] < komponenten[durchlauf] - 1)
			{
				//printf("Bruecken an Knoten: %d\n", durchlauf + 1, i+1);
			}

			//printf("Bruecken Komponenten RAW: %d\n", komponenten[durchlauf]);

			//gelöschte kante hinzufuegen

			copy_adj_matrix[durchlauf][i] = 1;
			
		}
	}
}

bool Graph::checkInfinity(int value)
{
	if (value == INT_MAX)
		return true;
	else
		return false;
}

void Graph::setWegMatrix(int (&out_matrix)[15][15])
{
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			out_matrix[i][j] = WegMatrix[i][j];
}

void Graph::initCalc()
{
	int copy_adj_matrix[15][15];
	int copy_weg_matrix[15][15];
	int komponenten;
	setAdjMatrix(copy_adj_matrix);
	setWegMatrix(copy_weg_matrix);

	creatDistanzMatrix();

	createWegMatrix(copy_adj_matrix, WegMatrix);
	calcKomponenten(WegMatrix, Komponenten[0]);

	calcExzentrizitaet();
	calcDurchmesser();
	calcRadius();
	calcZentren();
	calcArtikulation();
	calcBruecken();
}