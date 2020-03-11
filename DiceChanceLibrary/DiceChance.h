#pragma once
namespace Dice{
	enum VsType {
		NoVs, GreaterThan, LessThan, Equals
	};
	// ¬озвращает массив, в котором записано количество возможных совпадений.
	int* GetValueSpread(int cubes, int sides, int &N);

	// ¬озвращает общее количество совпадений
	double GetTotal(int *a, int N);

	// ¬озвращает массив шансов по заданному массиву совпадений
	double* GetChanceArray(int *a, int N);

	// ¬озвращает шанс по заданному массиву совпадений и типу
	double GetChance(int *a, int N, int vsNum, VsType type);

	// —кладывает два массива совпадений и возвращает результат
	int* AddArray(int *a, int Na, int *b, int Nb, int& N);

	// —мещает массив на plus. ѕри смещении элемент с индексом 0 хранит в себе все элементы, индекс которых меньше 0
	void AdjustArray(int *&a, int &N, int plus);
}