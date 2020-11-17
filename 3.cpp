#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
using namespace std;
int menu();
class Array
{
	double* arr;	//непосредственно массив
	unsigned size;	//размер массива
public:
	Array() { size = 0; arr = NULL; }//конструктор по ум.
	Array(unsigned sizeInp) { arr = new double[sizeInp]; size = sizeInp; }//конструктор с парам.
	Array(const Array& t)
	{
		size = t.size;
		arr = new double[size];
		for (int i = 0; i < size; i++) arr[i] = t.arr[i];
	}//конструктор копир.
	void Init(int sizeInp) {
		if (sizeInp <= 0) { cout << "Positive input only"; system("pause"); }
		else arr = new double[sizeInp]; size = sizeInp;
	};
	void Set(int index, int val)
	{
		if (index >= size || index < 0) { cout << "Out of range" << endl; system("pause"); }
		else arr[index] = val;
	};
	void Get(int index)
	{
		if (index >= size || index < 0) { cout << "Out of range" << endl; system("pause"); }
		else { cout << arr[index] << endl; system("pause"); }
	};
	friend void Print(Array&);
	void DelArray() { delete[]arr; size = 0; cout << "Memory cleared" << endl; system("pause"); };
	~Array() { cout << endl << "Destruct " << this << endl; delete[]arr; size = 0; }//деструктор
};

void Print(Array& mas)
{
	for (int i = 0; i < mas.size; i++)
	{
		cout << "mas[" << i << "] = " << mas.arr[i] << endl;
	}
	system("pause");
}

void copydemo(Array& mascpy)
{
	Array othermas(mascpy);
	cout << "Print for " << &mascpy << endl;
	Print(mascpy);
	cout << "Print for " << &othermas << endl;
	Print(othermas);
}
int main()
{
	int x, n;
	cout << "Enter array size: ";
	while (!(cin >> n) || n <= 0)
	{
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause");
		system("cls"); cout << "Enter array size: ";
	}
	Array mas(n);
	system("cls");
	while (true)
	{
		switch (menu())
		{
		case 1:
			cout << endl << "Enter the element index to set: ";
			if (!(cin >> n) || (n < 0))
			{
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause"); break;
			}
			if (n < 0) {cout << "Positive input only" << endl; system("pause"); break; }
			cout << endl << "Enter the element value to set: ";
			if (!(cin >> x))
			{
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause"); break;
			}
			mas.Set(n, x); break;
		case 2:
			cout << endl << "Enter the element index to get: ";
			if (!(cin >> n))
			{
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause"); break;
			}
			if (n < 0) {	cout << "Positive input only" << endl; system("pause"); break; }
			mas.Get(n); break;
		case 3:Print(mas);  break;
		case 4:copydemo(mas); system("pause"); break;
		case 5: return 0;
		}
		system("cls");
	}
	return 0;
}

int menu()
{
	cout << "Select function:" << endl;
	cout << "1. Set" << endl;
	cout << "2. Get" << endl;
	cout << "3. Print" << endl;
	cout << "4. CopyDemo" << endl;
	cout << "5. Exit" << endl;
	int i;
	if (!(cin >> i))
	{
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause"); return 0;
	}
	if (i < 1 || i > 5)
	{
		cout << "Please enter a number from 1 to 5" << endl; system("pause"); return 0;
	}
	return i;
}