#include "DiceChance.h"
namespace Dice {
	// Returns a match array, an array, where each position corresponds to the number of possible dice throws, 
	// the result of which equals to that position.
	int* GetValueSpread(int cubes, int sides, int &NResult) {
		if (cubes < 1 || sides < 1) return nullptr;

		NResult = cubes * sides + 1;
		int **matchArray = new int*[cubes + 1];
		for (int i = 0; i <= cubes; i++)
			matchArray[i] = new int[NResult];

		for (int i = 0; i <= cubes; i++)
			for (int j = 0; j < NResult; j++)
				matchArray[i][j] = 0;
		for (int j = 1; j <= sides; j++) matchArray[1][j] = 1;

		for (int i = 2; i <= cubes; i++) {
			for (int j = i; j <= i * sides; j++)
				matchArray[i][j] = matchArray[i][j - 1] + matchArray[i - 1][j - 1] - matchArray[i - 1][i * (sides + 1) - j];
		}

		int* result = matchArray[cubes];
		for (int i = 0; i < cubes; i++)
			delete[] matchArray[i];
		delete[] matchArray;
		return result;
	}

	// Returns the number of matches
	double GetTotal(int *matchArray, int N) {
		double total = 0;
		for (int i = 0; i < N; i++) total += matchArray[i];
		return total;
	}

	// Returns a chance array, given a match array
	double* GetChanceArray(int *matchArray, int N) {
		double total = GetTotal(matchArray, N);
		double* chance = new double[N];
		for (int i = 0; i < N; i++)
			chance[i] = matchArray[i] / total;
		return chance;
	}

	// Returns the chance, given a match array, the type of comparison and a number to compare to
	double GetChance(int *matchArray, int N, int versusNumber, VersusType versusType) {
		double total = GetTotal(matchArray, N);
		double chance = 0;
		int id = 0;
		while (id <= versusNumber)
			chance += matchArray[id++] / total;
		switch (versusType) {
		case Equals:
			return matchArray[versusNumber] / total;
		case LessThan:
			return chance;
		case GreaterThan:
			chance = 1 - chance;
			chance += matchArray[versusNumber] / total;
			return chance;
		}
		return 0;
	}

	// Adds two match arrays, the result is a match array
	int* AddArray(int *matchArrayA, int Na, int *matchArrayB, int Nb, int& NResult) {
		NResult = Na + Nb - 1;
		int *matchArrayResult = new int[NResult];
		for (int i = 0; i < NResult; i++)
			matchArrayResult[i] = 0;
		for (int i = 1; i < Na; i++)
			for (int j = 1; j < Nb; j++)
				matchArrayResult[i + j] += matchArrayA[i] * matchArrayB[j];
		return matchArrayResult;
	}

	// Shifts the array to the right (or left) by 'plus'. Values with position less than 0 are kept in 0
	void AdjustArray(int *&matchArray, int &N, int plus) {
		if (plus == 0) return;
		int *matchArrayResult, NResult = N;
		if (plus > 0)
			NResult += plus;
		matchArrayResult = new int[NResult];
		for (int i = 0; i < NResult; i++)
			matchArrayResult[i] = 0;
		for (int i = 0; i < N; i++) {
			int id = i + plus;
			if (id < 0) id = 0;
			matchArrayResult[id] += matchArray[i];
		}
		N = NResult;
		int *t = matchArray;
		matchArray = matchArrayResult;
		delete[] t;
	}
}
