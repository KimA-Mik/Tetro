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
	~Tetromino();

	//void StartMoving(FieldArray StartArray);

	void Rotate();

	void StartMoving(FieldArray& Field);

	//Передвигают массив, возвращая поле на отрисовку
	void MoveLeft();
	void MoveRight();
	bool MoveDown();

	TetroArray GetFigure();

	bool DoesItFit(int x, int y);
	bool DoesItFitRotated(TetroArray& Rotated);

	FieldArray GetNewField();

	void SetXPos(int x) { xPos = x; }
	void SetYPos(int y) { yPos = y; }

private:
	FieldArray CurrField; //массив на начало движения
	TetroArray aTetro ; // 4 на 4 тетромино
	int iType; // тип тетромино 1 - 7
	int xPos = 5;
	int yPos = 0;
};

