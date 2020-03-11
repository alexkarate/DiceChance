#include <iostream>
#include <iomanip>
#include <string>
#include "DiceChance.h"
using namespace std;
using namespace Dice;
// Returns the number of digits in a number
int GetNumberOfDigits(int a) {
	int k = 0;
	while (a > 0) {
		a /= 10; k++;
	}
	return k;
}

// ������� �� ������ � ����� ������ ����� �������� � ���������
void CleanString(std::string &s) {
	int n = 0;
	while (n < s.length() && (s[n] == ' ' || s[n] == '\t')) n++;
	s.erase(0, n);
	n = s.length() - 1;
	while (n >= 0 && (s[n] == ' ' || s[n] == '\t')) n--;
	s.erase(n + 1);
}
// ���������� stoi(s) ��� defaultNum
int SafeStoi(std::string &s, int defaultNum) {
	int result;
	try {
		result = stoi(s);
	}
	catch (const std::exception e) {
		result = defaultNum;
	}
	return result;
}

// �������� �� ������ ������ ������
bool isNum(char a) {
	return a >= '0' && a <= '9';
}

// ������� � ���������� ��� ������ �����, ���� ������� ����
Dice::VsType GetType(string &s, int &vsNum) {
	VsType vsType = NoVs;
	vsNum = s.find('=');
	if (vsNum != -1) vsType = Equals;
	else {
		vsNum = s.find('>');
		if (vsNum != -1) vsType = GreaterThan;
		else {
			vsNum = s.find('<');
			if (vsNum != -1) vsType = LessThan;
		}
	}
	if (vsType != NoVs) {
		string vsStr = s.substr(vsNum + 1);
		vsNum = SafeStoi(vsStr, -1);
	}
	else vsNum = 0;
	return vsType;
}

// ���������� ���������� ������� � ��������� ��� -1, ���� �� ���
int GetCubes(string &s, int dPos) {
	string cubeStr = s.substr(0, dPos);
	CleanString(cubeStr);
	return SafeStoi(cubeStr, -1);
}

// ���������� ���������� ������ � ��������� ��� -1, ���� �� ���
int GetSides(string &s, int dPos) {
	int n = 0;
	while (s[dPos + n + 1] == ' ' || isNum(s[dPos + n + 1])) n++;
	string sideStr = s.substr(dPos + 1, n);
	CleanString(sideStr);
	return SafeStoi(sideStr, -1);
}

// ���������� ����������� ��� 0, ���� ��� ���
int GetPlus(string &s) {
	int op = s.find('+');
	if (op == -1) op = s.find('-');
	if (op == -1) return 0;

	int n = 1;
	while (s[op + n] == ' ' || isNum(s[op + n])) n++;
	string opStr = s.substr(op, n);
	CleanString(opStr);
	return SafeStoi(opStr, 0);
}

int main() {
	int cubes, sides, plus, vsNum;
	string s;
	bool sucess;
	VsType vsType;
	cout << "Please input the expression: ";
	do {
		getline(cin, s);
		CleanString(s);
		int dicePos = s.find('d');
		cubes  = GetCubes(s, dicePos);
		sides  = GetSides(s, dicePos);
		vsType = GetType(s, vsNum);
		plus   = GetPlus(s);
		sucess = dicePos != -1 && cubes > 0 && sides > 0 && vsNum >= 0;
		if (!sucess) cout << "Invalid input. Please try again: ";
	} while (!sucess);
	int N;
	int *a;
	a = GetValueSpread(cubes, sides, N);
	AdjustArray(a, N, plus);
	double *chances = GetChanceArray(a, N);
	double chance = GetChance(a, N, vsNum, vsType);
	if (vsType)
		cout << fixed << chance * 100 << '%' << endl;
	for (int i = 1; i < N; i++)
		if(chances[i]>0)
			cout << setw(GetNumberOfDigits(N)) << i << ' ' << fixed << chances[i] * 100  << '%'<< endl;
	if (abs(chances[0] - 1) < 0.00001) cout << "No results";
	delete[] a;
	cin.get();
}
