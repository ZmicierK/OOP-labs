#include <iostream>
#include <math.h>

#define PI 3.14159265


using namespace std;

class Trans
{
public:
	double Sin(double& angle); //синус
	double Cos(double& angle); //косинус
	double Tan(double& angle); //тангенс
	double Asin(double& sn);   //арксинус
	double Acos(double& cs);   //арккосинус
	double Atan(double& tg);   //арктангенс
	double Ln(double& value);  //натуральный логарифм
	double Lg(double& value);  //десятичный логарифм
};


//трансцендентные исключения (см задание 1)
class TransException
{
protected:
	double* value = NULL;
	char opname[10];
public:
	TransException() : value(0), opname("-") {}
	TransException(const char* nameop, double* val)
	{
		strcpy_s(opname, nameop);
		value = val;
	}
	virtual void Message() { cerr << "Input error"; };
	virtual void Handler()
	{
		cout << "Please enter another value: ";
		cin >> *value;
		cout << "New value: " << *value << endl;
	}
};
//исключения логарифмических функций
class LogException : public TransException
{
public:
	LogException() : TransException() {}
	LogException(const char* nameop, double* val) : TransException(nameop, val) {}

	virtual void Message()
	{
		cout << "Something wrong with " << opname << ". Value " << *value << " is out of range" << endl;
	}
	void get_value(double val)
	{
		*value = val;
	}
};
//исключения тригонометрических функций
class TrigException : public TransException
{
public:
	TrigException() : TransException() {}
	TrigException(const char* nameop, double* val) :TransException(nameop, val) {}
	virtual void Message()
	{
		cout << "Something wrong with " << opname << ". Value " << *value << " is out of range" << endl;
	}
};

int main()
{
	double acos = 2, asin = 2, cos = 0, tan = 90, ln = 1;

	Trans test;
	while (true)
	{
		try
		{
			cout << "Test with functions:\n";
			cout << "Acos = " << test.Acos(acos) << endl;
			cout << "Asin  = " << test.Asin(asin) << endl;
			cout << "Cos = " << test.Cos(cos) << endl;
			cout << "Tan = " << test.Tan(tan) << endl;
			cout << "ln = " << test.Ln(ln) << endl;
			cout << "End without errors";
			break;
		}
		catch (TransException & p)
		{
			p.Message();
			p.Handler();
			system("cls");
		}
	}
}


double Trans::Acos(double& val)
{
	if (val < -1 || val > 1) throw TrigException("Acos", &val);
	return acos(val);
}
double Trans::Asin(double& val)
{
	if (val < -1 || val > 1) throw TrigException("Asin", &val);
	return acos(val);
}
double Trans::Atan(double& val)
{
	return atan(val);
}
double Trans::Cos(double& val)
{
	if (cos(val * PI / 180) <= 1.7949e-09) return 0;
	return cos(val * PI / 180);
}
double Trans::Sin(double& val)
{
	if (sin(val * PI / 180) <= 3.58979e-09) return 0;
	return sin(val * PI / 180);
}
double Trans::Tan(double& val)
{
	if (cos(val * PI / 180) <= 1.7949e-09) throw TrigException("Tan", &val);
	return tan(val * PI / 180);
}
double Trans::Ln(double& val)
{
	if (val < 0 || val == 1) throw LogException("Ln", &val);
	return log(val);

}
double Trans::Lg(double& val)
{
	if (val < 0 || val == 1) throw  LogException("Log", &val);
	return	log10(val);
}