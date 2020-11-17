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
	Array() { size = 0; arr = NULL;}
	void Init(int sizeInp) 
	{
		if (sizeInp <= 0) { cout << "Positive input only"; system("pause"); }
		else arr = new double[sizeInp]; size = sizeInp;
	};
	void Set(int index, int val)
	{
		if (index >= size) { cout << "Out of range" << endl; system("pause"); }
		else arr[index] = val;
	};
	void Get(int index)
	{
		if (index >= size) { cout << "Out of range" << endl; system("pause"); }
		else { cout << arr[index] << endl; system("pause"); }
	};
	friend void Print(Array&);
	void DelArray() {
		if (size) { delete[]arr; size = 0; cout << "Memory cleared" << endl; system("pause"); }
		else { cout << "nothing to del" << endl; system("pause"); }
};
};

void Print(Array& mas)
{
	for (int i = 0; i < mas.size; i++)
	{
		cout << "mas[" << i << "] = " << mas.arr[i] << endl;
	}
	system("pause");
}

int main()
{
	Array mas;
	int x, n;
	while (true)
	{
		switch (menu())
		{
		case 1:
			cout << "Enter array size: ";
			if (!(cin >> n))
			{
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause"); break;
			}
			if (n <= 0) { cout << "Positive input only" << endl; system("pause"); break; }
			mas.Init(n); break;
		case 2:
			cout << endl << "Enter the element index to set: ";
			if (!(cin >> n) || (n < 0))
			{
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause"); break;
			}
			cout << endl << "Enter the element value to set: ";
			if (!(cin >> x))
			{
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause"); break;
			}
			mas.Set(n, x); break;
		case 3:
			cout << endl << "Enter the element index to get: ";
			if (!(cin >> n))
			{
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause"); break;
			}
			if (n < 0) {cout << "Positive input only" << endl; system("pause"); break; }
			mas.Get(n); break;
		case 4:Print(mas); break;
		case 5:mas.DelArray(); break;
		case 6: return 0;
		}
		system("cls");
	}
	return 0;
}

int menu()
{
	cout << "Select function:" << endl;
	cout << "1. NewArray" << endl;
	cout << "2. Set" << endl;
	cout << "3. Get" << endl;
	cout << "4. Print" << endl;
	cout << "5. DelArray" << endl;
	cout << "6. Exit" << endl;
	int i;
	
	if (!(cin >> i)) 
	{
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause"); return 0;
	}
	if (i <= 0 || i > 6)
	{
		cout << "Please enter a number from 1 to 6" << endl; system("pause"); return 0;
	}
	return i;
}
