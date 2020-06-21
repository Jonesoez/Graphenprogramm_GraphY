#include "Graph.h"

int infinity = INT_MAX;

void Graph::creatDistanzMatrix()
{
	//setze diagonale mit 0en und restliche 0en in der matrix werden mit "unendlich" gespeichert
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
		{
			DistanzMatrix[i][j] = Matrix[i][j];;
			if (i == j)
				DistanzMatrix[i][j] = 0;
			else if (Matrix[i][j] == 0)
				DistanzMatrix[i][j] = infinity; //eigentlich unendlich, INT_MAX wird zur veranschaulichung genommen	
		}

	int temp_matrix[50][50];
	int potenzierte_matrix[50][50];

	//speichere die main matrix in einem temp array
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			temp_matrix[i][j] = Matrix[i][j];


	
	//durchlaufe matrix nach k
	for (int k = 1; k < Knoten; k++)
	{
		//aendere wert nur nach k wenn nicht 0 und unendlich ist
		matrixPower(temp_matrix, potenzierte_matrix, k);

		for (int i = 0; i < Knoten; i++)
			for (int j = 0; j < Knoten; j++)
				if (potenzierte_matrix[i][j] > 0 && DistanzMatrix[i][j] == infinity)
				{
					DistanzMatrix[i][j] = k;
				}
	}
}

void Graph::createWegMatrix(int in_matrix[50][50], int (&out_matrix)[50][50])
{
	//init wegmatrix, diagonale mit 1en fuellen
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
		{
			if (i == j)
				in_matrix[i][j] = 1;
		}

	int potenz_temp_matrix[50][50];
	int potenzierte_matrix[50][50];

	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			potenz_temp_matrix[i][j] = in_matrix[i][j];


	//durchlaufe matrix nach k
	for (int k = 1; k < Knoten; k++)
	{
		matrixPower(potenz_temp_matrix, potenzierte_matrix, k);
		for (int i = 0; i < Knoten; i++)
			for (int j = 0; j < Knoten; j++)
				if (potenzierte_matrix[i][j] != 0) //fuelle matrix mit 1en wenn nicht 0
					in_matrix[i][j] = 1;
	}

	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			out_matrix[i][j] = in_matrix[i][j];
}

