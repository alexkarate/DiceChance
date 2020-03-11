#pragma once
namespace Dice{
	enum VsType {
		NoVs, GreaterThan, LessThan, Equals
	};
	// Returns a match array, or an array, where each position corresponds to the number of possible dice throws, 
	// the result of which equals to that position.
	int* GetValueSpread(int cubes, int sides, int &N);

	// Returns the number of all matches
	double GetTotal(int *a, int N);

	// Returns a chance array, given a match array
	double* GetChanceArray(int *a, int N);

	// Returns the chance, given a match array, the type of comparison and a number to compare to
	double GetChance(int *a, int N, int vsNum, VsType type);

	// Adds two match arrays, the result is a match array
	int* AddArray(int *a, int Na, int *b, int Nb, int& N);

	// Shifts the array to the right (or left) by 'plus'. Values with position less than 0 are kept in 0
	void AdjustArray(int *&a, int &N, int plus);
}
