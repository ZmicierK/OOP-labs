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
	int last;		//индекс последнего элемента
public:
	Array() { size = 0; last = -1; arr = NULL; }//конструктор по ум.
	Array(unsigned sizeInp) { arr = new double[sizeInp]; size = sizeInp; last = -1; }//конструктор с парам.
	~Array() { /*cout << endl << "Destruct " << this << endl;*/ delete[]arr; size = 0; }//деструктор
	bool IsElementHere(int i)
	{
		return (i <= last && i >= 0);
	}
	Array& operator=(const Array& other)
	{
		size = other.size;
		last = other.last;
		if (arr != NULL)
		{
			delete[]arr;
		}
		arr = new double[size];
		for (int i = 0; i < size; i++) arr[i] = other.arr[i];
		return *this;
	}//копирование массива(=)

	Array& operator+=(const Array& other)
	{
		if (!other.size)
		{
			cout << "The array to be added is empty ";
		}
		else
		{
			double* temp;
			int i, j = 0;
			temp = new double[size + other.size];
			for (i = 0; i < size; i++)
			{
				temp[i] = arr[i];
			}
			delete[]arr;
			for (i = size; i < size + other.size; i++)
			{
				temp[i] = other.arr[j++];
			}
			arr = temp;
			size += other.size;
			last += other.size;
		}
		return *this;
	}//добавление массива(+=)

	Array& operator+=(double x)
	{
		last++;
		double* temp;
		int i;
		temp = new double[size + 1];
		for (i = 0; i < size; i++)
		{
			temp[i] = arr[i];
		}
		delete[]arr;
		arr = temp;
		arr[size++] = x;
		return *this;
	}//добавление нового элемента в массив(+=)

	double& operator[](int i)
	{
		if (i > last||i<0) { cout << "Boundary Error" << endl; exit(1); };
		return arr[i];
	}//получение доступа к элементу массива([])

	friend istream& operator>>(istream& is, Array&);//ввод значений(>>)
	friend ostream& operator<<(ostream& os, Array&);//вывод массива(<<)
};

istream& operator>>(istream& is, Array& mas)
{
	is >> mas.arr[++mas.last];
	if (!is) mas.last--;
	return is;
}//ввод значений(>>)

ostream& operator<<(ostream& os, Array& mas)
{
	for (int i = 0; i <= mas.last; i++)
	{
		os << "mas[" << i << "] = " << mas.arr[i] << endl;
	}
	return os;
}//вывод массива(<<)

void CopyAcces_Demo(Array& mascpy)
{
	int i, x;
	Array othermas;
	othermas = mascpy;
	cout << "Print for " << &mascpy << endl;
	cout << mascpy;
	cout << endl << "Enter the element index to set: ";
	while (!(cin >> i) || !othermas.IsElementHere(i))
	{
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Input error" << endl << "Enter the element index to set: ";
	}
	cout << "Enter the element value to set: ";
	while (!(cin >> x))
	{
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Input error" << endl << "Enter the element value to set: ";
	}
	othermas[i] = x;
	cout << "Print for " << &othermas << endl;
	cout << othermas;
	system("pause");
}

int main()
{
	int x, n, i;
	cout << "Enter array size: ";
	while (!(cin >> n) || n <= 0)
	{
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; system("pause");
		system("cls"); cout << "Enter array size: ";
	}
	Array mas(n);
	cout << "Array input:" << endl;
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
		case 1:cout << mas; system("pause"); break;
		case 2:int temp;
			cout << "Enter the element to add: ";
			while (!(cin >> temp))
			{
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl << "Enter the element to add: ";
			}
			mas += temp; break;
		case 3:
		{int n;
		cout << "Enter array size: ";
		while (!(cin >> n) || n <= 0)
		{
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl;
			cout << "Enter array size: ";
		}
		Array b(n);
		cout << "Array input:" << endl;
		for (i = 0; i < n; i++)
		{
			cout << "mas[" << i << "]= ";
			if (!(cin >> b))
			{
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Input error" << endl; i--;
			}
		}
		mas += b;
		}  break;
		case 4: CopyAcces_Demo(mas); break;
		case 5: return 0;
		}
		system("cls");
	}
	return 0;
}

int menu()
{
	cout << "Select function:" << endl;
	cout << "1. Array output" << endl;
	cout << "2. Adding element" << endl;
	cout << "3. Adding array" << endl;
	cout << "4. CopyAcces_Demo" << endl;
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
