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

	void Rotate();
	void ForceRotate();

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
	int GetType() { return iType; }

private:
	FieldArray CurrField; //массив на начало движения
	TetroArray aTetro ; // 4 на 4 тетромино
	int iType; // тип тетромино 1 - 7
	int xPos = 3;
	int yPos = 0;
};

