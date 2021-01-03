#include "Tetromino.h"
//UTF-8 Коммент

Tetromino::Tetromino()
{
    int X = rand() % 7 + 1;
	iType = X;

	switch (iType)
	{
	case 1:
		aTetro.at(0) = { 0,0,X,0 };
		aTetro.at(1) = { 0,0,X,0 };
		aTetro.at(2) = { 0,0,X,0 };
		aTetro.at(3) = { 0,0,X,0 };
		break;
	case 2:
		aTetro.at(0) = { 0,0,X,0 };
		aTetro.at(1) = { 0,X,X,0 };
		aTetro.at(2) = { 0,0,X,0 };
		aTetro.at(3) = { 0,0,0,0 };
		break;
	case 3:
		aTetro.at(0) = { 0,0,0,0 };
		aTetro.at(1) = { 0,X,X,0 };
		aTetro.at(2) = { 0,X,X,0 };
		aTetro.at(3) = { 0,0,0,0 };
		break;
	case 4:
		aTetro.at(0) = { 0,0,X,0 };
		aTetro.at(1) = { 0,X,X,0 };
		aTetro.at(2) = { 0,X,0,0 };
		aTetro.at(3) = { 0,0,0,0 };
		break;
	case 5:
		aTetro.at(0) = { 0,X,0,0 };
		aTetro.at(1) = { 0,X,X,0 };
		aTetro.at(2) = { 0,0,X,0 };
		aTetro.at(3) = { 0,0,0,0 };
		break;
	case 6:
		aTetro.at(0) = { 0,X,0,0 };
		aTetro.at(1) = { 0,X,0,0 };
		aTetro.at(2) = { 0,X,X,0 };
		aTetro.at(3) = { 0,0,0,0 };
		break;
	case 7:
		aTetro.at(0) = { 0,0,X,0 };
		aTetro.at(1) = { 0,0,X,0 };
		aTetro.at(2) = { 0,X,X,0 };
		aTetro.at(3) = { 0,0,0,0 };
		break;
	}
}

Tetromino::~Tetromino()
{

}

#include <iostream>
void Tetromino::Rotate()
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++)
			std::cout << aTetro.at(i).at(j);
		std::cout << std::endl;
	}
	std::cout << std::endl;
	//жожа
	int n = 4;
	int b;
	for (int i = 0; i < n / 2; i++)
		for (int j = i; j < n - 1 - i; j++) {
			b = a[i][j];
			a[i][j] = a[n - j - 1][i];
			a[n - j - 1][i] = a[n - i - 1][n - j - 1];
			a[n - i - 1][n - j - 1] = a[j][n - i - 1];
			a[j][n - i - 1] = b;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			std::cout << aTetro.at(i).at(j);
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

bool Tetromino::DoesItFit()
{
    return false;
}
