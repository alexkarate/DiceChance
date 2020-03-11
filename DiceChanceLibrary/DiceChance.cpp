#include "DiceChance.h"
namespace Dice {
	// Returns a match array, an array, where each position corresponds to the number of possible dice throws, 
	// the result of which equals to that position.
	int* GetValueSpread(int cubes, int sides, int &N) {
		if (cubes < 1 || sides < 1) return nullptr;

		N = sides * cubes + 1;
		int **a = new int*[cubes + 1];
		for (int i = 0; i <= cubes; i++)
			a[i] = new int[sides * cubes + 1];

		for (int i = 0; i <= cubes; i++)
			for (int j = 0; j <= sides * cubes; j++)
				a[i][j] = 0;
		for (int j = 1; j <= sides; j++) a[1][j] = 1;

		for (int i = 2; i <= cubes; i++) {
			for (int j = i; j <= i * sides; j++)
				a[i][j] = a[i][j - 1] + a[i - 1][j - 1] - a[i - 1][i * (sides + 1) - j];
		}

		int* result = a[cubes];
		for (int i = 0; i < cubes; i++)
			delete[] a[i];
		delete[] a;
		return result;
	}

	// Returns the number of matches
	double GetTotal(int *a, int N) {
		double total = 0;
		for (int i = 0; i < N; i++) total += a[i];
		return total;
	}

	// Returns a chance array, given a match array
	double* GetChanceArray(int *a, int N) {
		double total = GetTotal(a, N);
		double* chance = new double[N];
		for (int i = 0; i < N; i++)
			chance[i] = a[i] / total;
		return chance;
	}

	// Returns the chance, given a match array, the type of comparison and a number to compare to
	double GetChance(int *a, int N, int vsNum, VsType type) {
		double total = GetTotal(a, N);
		double chance = 0;
		int k = 1;
		while (k <= vsNum)
			chance += a[k++] / total;
		switch (type) {
		case Equals:
			return a[vsNum] / total;
		case LessThan:
			return chance;
		case GreaterThan:
			chance = 1 - chance;
			chance += a[vsNum] / total;
			return chance;
		}
		return 0;
	}

	// Adds two match arrays, the result is a match array
	int* AddArray(int *a, int Na, int *b, int Nb, int& N) {
		N = Na + Nb - 1;
		int *c = new int[N];
		for (int i = 0; i < N; i++)
			c[i] = 0;
		for (int i = 1; i < Na; i++)
			for (int j = 1; j < Nb; j++)
				c[i + j] += a[i] * b[j];
		return c;
	}

	// Shifts the array to the right (or left) by 'plus'. Values with position less than 0 are kept in 0
	void AdjustArray(int *&a, int &N, int plus) {
		if (plus == 0) return;
		int *b, Nb = N;
		if (plus > 0)
			Nb += plus;
		b = new int[Nb];
		for (int i = 0; i < Nb; i++)
			b[i] = 0;
		for (int i = 0; i < N; i++) {
			int id = i + plus;
			if (id < 0) id = 0;
			b[id] += a[i];
		}
		N = Nb;
		int *t = a;
		a = b;
		delete[] t;
	}
}
