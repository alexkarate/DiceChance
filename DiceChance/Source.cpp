#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
typedef long long llong;

// Возможные виды вывода шанса
enum VsType{
	NoVs, GreaterThan, LessThan, Equals
};

// Возвращает массив, в котором записано количество возможных совпадений.
int* GetValueSpread(int cubes, int sides, int &N) {
	if (cubes < 1 || sides < 1) return NULL;

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
	for (int i = cubes; i < N; i++) {
		if (result[i] < 0) throw overflow_error("Too many possible values");
	}
	return result;
}

// Возвращает общее количество совпадений
double GetTotal(int *a, int N) {
	double total = 0;
	for (int i = 0; i < N; i++) total += a[i];
	return total;
}

// Возвращает массив шансов по заданному массиву совпадений
double* GetChanceArray(int *a, int N) {
	double total = GetTotal(a, N);
	double* chance = new double[N];
	for (int i = 0; i < N; i++)
		chance[i] = a[i] / total;
	return chance;
}

// Возвращает шанс по заданному массиву совпадений и типу
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

// Складывает два массива совпадений и возвращает результат
int* AddArray (int *a, int Na, int *b, int Nb, int& N) {
	N = Na + Nb - 1;
	int *c = new int[N];
	for (int i = 0; i < N; i++)
		c[i] = 0;
	for (int i = 1; i < Na; i++)
		for (int j = 1; j < Nb; j++)
			c[i + j] += a[i] * b[j];
	return c;
}

// Удаляет из начала и конца строки знаки пробелов и табуляции
void CleanString(string &s) {
	int n = 0;
	while (n < s.length() && (s[n] == ' ' || s[n] == '\t')) n++;
	s.erase(0, n);
	n = s.length() - 1;
	while (n >= 0 && (s[n] == ' ' || s[n] == '\t')) n--;
	s.erase(n+1);
}

// Находит и возвращает тип вывода шанса, если таковой есть
VsType GetType(string &s, int &vsNum) {
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
		try { vsNum = stoi(vsStr); }
		catch (const exception &e) { vsNum = -1; }
	}
	else vsNum = 0;
	return vsType;
}

// Возвращает stoi(s) или defaultNum
int SafeStoi(string &s, int defaultNum) {
	int result;
	try {
		result = stoi(s);
	}
	catch (const exception e) {
		result = defaultNum;
	}
	return result;
}

// Возвращает количество кубиков в выражении или -1, если их нет
int GetCubes(string &s, int dPos) {
	string cubeStr = s.substr(0, dPos);
	CleanString(cubeStr);
	return SafeStoi(cubeStr, -1);
}

// Является ли данный символ цифрой
bool isNum(char a) {
	return a >= '0' && a <= '9';
}

// Возвращает количество сторон в выражении или -1, если их нет
int GetSides(string &s, int dPos) {
	int n = 0;
	while (s[dPos + n + 1] == ' ' || isNum(s[dPos + n + 1])) n++;
	string sideStr = s.substr(dPos + 1, n);
	CleanString(sideStr);
	return SafeStoi(sideStr, -1);
}

// Возвращает модификатор или 0, если его нет
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

// Смещает массив на plus. При смещении элемент с индексом 0 хранит в себе все элементы, индекс которых меньше 0
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

// Возвращает количество цифр в числе
int GetNumberOfDigits(int a) {
	int k = 0;
	while (a > 0) {
		a /= 10; k++;
	}
	return k;
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
	try {
		a = GetValueSpread(cubes, sides, N);
	}
	catch (const overflow_error e) {
		cout << e.what();
		cin.get();
		return 0;
	}
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