// Game v1.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>

using namespace std;

//.................................Menu..........................................//

void menuForRecruit()
{
	cout << "\n" << "...Выбирете юнита для спавна...";
	cout << "\n" << " (1) - Лёгкая пехота ";		cout << "\n" << " (2) - Тяжёлая пехота";
	cout << "\n" << " (3) - Лучник";				cout << "\n" << " (4) - Арбалетчик";
	cout << "\n" << " (5) - Знатный кавалерист";	cout << "\n" << " (6) - Катафракт";
	cout << "\n";
}

void menuForActualGame()
{
	cout << "\n" << " ...Игровое меню... ";
	cout << "\n" << " (1) - Выбор юнита для взаимодействие ";
	cout << "\n" << " (2) - Состояние выбраного юнита ";
	cout << "\n" << " (3) - Показать актуальную карту ";
	cout << "\n" << " (4) - Заспавнить юнит ";
	cout << "\n" << " (0) - Выход " << "\n";
}

class Object
{
public:
	virtual char unitCreator() const = 0;
};
//....................................База ...........................................//

//....................................Юниты ...........................................//
//..................................Описание пехоты....................................//

class Unit : public Object
{
public:
	int health, armor, attack,
		xPos, yPos,
		id;
	virtual bool riverPass() { return allowRiverPass; }

	virtual bool unreqAttack() { return unrequitedAttack; }

	virtual int getCurrentHealth() { return health; }

	virtual int getCurrentArmor() { return armor; }

	virtual int getCurrentAttack() { return attack; }

	virtual void setxyPos(int x, int y) { xPos = x; yPos = y; }

	virtual void setHealth(int hp) { health = hp; }

	char unitCreator() const override { return unitSign; }

private:

	char unitSign = ' ';
	bool allowRiverPass,
		unrequitedAttack;
};

class Infantry : public Unit
{
public:
	char unitCreator() const = 0;
};

class LightInfantry : public Infantry								
{
public:
	LightInfantry() { health = 50; attack = 60; armor = 30; }

	char unitCreator() const override { return unitSign; }

	bool riverPass() { return allowRiverPass; }
private:
	char unitSign = 'L';
	bool allowRiverPass = true,
		unrequitedAttack = false;
};										

class HeavyInfantry : public Infantry								
{
public:
	HeavyInfantry() { health = 100; attack = 80; armor = 80; }

	char unitCreator() const override { return unitSign; }

	bool riverPass() { return allowRiverPass; }
private:
	char unitSign = 'H';
	bool allowRiverPass = false,
		unrequitedAttack = false;
};										

//.................................... Описание стрелков....................................//

class Skirmishers : public Unit										
{
public:
	char unitCreator() const = 0;
};

class Crossbowman : public Skirmishers                              
{
public:
	Crossbowman() { health = 50; attack = 80; armor = 50; }

	char unitCreator() const override { return unitSign; }

	bool riverPass() { return allowRiverPass; }
private:
	char unitSign = 'C';
	bool allowRiverPass = true,
		unrequitedAttack = true;
};

class Archer : public Skirmishers
{
public:
	Archer() { health = 70; attack = 60; armor = 10; }

	char unitCreator() const override { return unitSign; }

	bool riverPass() { return allowRiverPass; }
private:
	char unitSign = 'A';
	bool allowRiverPass = true,
		unrequitedAttack = true;
};
//.................................... Описание кавалерии....................................//

class Cavalry : public Unit
{
public:
	char unitCreator() const = 0;
};

class NobleHorsman : public Cavalry
{
public:
	NobleHorsman() { health = 100; attack = 100; armor = 15; }

	char unitCreator()  const override { return unitSign; }

private:
	char unitSign = 'N';
	bool allowRiverPass = false,
		unrequitedAttack = false;
};

class Cataphract : public Cavalry
{
public:
	Cataphract() { health = 150; attack = 70; armor = 70; }

	char unitCreator() const override { return unitSign; }

private:
	char unitSign = 'K';
	bool allowRiverPass = false,
		unrequitedAttack = false;
};

//..........................................Ланжшафт........................................//

class Landscape
{
public:
	virtual char terrainCreator() const = 0;
};

class Arable : Landscape
{
public:
	char terrainCreator() const override { return terrainSign; }
	char terrainSign = '#';
};

class Mountain : Landscape
{
public:
	char terrainCreator() const override { return terrainSign; }
	char terrainSign = '^';
};

class River : public Landscape
{
public:
	char terrainCreator() const override { return terrainSign; }
	char terrainSign = '~';
};

