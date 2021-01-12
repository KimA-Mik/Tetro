#pragma once
#include <array>
//поле 10 на 20
#define FieldArray std::array<std::array<int,20>,10>
#define TetroArray std::array<std::array<int, 4>, 4>

//
//Сам тетромино
class Tetromino
{
public:
	Tetromino();
	Tetromino(int X);
	~Tetromino();

	//void StartMoving(FieldArray StartArray);

	void Rotate(int xPos, int yPos);
	void ForceRotate();

	void StartMoving(FieldArray& Field);

	TetroArray GetFigure();

	bool DoesItFit(int x, int y);
	bool DoesItFitRotated(int xPos, int yPos, TetroArray& Rotated);

	FieldArray GetNewField();

	int GetType() { return iType; }

private:
	FieldArray CurrField; //массив на начало движения
	TetroArray aTetro ; // 4 на 4 тетромино
	int iType; // тип тетромино 1 - 7
};

