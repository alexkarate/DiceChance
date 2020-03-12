#pragma once
namespace Dice{
	enum VersusType {
		NoVersus, GreaterThan, LessThan, Equals
	};
	// Returns a match array, or an array, where each position corresponds to the number of possible dice throws, 
	// the result of which equals to that position.
	int* GetValueSpread(int cubes, int sides, int &NResult);

	// Returns the number of all matches
	double GetTotal(int *matchArray, int N);

	// Returns a chance array, given a match array
	double* GetChanceArray(int *matchArray, int N);

	// Returns the chance, given a match array, the type of comparison and a number to compare to
	double GetChance(int *matchArray, int N, int vsNum, VersusType type);

	// Adds two match arrays, the result is a match array
	int* AddArray(int *matchArrayA, int Na, int *matchArrayB, int Nb, int& NResult);

	// Shifts the array to the right (or left) by 'plus'. Values with position less than 0 are kept in 0
	void AdjustArray(int *&matchArray, int &N, int plus);
}