class Hill : public Landscape
{
public:
	char terrainCreator() const override { return terrainSign; }
	char terrainSign = '=';
};

class Forest : public Landscape
{
public:
	char terrainCreator() const override { return terrainSign; }
	char terrainSign = '%';
};

//............................................Карта.........................................//

class MapForBattlefield
{
public:
	int row,
		col;
	char** field;
	MapForBattlefield(int colM, int rowM)
	{
		col = colM;
		row = rowM;
		createNfill();
	}

	void createNfill()
	{
		field = new char*[col];
		for (int c = 0; c < col; c++)
		{
			field[c] = new char[row];
		}
		for (int c = 0; c < col; c++)
		{
			for (int r = 0; r < row; r++)
			{
				if (c == 0 || c == col - 1 || r == 0 || r == row - 1) { field[c][r] = border; }
				else { field[c][r] = clearField; }
			}
		}
	}

	void fillForTerrainMap()
	{
		Mountain mount;  Arable arab;  River rvr;  Hill hll;  Forest frst;

		int riverCounter = 0,
			mountainCounter = 0;

		for (int c = 1; c < col - 1; c++)
		{
			for (int r = 1; r < row - 1; r++)
			{
				switch (rand() % 4)
				{
				case(0):
				{
					if (riverCounter < 10)
					{
						field[r][c] = rvr.terrainCreator();
						riverCounter++;
						break;
					}
					else
					{
						field[r][c] = frst.terrainCreator();
						break;
					}
				}
				case(1):
				{
					if (mountainCounter < 10)
					{
						field[r][c] = mount.terrainCreator();
						mountainCounter++;
						break;
					}
					else
					{
						field[r][c] = hll.terrainCreator();
						break;
					}
				}
				case(2): { field[r][c] = arab.terrainCreator(); break; }

				case(3): { field[r][c] = hll.terrainCreator(); break; }

				default: { field[r][c] = '?'; break; }
				}
			}
		}
	}

	void showField()
	{
		for (int c = 0; c < col; c++)
		{
			for (int r = 0; r < row; r++)
			{
				cout << field[c][r] << ' ';
			}
			cout << endl;
		}
	}

	void setUnit(int xPos, int yPos, Unit * un)
	{
		field[xPos][yPos] = un->unitCreator();
		un->setxyPos(xPos, yPos);
	}

private:
	char border = 'X',
		clearField = ' ';
};

//.....................................Вывод конечной карты...........................................//

void showFieldAndUnitMap(MapForBattlefield unitMap, MapForBattlefield terrainMap)
{
	for (int c = 0; c < unitMap.col; c++)
	{
		for (int r = 0; r < unitMap.row; r++)
		{
			if (unitMap.field[c][r] == ' ')
			{
				cout << terrainMap.field[c][r] << ' ';
			}
			else
			{
				cout << unitMap.field[c][r] << ' ';
			}
		}
		cout << endl;
	}
}

//.......................................Карта ссылок.......................................//

class UnitPointerMap
{
public:
	int size = 10,
		counter;
	Unit*** MatrixPointer;
	Unit ** Array;

	UnitPointerMap(int row, int col)
	{
		Array = new Unit*[size];
		MatrixPointer = new Unit**[row];
		for (int a = 0; a < row; a++)
		{
			MatrixPointer[a] = new Unit*[col];
		}
	}
	void setPointer(int xPos, int yPos, Unit *un1)
	{
		MatrixPointer[xPos][yPos] = un1; 
	}
	void setArray(Unit * un) //недоделано
	{
		Array[counter] = un;
		cout << counter;
	}
	void showActiveUnitArray()
	{
		for (int a = 0; a < size; a++)
		{
			cout << a << " Юнит " << Array[a]->unitCreator() << "  Находится на X: " << Array[a]->xPos << " Y: " << Array[a]->yPos << " Здоровье: " << Array[0]->health;
		}
	}
};

//.......................................Перемещение........................................//
/*Добавть взаимодействие с ландшафтом*/

