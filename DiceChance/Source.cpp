#include <iostream>
#include <iomanip>
#include <string>
#include "DiceChance.h"
using namespace std;
using namespace Dice;

// Returns the amount of digits in a number
int GetNumberOfDigits(int number) {
	int digits = 0;
	while (number > 0) {
		number /= 10; digits++;
	}
	return digits;
}

// Deletes spaces from the front and the back of the string
void CleanString(string &str) {
	int count = 0;
	while (count < str.length() && (str[count] == ' ' || str[count] == '\t')) count++;
	str.erase(0, count);
	count = str.length() - 1;
	while (count >= 0 && (str[count] == ' ' || str[count] == '\t')) count--;
	str.erase(count + 1);
}
// Returns stoi(str) or defaultNumber
int SafeStoi(string &str, int defaultNumber) {
	int result;
	try {
		result = stoi(str);
	}
	catch (const exception e) {
		result = defaultNumber;
	}
	return result;
}

// Returns true if the character is a digit
bool isDigit(char a) {
	return a >= '0' && a <= '9';
}

// Returns the type of comparison that is used and the number to compare to
VersusType GetType(string &str, int &versusNumber) {
	VersusType versusType = NoVersus;
	versusNumber = str.find('=');
	if (versusNumber != -1) versusType = Equals;
	else {
		versusNumber = str.find('>');
		if (versusNumber != -1) versusType = GreaterThan;
		else {
			versusNumber = str.find('<');
			if (versusNumber != -1) versusType = LessThan;
		}
	}
	if (versusType != NoVersus) {
		string versusStr = str.substr(versusNumber + 1);
		versusNumber = SafeStoi(versusStr, -1);
	}
	else versusNumber = 0;
	return versusType;
}

// Returns the number of cubes in an expression or -1 if none
int GetCubes(string &str, int dicePos) {
	string cubeStr = str.substr(0, dicePos);
	CleanString(cubeStr);
	return SafeStoi(cubeStr, -1);
}

// Returns the number of sides in an expression or -1 if none
int GetSides(string &str, int dicePos) {
	int count = 0;
	while (str[dicePos + count + 1] == ' ' || isDigit(str[dicePos + count + 1])) count++;
	string sideStr = str.substr(dicePos + 1, count);
	CleanString(sideStr);
	return SafeStoi(sideStr, -1);
}

// Returns the addition (or subtraction) in an expression, or 0 if none
int GetPlus(string &str) {
	int op = str.find('+');
	if (op == -1) op = str.find('-');
	if (op == -1) return 0;

	int count = 1;
	while (str[op + count] == ' ' || isDigit(str[op + count])) count++;
	string opStr = str.substr(op, count);
	CleanString(opStr);
	return SafeStoi(opStr, 0);
}

int main() {
	int cubes, sides, plus, versusNumber;
	string str;
	bool sucess;
	VersusType versusType;
	cout << "Please input the expression: ";
	do {
		getline(cin, str);
		CleanString(str);
		int dicePos = str.find('d');
		cubes  = GetCubes(str, dicePos);
		sides  = GetSides(str, dicePos);
		versusType = GetType(str, versusNumber);
		plus   = GetPlus(str);
		sucess = dicePos != -1 && cubes > 0 && sides > 0 && versusNumber >= 0;
		if (!sucess) cout << "Invalid input. Please try again: ";
	} while (!sucess);
	int N;
	int *a;
	a = GetValueSpread(cubes, sides, N);
	AdjustArray(a, N, plus);
	double *chances = GetChanceArray(a, N);
	double chance = GetChance(a, N, versusNumber, versusType);
	if (versusType)
		cout << fixed << chance * 100 << '%' << endl;
	int idWidth = GetNumberOfDigits(N);
	for (int i = 0; i < N; i++)
		if(chances[i]>0)
			cout << setw(idWidth) << i << ": " << fixed << chances[i] * 100  << '%' << endl;
	if (abs(chances[0] - 1) < 0.00001) cout << "No results";
	delete[] a;
	cin.get();
}
