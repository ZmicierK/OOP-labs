#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
using namespace std;
int menu();
template <class T>
class Vector
{
	double* vec;	//непосредственно вектор
	unsigned size;	//размер вектора
	int last;		//индекс последнего элемента
public:
	Vector() { size = 0; last = -1; vec = NULL; }//конструктор по ум.
	Vector(unsigned sizeInp) { vec = new double[sizeInp]; size = sizeInp; last = -1; }//конструктор с парам.
	~Vector() {delete[]vec; size = 0; }//деструктор
	bool IsElementHere(int i) 
	{ 
		return (i<=last && i>=0); 
	}
	double& operator[](int i)
	{
		if (i > last || i<0) { cout << "Boundary Error" << endl; exit(1); };
		return vec[i];
	}//получение доступа к элементу массива([])

	friend istream& operator>>(istream& is, Vector<T>& mas) 
	{
		is >> mas.vec[++mas.last];
		if (!is) mas.last--;
		return is;
	}//ввод значений(>>)
	friend ostream& operator<<(ostream& os, Vector<T>& mas)
	{
		for (int i = 0; i <= mas.last; i++)
		{
			os << "mas[" << i << "] = " << mas.vec[i] << endl;
		}
		return os;
	}//вывод массива(<<)
};

int main()
{
	int x, n, i;
	cout << "Enter vector size: ";
	while (!(cin >> n) || n <= 0)
	{
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause");
		system("cls"); cout << "Enter vector size: ";
	}	
	Vector<int> mas(n);
	cout << "Vector input:" << endl;
	for (i = 0; i < n; i++)
	{
		cout << "mas[" << i << "]= ";
		if (!(cin >> mas))
		{
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; i--;
		}
	}
	system("cls");
	while (true)
	{
		switch (menu())
		{
		case 1:
			cout << "Enter index: ";
			while (!(cin >> n) || !mas.IsElementHere(n))
			{
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl<< "Enter correct index: ";
			}
			cout <<"mas["<<n<<"]= "<< mas[n]<<endl; system("pause"); break;
		case 2: cout << mas; system("pause"); break;
		case 3: return 0;
		}
		system("cls");
	}
	return 0;
}

int menu()
{
	cout << "Select function:" << endl;
	cout << "1. Vector get by index" << endl;
	cout << "2. Vector output" << endl;
	cout << "3. Exit" << endl;
	int i;
	if (!(cin >> i))
	{
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause"); return 0;
	}
	if (i < 1 || i > 3)
	{
		cout << "Please enter a number from 1 to 3" << endl; system("pause"); return 0;
	}
	return i;
}