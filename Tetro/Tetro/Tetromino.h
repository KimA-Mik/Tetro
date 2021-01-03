#pragma once
#include <array>
//
//Сам тетромино
class Tetromino
{
public:
	Tetromino();
	~Tetromino();
	void Rotate();
	void R2();
	bool DoesItFit();

private:
	std::array<std::array<int, 4>, 4> aTetro ; // 4 на 4 тетромино
	int iType; // тип тетромино 1 - 7
};

