// ExaminationVariant12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	float a, b, x;
	int zero = 0;
	cout << "Введите число a:" << endl;
	cin >> a;
	cout << "Введите число b:" << endl;
	cin >> b;
	_asm
	{
		FINIT
		FLD a
		FADD b
		FST x
		fldz
		fcomip st, st(1)
		jz zeronumber
		FLD1 
		FLD x
		FDIV 
		FST x
		jmp exitdd
		zeronumber :
		FLD zero
			FLD1
			FADD
			FST zero
			exitdd :
		FWAIT
	}
	if (zero == 0)
	{
		cout << "1/(a+b)=" << x << endl;
	}
	else
	{
		cout << "Деление на 0 недопустимо" << endl;
	}
	system("pause");
}
