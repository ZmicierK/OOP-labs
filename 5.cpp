#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <ctime>
using namespace std;

class Weapon
{
protected:
	//имя
	char name[20];
	//сила удара
	int blow_power;
	//сила защиты
	int protect_power;
public:
	//конструктор
	Weapon(int bp, int pp,const char nameget[])
	{
		strcpy_s(name, nameget);
		//name[]=nameget;
		blow_power = bp;
		protect_power = pp;
	}
	//ударить
	virtual int Strike() { return 0; };//заглушка
	//защититься
	virtual int Protect(int power) { return 0; };
	//возвратить имя оружия
	char* GetName() {};
};


class Shield :public Weapon //щит
{
public:
	Shield() :Weapon(0, 10, "Shield") {};
	int Protect(int power)
	{
		int new_protect_power = rand() % protect_power;
		protect_power -= new_protect_power / 10;
		power -= new_protect_power;
		if (power > 0) return power; else return 0;
	}
};


class Club :public Weapon //дубинка
{
public:
	Club() :Weapon(150, 0, "Club") {};
	int Strike()
	{
		int new_blow_power = (rand() % blow_power);
		blow_power -= new_blow_power / 10;
		return new_blow_power;
	}
};


class Sword :public Weapon //меч
{
public:
	Sword() :Weapon(200, 0, "Sword") {};
	int Strike()
	{
		int new_blow_power = (rand() % blow_power);
		blow_power -= new_blow_power / 10;
		return new_blow_power;
	}
};


class Personage
{
protected:
	//имя
	char name[20];
	//здоровье
	int health;
	//оружие нападения
	Weapon* weapon_attack;
	//оружие защиты
	Weapon* weapon_guard;
public:
	Personage(const char nameget[], int Healget) 
	{
			int i;
			cout << "Select weapon attack:\n1.Club\n2.Sword\n";
			while (!(cin >> i) || i < 1 || i >2)
			{
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Input error" << endl << "Select weapon attack:\n1.Club\n2.Sword\n";
			}
			switch (i)
			{
			case 1: weapon_attack = new Club; break;
			case 2: weapon_attack = new Sword; break;
			}
			weapon_guard=new Shield;
		strcpy_s(name, nameget); health = Healget;
	};
	virtual void Attack(Personage*) {};
	virtual void Guard(int) {};
	//false – игрок еще жив, иначе true
	bool IsDead() { return (health <= 0); }
	char* get_name() { return name; }
	~Personage() { delete weapon_attack; delete weapon_guard; }
};


class Warrior :public Personage //воин
{
public:
	Warrior() :Personage("Warrior", 400) {}
	void Attack(Personage* pers)
	{
		int blow = weapon_attack->Strike();
		int luck;
		if (!blow) luck = 0;
		else luck = (0 - blow / 2) + rand() % blow;
		cout << "Attack: " << name << " Blow power: " << blow << " Luck: " << luck;
		blow += luck;
		cout << " Finish blow: " << blow << " Health " << health << endl;
		pers->Guard(blow);
	}
	void Guard(int blow) 
	{
		int damage = weapon_guard->Protect(blow);
		int luck;
		if (!damage) luck = 0;
		else luck = (0 - damage / 2) + (rand() % damage);
		cout << "Guard: " << name << " Damage power: " << damage << " Luck: " << luck;
		damage += luck;
		health -= damage;
		cout << " Finish damage: " << damage << " Health " << health << endl;
	};
};


class Monster :public Personage //монстр
{
public:
	Monster() :Personage("Monster", 500) {}
	void Attack(Personage* pers)
	{
		int blow = weapon_attack->Strike();
		int luck;
		if (!blow) luck = 0;
		else luck = (0 - blow / 2) + rand() % blow;
		cout << "Attack: " << name <<" Blow power: "<< blow << " Luck: " << luck;
		blow += luck;
		cout << " Finish blow: " << blow << " Health " << health << endl;
		pers->Guard(blow);
	}
	void Guard(int blow)
	{
		int damage = weapon_guard->Protect(blow);
		int luck;
		if (!damage) luck = 0;
		else luck = (0 - damage / 2) + (rand() % damage);
		cout << "Guard: " << name << " Damage power: " << damage << " Luck: " << luck;
		damage += luck;
		health -= damage;
		cout << " Finish damage: " << damage << " Health " << health << endl;
	};
};

class Combat
{
	Personage* p1; //игрок 1
	Personage* p2; //игрок 2
	Personage* a_player; //атакующий игрок
	Personage* g_player; //защищающийся игрок
public:
	Combat()
	{
		p1 = NULL; p2 = NULL;
		a_player = NULL;
		g_player = NULL;
		int i;
		cout << "Select 1 personage:\n1.Warrior\n2.Monster\n";
		while (!(cin >> i)||i<1||i >2 )
		{
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input error" << endl << "Select 1 personage:\n1.Warrior\n2.Monster\n";
		}
		switch (i)
		{
			case 1: p1 = new Warrior; break;
			case 2: p1 = new Monster; break;
		}
		cout << "Select 2 personage:\n1.Warrior\n2.Monster\n";
		while (!(cin >> i) || i < 1 || i >2)
		{
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input error" << endl << "Select 2 personage:\n1.Warrior\n2.Monster\n";
		}
		switch (i)
		{
		case 1: p2 = new Warrior; break;
		case 2: p2 = new Monster; break;
		}
	};
	~Combat() { delete p1; delete p2; };
	void Start() 
	{
		srand(time(0));
		int i=0;
		while (true)
		{
			if (rand() % 2) { a_player = p1; g_player = p2; }
			else { a_player = p2; g_player = p1; }
			cout << "step " << ++i << endl;
			a_player->Attack(g_player);
			if (g_player->IsDead())
			{
				if (p1 == a_player) 
				{
					cout << endl << "Game over " << a_player->get_name() << "(personage 1) wins"; return;
				}
				else
				{
					cout << endl << "Game over " << a_player->get_name() << "(personage 2) wins"; return;

				}
			}
		}
	};
};



int main()
{
	Combat Comb;
	Comb.Start();
	return 0;
}