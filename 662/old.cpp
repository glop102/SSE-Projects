#include <cmath>
#include <iostream>
#include <ctime>
using namespace std;
/**
* MyRPG 2.0
*
* Jacob Storey
* 11.04.14
*/

void fightWarlock(bool& end, int PMaxHealth, int& PHealth, int PNumOfDie, int PDieType, int PReact, int PArmor, int PHitchance, int& Potion, int& gold)
{
	/* Warlock Values*/
	int WMaxHealth = rand() % 100 + 101;
	int WHealth = WMaxHealth;
	int WNumOfDie = rand() % 6 + 1;
	int WDieType = 6;
	int WSpeed = rand() % 100 + 151;
	int WPrep = 0;
	int WArmor = rand() % 4 + 1;
	int WAction = 0;
	int WHitchance = 60;
	/* Player Values*/
	int PPrep = 0;
	int PAction = 0;
	bool flee = false;
	/*Shared Values*/
	int damage = 0;

	cout << "You've encountered a Warlock! Prepare for battle!" << endl;

	while (WHealth > 0 && PHealth > 0 && flee == false){
		PPrep++;
		if (PPrep == PReact){
			damage = 0;
			PPrep = 0;
			cout << "Your turn:" << endl;
			cout << "1. Attack" << endl;
			cout << "2. Flee" << endl;
			cout << "3. Evaluate" << endl;
			cout << "4. Use potion" << endl;
			cout << "You have " << PHealth << " health left." << endl;
			cout << "What would you like to do: ";
			cin >> PAction;
			if (PAction == 1)
			{
				if (rand() % 100 + 1 <= PHitchance)
				{
					for (int d = 1; d <= PNumOfDie; d++)
					{
						damage += rand() % PDieType + 1;
					}
					damage -= WArmor;
					if (damage < 0)
						damage = 0;
					cout << "Hit! You did " << damage << " to the opponent.\n" << endl;
					WHealth -= damage;
				}
				else
				{
					cout << "Miss!\n" << endl;
				}
			}
			else if (PAction == 2)
			{
				flee = true;
			}
			else if (PAction == 3)
			{
				cout << "The enemy looks like he has " << WHealth << " health left.\n" << endl;
			}
			else if (PAction == 4)
			{
				if (Potion > 0)
				{
					cout << "You drink a potion and restore to full health.\n\n"; Potion--; PHealth = PMaxHealth;
				}				
				else
					cout << "You don't have any potions.\n\n";
			}
		}

		WPrep++;
		if (WPrep == WSpeed)
		{
			damage = 0;
			WPrep = 0;
			cout << "Opponents turn:" << endl;
			WAction = rand() % 1 + 1;
			if (WAction == 1)
			{
				if (rand() % 100 + 1 <= WHitchance)
				{
					for (int d = 1; d <= WNumOfDie; d++)
					{
						damage += rand() % WDieType + 1;
					}
					damage -= PArmor;
					if (damage < 0)
						damage = 0;
					cout << "Hit! You took " << damage << " from the opponent.\n" << endl;
					PHealth -= damage;
				}
				else
				{
					cout << "Miss!\n" << endl;
				}
			}
		}
	}
	if (PHealth <= 0)
	{
		cout << "GAME OVER" << endl;
		end = true;
	}
	else if (flee)
	{
		cout << "You have run away." << endl;
	}
	else if (WHealth <= 0)
	{
		cout << "You win!" << endl;
		gold += (WNumOfDie * WDieType) + (WMaxHealth) / 10;
		cout << "You earned " << (WNumOfDie * WDieType) + (WMaxHealth) / 10	<< " gold pieces!\n";
		
	}
}
void fightSkeleton(bool& end, int PMaxHealth, int& PHealth, int PNumOfDie, int PDieType, int PReact, int PArmor, int PHitchance, int& Potion, int& gold)
{
	/* Skeleton Values*/
	int SMaxHealth = rand() % 150 + 151;
	int SHealth = SMaxHealth;
	int SNumOfDie = rand() % 2 + 1;
	int SDieType = 4;
	int SSpeed = rand() % 150 + 151;
	int SPrep = 0;
	int SArmor = rand() % 4 + 1;
	int SAction = 0;
	int SHitchance = 75;
	/* Player Values*/
	int PPrep = 0;
	int PAction = 0;
	bool flee = false;
	/*Shared Values*/
	int damage = 0;

	cout << "You've encountered a Skeleton! Prepare for battle!" << endl;

	while (SHealth > 0 && PHealth > 0 && flee == false){
		PPrep++;
		if (PPrep == PReact){
			damage = 0;
			PPrep = 0;
			cout << "Your turn:" << endl;
			cout << "1. Attack" << endl;
			cout << "2. Flee" << endl;
			cout << "3. Evaluate" << endl;
			cout << "4. Use potion" << endl;
			cout << "You have " << PHealth << " health left." << endl;
			cout << "What would you like to do: ";
			cin >> PAction;
			if (PAction == 1)
			{
				if (rand() % 100 + 1 <= PHitchance)
				{
					for (int d = 1; d <= PNumOfDie; d++)
					{
						damage += rand() % PDieType + 1;
					}
					damage -= SArmor;
					if (damage < 0)
						damage = 0;
					cout << "Hit! You did " << damage << " to the opponent.\n" << endl;
					SHealth -= damage;
				}
				else
				{
					cout << "Miss!\n" << endl;
				}
			}
			else if (PAction == 2)
			{
				flee = true;
			}
			else if (PAction == 3)
			{
				cout << "The enemy looks like he has " << SHealth << " health left.\n" << endl;
			}
			else if (PAction == 4)
			{
				if (Potion > 0)
				{
					cout << "You drink a potion and restore to full health.\n\n"; Potion--; PHealth = PMaxHealth;
				}
				else
					cout << "You don't have any potions.\n\n";
			}
		}

		SPrep++;
		if (SPrep == SSpeed)
		{
			damage = 0;
			SPrep = 0;
			cout << "Opponents turn:" << endl;
			SAction = rand() % 1 + 1;
			if (SAction == 1)
			{
				if (rand() % 100 + 1 <= SHitchance)
				{
					for (int d = 1; d <= SNumOfDie; d++)
					{
						damage += rand() % SDieType + 1;
					}
					damage -= PArmor;
					if (damage < 0)
						damage = 0;
					cout << "Hit! You took " << damage << " from the opponent.\n" << endl;
					PHealth -= damage;
				}
				else
				{
					cout << "Miss!\n" << endl;
				}
			}
		}
	}
	if (PHealth <= 0)
	{
		cout << "GAME OVER" << endl;
		end = true;
	}
	else if (flee)
	{
		cout << "You have run away." << endl;
	}
	else if (SHealth <= 0)
	{
		cout << "You win!" << endl;
		gold += (SNumOfDie * SDieType) + (SMaxHealth) / 10;
		cout << "You earned " << (SNumOfDie * SDieType) + (SMaxHealth) / 10 << " gold pieces!\n";

	}
}
void fightDemon(bool& end, int PMaxHealth, int& PHealth, int PNumOfDie, int PDieType, int PReact, int PArmor, int PHitchance, int& Potion, int& gold)
{
	/* Demon Values*/
	int DMaxHealth = rand() % 150 + 201;
	int DHealth = DMaxHealth;
	int DNumOfDie = rand() % 5 + 1;
	int DDieType = 8;
	int DSpeed = rand() % 150 + 51;
	int DPrep = 0;
	int DArmor = rand() % 5 + 1;
	int DAction = 0;
	int DHitchance = 80;
	/* Player Values*/
	int PPrep = 0;
	int PAction = 0;
	bool flee = false;
	/*Shared Values*/
	int damage = 0;

	cout << "You've encountered a Demon! Prepare for battle!" << endl;

	while (DHealth > 0 && PHealth > 0 && flee == false){
		PPrep++;
		if (PPrep == PReact){
			damage = 0;
			PPrep = 0;
			cout << "Your turn:" << endl;
			cout << "1. Attack" << endl;
			cout << "2. Flee" << endl;
			cout << "3. Evaluate" << endl;
			cout << "4. Use potion" << endl;
			cout << "You have " << PHealth << " health left." << endl;
			cout << "What would you like to do: ";
			cin >> PAction;
			if (PAction == 1)
			{
				if (rand() % 100 + 1 <= PHitchance)
				{
					for (int d = 1; d <= PNumOfDie; d++)
					{
						damage += rand() % PDieType + 1;
					}
					damage -= DArmor;
					if (damage < 0)
						damage = 0;
					cout << "Hit! You did " << damage << " to the opponent.\n" << endl;
					DHealth -= damage;
				}
				else
				{
					cout << "Miss!\n" << endl;
				}
			}
			else if (PAction == 2)
			{
				flee = true;
			}
			else if (PAction == 3)
			{
				cout << "The enemy looks like he has " << DHealth << " health left.\n" << endl;
			}
			else if (PAction == 4)
			{
				if (Potion > 0)
				{
					cout << "You drink a potion and restore to full health.\n\n"; Potion--; PHealth = PMaxHealth;
				}
				else
					cout << "You don't have any potions.\n\n";
			}
		}

		DPrep++;
		if (DPrep == DSpeed)
		{
			damage = 0;
			DPrep = 0;
			cout << "Opponents turn:" << endl;
			DAction = rand() % 1 + 1;
			if (DAction == 1)
			{
				if (rand() % 100 + 1 <= DHitchance)
				{
					for (int d = 1; d <= DNumOfDie; d++)
					{
						damage += rand() % DDieType + 1;
					}
					damage -= PArmor;
					if (damage < 0)
						damage = 0;
					cout << "Hit! You took " << damage << " from the opponent.\n" << endl;
					PHealth -= damage;
				}
				else
				{
					cout << "Miss!\n" << endl;
				}
			}
		}
	}
	if (PHealth <= 0)
	{
		cout << "GAME OVER" << endl;
		end = true;
	}
	else if (flee)
	{
		cout << "You have run away." << endl;
	}
	else if (DHealth <= 0)
	{
		cout << "You win!" << endl;
		gold += (DNumOfDie * DDieType) + (DMaxHealth) / 10;
		cout << "You earned " << (DNumOfDie * DDieType) + (DMaxHealth) / 10 << " gold pieces!\n";

	}
}
void fightEnemy(bool& end, int PMaxHealth, int& PHealth, int PNumOfDie, int PDieType, int PReact, int PArmor, int PHitchance, int& Potion, int& gold)
{
	int rEnemy = rand() % 100 + 1;
	if (rEnemy >= 1 && rEnemy <= 20)
	{
		fightWarlock(end, PMaxHealth, PHealth, PNumOfDie, PDieType, PReact, PArmor, PHitchance, Potion, gold);
	}
	else if (rEnemy >= 21 && rEnemy <= 95)
	{
		fightSkeleton(end, PMaxHealth, PHealth, PNumOfDie, PDieType, PReact, PArmor, PHitchance, Potion, gold);
	}
	else if (rEnemy >= 96 && rEnemy <= 100)
	{
		fightDemon(end, PMaxHealth, PHealth, PNumOfDie, PDieType, PReact, PArmor, PHitchance, Potion, gold);
	}
}
void weapon(int weaponType, int& PNumOfDie, int& PDieType)
{
	if (weaponType == 1)
	{
		PNumOfDie = 2; PDieType = 4; cout << "Your weapon is now a 2d4 (This means the damage will be the sum" << endl 
		<< "of rolling two four-sided die).\n\n";
	}
	else if (weaponType == 2)
	{
		PNumOfDie = 1; PDieType = 12; cout << "Your weapon is now a 1d12.\n\n";
	}
	else if (weaponType == 3)
	{
		PNumOfDie = 2; PDieType = 6; cout << "Your weapon is now a 2d6.\n\n";
	}
	else if (weaponType == 4)
	{
		PNumOfDie = 3; PDieType = 4; cout << "Your weapon is now a 3d4.\n\n";
	}
	else if (weaponType == 5)
	{
		PNumOfDie = 3; PDieType = 6; cout << "Your weapon is now a 3d6.\n\n";
	}
	else if (weaponType == 6)
	{
		PNumOfDie = 3; PDieType = 8; cout << "Your weapon is now a 3d8.\n\n";
	}
	else if (weaponType == 7)
	{
		PNumOfDie = 4; PDieType = 6; cout << "Your weapon is now a 4d6.\n\n";
	}
	else if (weaponType == 8)
	{
		PNumOfDie = 5; PDieType = 6; cout << "Your weapon is now a 5d6.\n\n";
	}
	else if (weaponType == 9)
	{
		PNumOfDie = 3; PDieType = 12; cout << "Your weapon is now a 3d12.\n\n";
	}
	else if (weaponType == 10)
	{
		PNumOfDie = 2; PDieType = 20; cout << "Your weapon is now a 2d20.\n\n";
	}
}
void main(void)
{
	srand((unsigned)time(NULL));
	int PMaxHealth = 100, PHealth = PMaxHealth, gold = 500, act, fightCount = 0, PNumOfDie = 1, PDieType = 1, PReact = 75, PPrep = 0, PArmor = 0, PHitchance = 75, Potion = 0, weaponType = 0;
	bool end = false;
	cout << "Welcome hero, to The Dungeon!\nEach day you will have the option to rest and recover\n"
		<< "your health fight and earn gold,\nor spend your gold in the shop to upgrade your equipment.\n"
		<< "I'll give you "<< gold <<" just to get started.\n"
		<< "You should upgrade your weapon and save a bit in case you need to rest.\n\n";

	while (!end)
	{
		cout << "What will you do today?\n1. Rest\n2. Fight\n3. Shop\n5. Exit\n";
		cin >> act;
		if (act == 1)
		{
			if (gold > 25)
			{
				PHealth = PMaxHealth;
				gold -= 25;
				cout << "You have regained your health at the cost of 25 gold.\n";
				fightCount = 0;
			}
			else
			{
				cout << "You can't afford to rest today.\n";
			}

		}
		else if (act == 2)
		{
			fightEnemy(end, PMaxHealth, PHealth, PNumOfDie, PDieType, PReact, PArmor, PHitchance, Potion, gold);
			cout << "Your total gold is " << gold << endl;
			fightCount++;
		}
		else if (act == 3)
		{
			int item, price;
			cout << "Welcome to the shop! You have " << gold << " gold. What can I help you with? \n1. Armor " << 20 + (PArmor * 5) << " gold"
				<< "\n2. Weapons " << 20 + (PDieType * PNumOfDie * 5) << " gold \n3. Health Potion 50 gold\nANY OTHER TO EXIT\n";
			cin >> item;
			if (item == 1)
			{
				price = 20 + (PArmor * 5);
				if (price < gold)
				{
					PArmor += 2;
					gold -= price;
					cout << "You have upgraded your armor to " << PArmor << ".\n\n";
				}
				else
					cout << "You can't afford that.\n\n";
			}
			else if (item == 2)
			{
				price = 20 + (PDieType * PNumOfDie * 5);
				if (price < gold && weaponType < 10)
				{
					weaponType++;
					weapon(weaponType, PNumOfDie, PDieType);
					gold -= price;
				}
				else if (gold < price)
					cout << "You can't afford that.\n\n";
				else if (weaponType >= 10)
					cout << "Your weapon is maxed out!\n\n";
			}
			else if (item == 3)
			{
				price = 50;
				if (price < gold)
				{
					Potion++;
					gold -= price;
					cout << "You have bought a potion.\n\n";
				}
				else
					cout << "You can't afford that.\n\n";
			}
			else
			{

			}
		}
		else if (act == 5)
		{
			end = true;
		}

	}
	cout << "You ended the game with " << gold << " gold.\n";
}