//potenziere matrix mit parameter n als exponent
void Graph::matrixPower(int in_matrix[50][50], int (&out_matrix)[50][50], int n)
{
	//setze diagonale mit 1en
	for (int i = 0; i < Knoten; ++i)
		for (int j = 0; j < Knoten; ++j)
			out_matrix[i][j] = (i == j);

	int temp[50][50];

	for (int durchlauf = 0; durchlauf < n; durchlauf++)
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

void Graph::calcKomponenten(int wegmatrix[50][50], int &out_anzahl)
{
	//speichere 2d array wegmatrix in einem 1d array
	int temp_matrix[2500] = { };
	int m_data = 0;
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
		{	
			temp_matrix[m_data] = wegmatrix[i][j];
			m_data++;
		}
			

	//erstelle string set zum speichern der komponenten in einer zeile
	std::unordered_set<std::string> KomponentenSet;
	KomponentenSet.clear();

	int zeile = 0;
	int spalte = 0;
	std::string KomponentenZeilen[50];

	for (int i = 0; i < MatrixSize; i++)
	{
		//append ermoeglicht es mir die einzelnen eintraege nacheinander in einem array zu speichern
		KomponentenZeilen[zeile].append(std::to_string(temp_matrix[i]));
		spalte++;

		//wenn die eintraege die anzahl der knoten erreicht dann springe zur naechsten zeile
		if (spalte == Knoten)
		{
			zeile++;
			spalte = 0;
		}
	}

	//unordered_set -> .emplace speichert einzigartige zeilen, die size gibt mir dann die anzahl der komponenten aus
	for (int i = 0; i < Knoten; i++)
		KomponentenSet.emplace(KomponentenZeilen[i]);

	int size = KomponentenSet.size();
	out_anzahl = size;
}


void Graph::calcExzentrizitaet()
{
	for (int i = 0; i < Knoten; i++)
	{
		int exz = 0;
		for (int j = 0; j < Knoten; j++)
		{
			if (DistanzMatrix[i][j] > exz)
				exz = DistanzMatrix[i][j];
		}
		Exzentrizitaeten[i] = exz;
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

void Graph::setAdjMatrix(int (&out_matrix)[50][50])
{
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			out_matrix[i][j] = Matrix[i][j];
}

void Graph::calcArtikulation()
{
	for (int durchlauf = 0; durchlauf < Knoten; durchlauf++)
	{
		int copy_adj_matrix[50][50] = {};
		int temp_wegmatrix[50][50] = {};
		int gespeicherte_zeile[2500];
		setAdjMatrix(copy_adj_matrix);

		for (int i = 0; i < Knoten; i++)
		{
			gespeicherte_zeile[durchlauf] = copy_adj_matrix[durchlauf][i];
			copy_adj_matrix[durchlauf][i] = 0;
		}

		createWegMatrix(copy_adj_matrix, temp_wegmatrix);
		calcKomponenten(temp_wegmatrix, Komponenten[durchlauf + 1]);

		//ueberpruefe ob sich die neu berechneten komponenten mit der originalen adjazenzmatrix unterscheiden Komponenten[0] = Komponenten aus der unberuehrten main matrix
		if (Komponenten[0] < Komponenten[durchlauf + 1] - 1)
		{
			Artikulation[durchlauf] = durchlauf + 1;
			ArtikulationenAnzahl++;
		}

		//geloeschten Knoten wieder hinzufügen
		for (int i = 0; i < Knoten; i++)
			copy_adj_matrix[durchlauf][i] = gespeicherte_zeile[i];
	}
}

void Graph::calcBruecken()
{
	int komponenten[50] = {};
	int pos = 0;
	
	for (int durchlauf = 0; durchlauf < Knoten; durchlauf++)
	{
		for (int i = durchlauf+1; i < Knoten; i++) //durchlaufe die matrix gespiegelt
		{
			int copy_adj_matrix[50][50] = { 0 };
			int temp_wegmatrix[50][50] = { 0 };
			setAdjMatrix(copy_adj_matrix);

			if (copy_adj_matrix[durchlauf][i] == 1)
			{
				//loesche kante mit spiegelung
				copy_adj_matrix[durchlauf][i] = 0;
				copy_adj_matrix[i][durchlauf] = 0;

				createWegMatrix(copy_adj_matrix, temp_wegmatrix);
				calcKomponenten(temp_wegmatrix, komponenten[pos]);
				

				if (Komponenten[0] < komponenten[pos])
				{
					Bruecken[pos].append(std::to_string(durchlauf + 1));
					Bruecken[pos].append("-");
					Bruecken[pos].append(std::to_string(i + 1));
					Bruecken[pos].append(" ");
				}
			
				//setze geloeschte kante wieder zurueck
				copy_adj_matrix[durchlauf][i] = 1;
				copy_adj_matrix[i][durchlauf] = 1;
			}
		}
		pos++;
	}
}

bool Graph::checkInfinity(int value)
{
	if (value == INT_MAX)
		return true;
	else
		return false;
}

void Graph::setWegMatrix(int (&out_matrix)[50][50])
{
	for (int i = 0; i < Knoten; i++)
		for (int j = 0; j < Knoten; j++)
			out_matrix[i][j] = WegMatrix[i][j];
}

void Graph::initCalc()
{
	int copy_adj_matrix[50][50];
	int copy_weg_matrix[50][50];
	setAdjMatrix(copy_adj_matrix);
	setWegMatrix(copy_weg_matrix);

	//Distanz- und Wegmatrix Berechnung
	creatDistanzMatrix();
	createWegMatrix(copy_adj_matrix, WegMatrix);

	//Komponenten
	calcKomponenten(WegMatrix, Komponenten[0]);

	//Eigenschaften
	calcExzentrizitaet();
	calcDurchmesser();
	calcRadius();
	calcZentren();

	//Artikulationen und Bruecken
	calcArtikulation();
	calcBruecken();
}