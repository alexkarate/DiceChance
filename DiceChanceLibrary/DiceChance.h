#pragma once
namespace Dice{
	enum VsType {
		NoVs, GreaterThan, LessThan, Equals
	};
	// ���������� ������, � ������� �������� ���������� ��������� ����������.
	int* GetValueSpread(int cubes, int sides, int &N);

	// ���������� ����� ���������� ����������
	double GetTotal(int *a, int N);

	// ���������� ������ ������ �� ��������� ������� ����������
	double* GetChanceArray(int *a, int N);

	// ���������� ���� �� ��������� ������� ���������� � ����
	double GetChance(int *a, int N, int vsNum, VsType type);

	// ���������� ��� ������� ���������� � ���������� ���������
	int* AddArray(int *a, int Na, int *b, int Nb, int& N);

	// ������� ������ �� plus. ��� �������� ������� � �������� 0 ������ � ���� ��� ��������, ������ ������� ������ 0
	void AdjustArray(int *&a, int &N, int plus);
}