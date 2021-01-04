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
	bool DoesItFit();

	//Передвигают массив, возвращая поле на отрисовку
	//FieldArray MoveLeft();
	//FieldArray MoveRight();
	//FieldArray MoveDown(bool* Succes);

	//FieldArray GetCurrField();


private:
	FieldArray CurrField; //массив на начало движения
	TetroArray aTetro ; // 4 на 4 тетромино
	int iType; // тип тетромино 1 - 7
};