void moveUnit(MapForBattlefield unitMap, UnitPointerMap pointerMap, MapForBattlefield terrainMap)
{
	int xPos, yPos,
		moveInput;
	cout << "Введите координаты перемещаемого юнита: " "\n";
	cout << " X: "; cin >> xPos;  cout << " Y: "; cin >> yPos;
	cout << "Введите направление движения: ";
	cin >> moveInput;
	switch (moveInput)
	{
	case 8:
	{
		int newX = xPos - 1, newY = yPos;
		if (terrainMap.field[newX][newY] == '~' && pointerMap.MatrixPointer[xPos][yPos]->riverPass() == false)
		{
			cout << "\n Юнит не умеет плавать \n";
			break;
		}
		else
		{
			//Перемещение символа на основной карте 
			unitMap.field[xPos][yPos] = ' ';
			unitMap.field[newX][newY] = pointerMap.MatrixPointer[xPos][yPos]->unitCreator();
			//Перемещение ссылки на объект
			pointerMap.setPointer(newX, newY, pointerMap.MatrixPointer[xPos][yPos]);
			break;
		}
		break;
	}
	case 2:
	{
		int newX = xPos + 1, newY = yPos;
		if (terrainMap.field[newX][newY] == '~' && pointerMap.MatrixPointer[xPos][yPos]->riverPass() == false)
		{
			cout << "\n Юнит не умеет плавать \n";
			break;
		}
		else
		{
			unitMap.field[xPos][yPos] = ' ';
			unitMap.field[newX][newY] = pointerMap.MatrixPointer[xPos][yPos]->unitCreator();
			pointerMap.setPointer(newX, newY, pointerMap.MatrixPointer[xPos][yPos]);
			break;
		}
		break;
	}
	case 6:
	{
		int newX = xPos, newY = yPos + 1;
		if (terrainMap.field[newX][newY] == '~' && pointerMap.MatrixPointer[xPos][yPos]->riverPass() == false)
		{
			cout << "\n Юнит не умеет плавать \n";
			break;
		}
		else
		{
			unitMap.field[xPos][yPos] = ' ';
			unitMap.field[newX][newY] = pointerMap.MatrixPointer[xPos][yPos]->unitCreator();
			pointerMap.setPointer(newX, newY, pointerMap.MatrixPointer[xPos][yPos]);
			break;
		}
		break;
	}
	case 4:
	{
		int newX = xPos, newY = yPos - 1;
		if (terrainMap.field[newX][newY] == '~' && pointerMap.MatrixPointer[xPos][yPos]->riverPass() == false)
		{
			cout << "\n Юнит не умеет плавать \n";
			break;
		}
		else
		{
			unitMap.field[xPos][yPos] = ' ';
			unitMap.field[newX][newY] = pointerMap.MatrixPointer[xPos][yPos]->unitCreator();
			pointerMap.setPointer(newX, newY, pointerMap.MatrixPointer[xPos][yPos]);
			break;
		}
		break;
	}
	default:
		cout << "\n" "Некоректный ввод!" "\n";
		break;
	}
}

//......................................Битва..........................................//

void battle(UnitPointerMap pointerMap, MapForBattlefield unitMap)
{
	int xPosAtt, yPosAtt,
		xPosDef, yPosDef,
		hpDef, hpAtt;
	cout << "Введите координаты атакующего юнита: " "\n";
	cout << " X: "; cin >> xPosAtt;  cout << " Y: "; cin >> yPosAtt;

	cout << "Введите координаты защищающего юнита: " "\n";
	cout << " X: "; cin >> xPosDef;  cout << " Y: "; cin >> yPosDef;

	hpDef = (pointerMap.MatrixPointer[xPosDef][yPosDef]->health + pointerMap.MatrixPointer[xPosDef][yPosDef]->armor) - pointerMap.MatrixPointer[xPosAtt][yPosAtt]->attack;
	hpAtt = (pointerMap.MatrixPointer[xPosAtt][yPosAtt]->health + pointerMap.MatrixPointer[xPosAtt][yPosAtt]->armor) - pointerMap.MatrixPointer[xPosDef][yPosDef]->attack;

	if (hpDef < 0)
	{
		delete pointerMap.MatrixPointer[xPosDef][yPosDef];
		unitMap.field[xPosDef][yPosDef] = ' ';
	}
	else
	{
		pointerMap.MatrixPointer[xPosDef][yPosDef]->setHealth(hpDef);
	}
	if (hpAtt < 0)
	{
		delete pointerMap.MatrixPointer[xPosAtt][yPosAtt];
		unitMap.field[xPosAtt][yPosAtt] = ' ';
	}
	else
	{
		pointerMap.MatrixPointer[xPosAtt][yPosAtt]->setHealth(hpAtt);
	}
}

//............................Создание юнитов.......................................//

