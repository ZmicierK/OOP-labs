#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
using namespace std;
struct Array
{
	double* vec;	//непосредственно вектор
	unsigned size; //размер вектора
	int last=-1;	   //индекс последнего элемента
};

double* NewArray(int); // Создание нового массива
void Add(Array&, int); // Добавление нового значения в массив
void Del(Array&, int); // Удаление из массива i-го элемента
void Print(Array&); // Вывод элементов массива на экран.
void DelArray(Array&); // Полное освобождение памяти занятой массивом
int menu(); // Меню
int main()
{
	Array temp;
	temp.size = 0;
	temp.last = -1;
	int x, n;
	while (true)
	{
		switch (menu())
		{
		case 1:
			cout << "Enter array size: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (!(cin >> n)) 
			{
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause"); break; 
			}
			if (n <= 0) { cout << "Positive input only" << endl; system("pause"); break; }
			temp.size = n;
			temp.last = -1;
			temp.vec = NewArray(n); break;

		case 2:
			cout << endl << "Enter the element to add: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (!(cin >> x))
			{
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause");break;
			}
			Add(temp, x); break;

		case 3:
			cout << endl << "Enter the element index to del: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (!(cin >> n))
			{
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause"); break;
			}
			Del(temp, n); break;

		case 4:Print(temp); break;

		case 5:DelArray(temp); break;

		case 6:return 0;
		}
		system("cls");
	}
}

int menu()
{
	cout << "Select function:" << endl;
	cout << "1. NewArray" << endl;
	cout << "2. Add" << endl;
	cout << "3. Del" << endl;
	cout << "4. Print" << endl;
	cout << "5. DelArray" << endl;
	cout << "6. Exit" << endl;
	int i = 0;
	if (!(cin >> i))
	{
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); cout << "Input error" << endl; system("pause"); 
		return 0;
	}

	if (i <= 0 || i > 6)
	{
		cout << "Please enter a number from 1 to 6" << endl; system("pause"); return 0;
	}
	return i;
}

double* NewArray(int n)
{
	return new double[n];
}
void Add(Array& temp, int x)
{
	if (static_cast<int>(temp.size) > (temp.last + 1)) temp.vec[++temp.last] = x;
	else { cout << "Out of range" << endl; system("pause"); }
}
void Del(Array& temp, int x)
{
	if ((x < 0) || (x > temp.last))
	{
		cout << "The element with index " << x << " does not exist" << endl; system("pause");
	}
	else
	{
		for (int i = x; i < temp.last; i++) temp.vec[i] = temp.vec[i + 1];
		temp.last--;
	}
}
void Print(Array& temp)
{
	cout << "Array:" << endl;
	for (int i = 0; i <= temp.last; i++)
	{
		cout << "[" << i << "] = " << temp.vec[i] << endl;
	}
	system("pause");
}
void DelArray(Array& temp)
{
	if (temp.last == -1) 
	{
		cout << "Nothing to Del"<<endl; system("pause");
	}
	else 
	{
		temp.last = -1; temp.size = 0;
		delete[]temp.vec;
	}
}