void spawnUnit(int xPos, int yPos, int unitNum, UnitPointerMap pointerMap, MapForBattlefield unitMap)
{
	switch (unitNum)
	{
	case 1:
	{
		Infantry* newLI = new LightInfantry();
		pointerMap.setPointer(xPos, yPos, newLI);
		unitMap.field[xPos][yPos] = newLI->unitCreator();
		pointerMap.MatrixPointer[xPos][yPos]->setxyPos(xPos, yPos);
		pointerMap.setArray(newLI);
		break;
	}
	case 2:
	{
		Infantry* newHI = new HeavyInfantry();
		pointerMap.setPointer(xPos, yPos, newHI);
		unitMap.field[xPos][yPos] = newHI->unitCreator();
		pointerMap.MatrixPointer[xPos][yPos]->setxyPos(xPos, yPos);
		pointerMap.setArray(newHI);
		break;
	}
	case 3:
	{
		Skirmishers* newArch = new Archer();
		pointerMap.setPointer(xPos, yPos, newArch);
		unitMap.field[xPos][yPos] = newArch->unitCreator();
		pointerMap.MatrixPointer[xPos][yPos]->setxyPos(xPos, yPos);
		pointerMap.setArray(newArch);
		break;
	}
	case 4:
	{
		Skirmishers* newCrossB = new Crossbowman();
		pointerMap.setPointer(xPos, yPos, newCrossB);
		unitMap.field[xPos][yPos] = newCrossB->unitCreator();
		pointerMap.MatrixPointer[xPos][yPos]->setxyPos(xPos, yPos);
		pointerMap.setArray(newCrossB);
		break;
	}
	case 5:
	{
		Cavalry* newNH = new NobleHorsman();
		pointerMap.setPointer(xPos, yPos, newNH);
		unitMap.field[xPos][yPos] = newNH->unitCreator();
		pointerMap.MatrixPointer[xPos][yPos]->setxyPos(xPos, yPos);
		pointerMap.setArray(newNH);
		break;
	}
	case 6:
	{
		Cavalry * newCata = new Cataphract();
		pointerMap.setPointer(xPos, yPos, newCata);
		unitMap.field[xPos][yPos] = newCata->unitCreator();
		pointerMap.MatrixPointer[xPos][yPos]->setxyPos(xPos, yPos);
		pointerMap.setArray(newCata);
		break;
	}
	default:
		cout << "Неверный ввод" << "/n";
		break;
	}
}

void spawnMenu(UnitPointerMap pointerMap, MapForBattlefield unitMap)
{
	int unChoose,
		xPos, yPos;
	menuForRecruit();
	cout << "Выбирите какого юнита заспавнить: \n";
	cin >> unChoose;
	cout << "Введите координаты: " "\n";
	cout << " X: "; cin >> xPos;  cout << " Y: "; cin >> yPos;
	menuForRecruit();
	spawnUnit(xPos, yPos, unChoose, pointerMap, unitMap);
}

//...............................Цикличное меню........................................//

void menuCycle(UnitPointerMap pointerMap, MapForBattlefield unitMap, MapForBattlefield terrainMap)
{
	bool flag = false;
	int menuChoose;
	while(!flag)
	{
		menuForActualGame();
		cin >> menuChoose;
		switch (menuChoose)
		{
		case 1: // Выбор юнита для взаимодействие 
		{
			int choose; 
			cout << "\n(1) - Aтака выбраным юнитом \n" << "(2) - Перемещение выбраного юнита \n"; 
			cin >> choose;
			switch (choose)
			{
			case 1:
			{
				battle(pointerMap, unitMap);
				break;
			}
			case 2:
			{
				moveUnit(unitMap, pointerMap, terrainMap);
				break;
			}
			default:
				cout << "\n" "Некоректный ввод!" "\n";
				break;
			}
			break;
		}
		case 2: // Состояние юнита
		{
			int xPos, yPos;
			cout << "Введите координаты юнита для проверки состояния: " "\n";
			cout << " X: "; cin >> xPos;  cout << " Y: "; cin >> yPos;
			cout << " Юнит: " << pointerMap.MatrixPointer[xPos][yPos]->unitCreator() << " Количество здоровья: " << pointerMap.MatrixPointer[xPos][yPos]->health << "\n";
			break;
		}
		case 3: // Показать актуальную карту
		{
			showFieldAndUnitMap(unitMap, terrainMap);
			break;
		}
		case 4: // Заспавнить юнит
		{
			spawnMenu(pointerMap, unitMap);
			break;
		}
		case 0:
		{
			flag = true;
			break;
		}
		default:
			cout << "\n" "Некоректный ввод!" "\n";
			break;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << " Ведите размерность карты: \n";
	int mapSize;
	cin >> mapSize;

	MapForBattlefield MapForUnit(mapSize, mapSize);
	MapForBattlefield MapForTerrain(mapSize, mapSize);
	UnitPointerMap pointerMap(mapSize, mapSize);
	MapForTerrain.fillForTerrainMap();

	menuCycle(pointerMap, MapForUnit, MapForTerrain);

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
