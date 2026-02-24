////////////////////////////////////////////////////////
//	Name:		Lott Game
//	Author:		Alen Bell
//	Date:		December 2002
//	Course:		CS 171-2
//	Purpose:	Lotto game
////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include "dice.h"

#include <iomanip> //for numbers w/commas
#include <locale>
#include <istream>
#include <sstream>
// #include <iomanip>

using namespace std;

#include <random>
#include <thread>

struct Lottery
{
	string name;
	unsigned int whiteCount;
	unsigned int whiteSides;
	unsigned int redSides;
	unsigned int cashpotStart;
	unsigned int cost;
	unsigned int odds;
};

template <class T>
string formatWithComma(T v)
{

	auto s = std::to_string(v);

	int n = s.length() - 3;
	int end = (v >= 0) ? 0 : 1; // Support for negative numbers
	while (n > end)
	{
		s.insert(n, ",");
		n -= 3;
	}
	return s;
}

static thread_local std::mt19937_64 rng(std::random_device{}());

inline int rollDiceAccurately(int lo, int hi)
{
	uniform_int_distribution<int> dist(lo, hi);
	return dist(rng);
}

unsigned long long combinations(unsigned int n, unsigned int k)
{
	if (k > n)
		return 0;
	if (k > n - k)
		k = n - k; // symmetry

	unsigned long long result = 1;
	for (unsigned int i = 1; i <= k; ++i)
	{
		result = result * (n - k + i) / i;
	}
	return result;
}

unsigned int calculateOdds(const Lottery &L)
{
	unsigned long long whiteCombos =
		combinations(L.whiteSides, L.whiteCount);

	unsigned long long totalOdds = whiteCombos;

	if (L.redSides > 0)
		totalOdds *= L.redSides;

	return static_cast<unsigned int>(totalOdds);
}

bool isNumber(const std::string &str)
{
	std::stringstream ss(str);
	double value;
	// Try to extract a double and check if the stream reaches the end (eof)
	// after potential whitespace (ws)
	if (ss >> value)
	{
		return true;
	}
	return false;
}

int chooseProcessSpeed()
{

	cout << "\nChoose CPU workload:\n1. 2002's CS 171  \n2. Part Time \n3. Full Time \n4. Over Time\nEnter number: ";

	int num = 0;

	cin >> num;

	if (num != 1 && num != 2 && num != 3 && num != 4 && num != 5)
	{
		throw runtime_error("Invalid selection");
	}

	cout << endl
		 << endl;
	return num;
}

Lottery chooseLottery()
{

	ifstream file("lottoInfo.txt");
	if (!file)
	{
		throw runtime_error("Could not open lottoInfo.txt");
	}

	vector<Lottery> lotteries;
	string line;

	while (getline(file, line))
	{
		stringstream ss(line);
		Lottery L;

		getline(ss, L.name, ',');
		ss.ignore(1);
		ss >> L.whiteCount;
		ss.ignore(2);
		ss >> L.whiteSides;
		ss.ignore(2);
		ss >> L.redSides;
		ss.ignore(2);
		ss >> L.cashpotStart;
		ss.ignore(2);
		ss >> L.cost;
		ss.ignore(2);
		ss >> L.odds;

		lotteries.push_back(L);
	}

	file.close();

	for (int i = 0; i < lotteries.size(); i++)
	{

		lotteries[i].odds = calculateOdds(lotteries[i]);
	}

	cout << left
		 << setw(7) << "Index"
		 << setw(15) << "Lotto"
		 << setw(12) << "White Pots"
		 << setw(10) << "White's"
		 << setw(8) << "Mega's"
		 << setw(14) << "Start"
		 << setw(6) << "Cost"
		 << setw(18) << "Odds"
		 << endl;

	cout << string(90, '-') << endl;

	string tempIndex, tempStart, tempCost, tempOdds;

	for (size_t i = 0; i < lotteries.size(); i++)
	{
		const Lottery &L = lotteries[i];

		tempIndex = to_string((i + 1));
		tempIndex += ".";
		tempStart = "$";
		tempStart += formatWithComma(L.cashpotStart);
		tempCost = "$";
		tempCost += to_string(L.cost);

		tempOdds = "1 in ";
		tempOdds += formatWithComma(L.odds);

		cout << left
			 << setw(7) << tempIndex
			 << setw(15) << L.name
			 << setw(12) << L.whiteCount
			 << setw(10) << L.whiteSides
			 << setw(8) << L.redSides
			 << setw(14) << tempStart
			 << setw(6) << tempCost
			 << setw(18) << tempOdds
			 << endl;
	}

	cout << "\nWould you like to choose one of the available options or make your own? (0 for custom)\nEnter Number: ";
	unsigned int choice;
	cin >> choice;

	if (choice == 0)
	{
		Lottery custom;
		custom.name = "CUSTOM";

		cout << "Enter number of white pots: ";
		cin >> custom.whiteCount;

		cout << "Enter white ball count: ";
		cin >> custom.whiteSides;

		cout << "Enter mega ball count: ";
		cin >> custom.redSides;

		cout << "Enter starting cashpot: ";
		cin >> custom.cashpotStart;

		cout << "Enter cost to play: ";
		cin >> custom.cost;

		custom.odds = calculateOdds(custom);
		cout << "Your Odds Are: 1 in " << formatWithComma(custom.odds) << endl;

		return custom;
	}

	if (choice < 1 || choice > lotteries.size())
	{
		throw runtime_error("Invalid selection");
	}

	return lotteries[choice - 1];
}

inline bool checkDuplicates(int rolls[], int index)
{

	for (int i = 0; i < index; i++)
	{
		if (rolls[index] == rolls[i])
		{
			return true;
		}
	}

	return false;
}

inline int setMagicNumber(int winningSet[], int set[], int totalPots)
{
	int total = 0;
	for (int i = 0; i < totalPots; i++)
	{
		total += abs(winningSet[i] - set[i]);
	}

	return total;
}

bool checkWin(int winningRoll[], int currentRoll[], int totalPots)
{

	for (int i = 0; i < totalPots; i++)
	{
		if (currentRoll[i] != winningRoll[i])
		{
			return true;
		}
	}

	return false;
}

inline bool isNotWin(const int *win, const int *cur, int n)
{
	for (int i = 0; i < n; ++i)
		if (cur[i] != win[i])
			return true;
	return false;
}

inline void insertionSort(int *a, int n)
{
	for (int i = 1; i < n; ++i)
	{
		int key = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > key)
		{
			a[j + 1] = a[j];
			--j;
		}
		a[j + 1] = key;
	}
}

inline void tiny_delay(int delay)
{
	volatile long long x = 0;
	for (int i = 0; i < delay; ++i)
		x += i;
}

unsigned long long doubles(int sides, int mega)
{

	int showTestCode = 0;

	if (showTestCode == 1)
		cout << "0\n";

	Dice one(sides);
	Dice two(sides);
	Dice three(sides);
	Dice four(sides);
	Dice five(sides);
	Dice six(mega);
	Dice A(sides);
	Dice B(sides);
	Dice C(sides);
	Dice D(sides);
	Dice E(sides);
	Dice F(mega);

	int rollone, rolltwo, rollthree, rollfour, rollfive, rollsix;
	int rollBone, rollBtwo, rollBthree, rollBfour, rollBfive, rollBsix;
	unsigned long long counter = 0;
	cout << endl;
	cout << endl;

	cout << "The number of rolls to win the lotto:                                  ";

	do
	{

		counter++;
		/////////////////// Dice One

		rollone = one.Roll();

		do
		{
			rolltwo = two.Roll();
		} while (rolltwo == rollone);
		do
		{
			rollthree = three.Roll();
		} while (rollthree == rollone || rollthree == rolltwo);
		do
		{
			rollfour = four.Roll();
		} while (rollfour == rollone || rollfour == rolltwo || rollfour == rollthree);
		do
		{
			rollfive = five.Roll();
		} while (rollfive == rollone || rollfive == rolltwo || rollfive == rollthree || rollfive == rollfour);
		//		do
		//		{
		rollsix = six.Roll();
		//		}	while ( rollsix == rollone || rollsix == rolltwo || rollsix == rollthree || rollsix == rollfour || rollsix == rollfive );
		//		cout << rollone << " " << rolltwo << " " << rollthree << " " << rollfour << " " << rollfive << " " << rollsix << endl;
		/////////////////// Dice Two
		rollBone = one.Roll();
		do
		{
			rollBtwo = two.Roll();

		} while (rollBtwo == rollBone);
		do
		{
			rollBthree = three.Roll();
		} while (rollBthree == rollBone || rollBthree == rollBtwo);
		do
		{
			rollBfour = four.Roll();
		} while (rollBfour == rollBone || rollBfour == rollBtwo || rollBfour == rollBthree);
		do
		{
			rollBfive = five.Roll();
		} while (rollBfive == rollBone || rollBfive == rollBtwo || rollBfive == rollBthree || rollBfive == rollBfour);
		//		do
		//		{
		rollBsix = six.Roll();
		//		}	while ( rollBsix == rollBone || rollBsix == rollBtwo || rollBsix == rollBthree || rollBsix == rollBfour || rollBsix == rollBfive );
		//	cout << rollBone << " " << rollBtwo << " " << rollBthree << " " << rollBfour << " " << rollBfive << " " << rollBsix << endl;

		if (counter < 10 && counter > 1)
			cout << "\b";
		if (counter < 100 && counter >= 10)
			cout << "\b\b";
		if (counter < 1000 && counter >= 100)
			cout << "\b\b\b";
		if (counter < 10000 && counter >= 1000)
			cout << "\b\b\b\b";
		if (counter < 100000 && counter >= 10000)
			cout << "\b\b\b\b\b";
		if (counter < 1000000 && counter >= 100000)
			cout << "\b\b\b\b\b\b";
		if (counter < 10000000 && counter >= 1000000)
			cout << "\b\b\b\b\b\b\b";
		if (counter < 100000000 && counter >= 10000000)
			cout << "\b\b\b\b\b\b\b\b";
		if (counter < 1000000000 && counter >= 100000000)
			cout << "\b\b\b\b\b\b\b\b\b";

		if (counter < 10000000000 && counter >= 1000000000)
			cout << "\b\b\b\b\b\b\b\b\b\b";
		if (counter < 100000000000 && counter >= 10000000000)
			cout << "\b\b\b\b\b\b\b\b\b\b\b";
		if (counter < 1000000000000 && counter >= 100000000000)
			cout << "\b\b\b\b\b\b\b\b\b\b\b\b";
		if (counter < 10000000000000 && counter >= 1000000000000)
			cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b";

		if (counter < 100000000000000 && counter >= 10000000000000)
			cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		if (counter < 1000000000000000 && counter >= 100000000000000)
			cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		if (counter < 10000000000000000 && counter >= 1000000000000000)
			cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		if (counter < 100000000000000000 && counter >= 10000000000000000)
			cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		if (counter < 1000000000000000000 && counter >= 100000000000000000)
			cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";

		cout << counter;

		int temp5 = rollfive;
		int temp4 = rollfour;
		int temp3 = rollthree;
		int temp2 = rolltwo;
		int temp1 = rollone;

		if (rollone > rolltwo)
		{
			rollone = rolltwo;
			rolltwo = temp1;
			temp1 = rollone;
			temp2 = rolltwo;
		}

		if (rollone > rollthree)
		{
			rollone = rollthree;
			rolltwo = temp1;
			rollthree = temp2;
			temp3 = rollthree;
			temp2 = rolltwo;
			temp1 = rollone;
		}
		if (rolltwo > rollthree)
		{
			rolltwo = rollthree;
			rollthree = temp2;
			temp3 = rollthree;
			temp2 = rolltwo;
		}

		if (rollone > rollfour)
		{
			rollone = rollfour;
			rolltwo = temp1;
			rollthree = temp2;
			rollfour = temp3;
			temp4 = rollfour;
			temp3 = rollthree;
			temp2 = rolltwo;
			temp1 = rollone;
		}
		if (rolltwo > rollfour)
		{
			rolltwo = rollfour;
			rollthree = temp2;
			rollfour = temp3;
			temp4 = rollfour;
			temp3 = rollthree;
			temp2 = rolltwo;
		}
		if (rollthree > rollfour)
		{
			rollthree = rollfour;
			rollfour = temp3;
			temp4 = rollfour;
			temp3 = rollthree;
		}
		if (rollone > rollfive)
		{
			rollone = rollfive;
			rolltwo = temp1;
			rollthree = temp2;
			rollfour = temp3;
			rollfive = temp4;
			temp5 = rollfive;
			temp4 = rollfour;
			temp3 = rollthree;
			temp2 = rolltwo;
			temp1 = rollone;
		}
		if (rolltwo > rollfive)
		{
			rolltwo = rollfive;
			rollthree = temp2;
			rollfour = temp3;
			rollfive = temp4;
			temp5 = rollfive;
			temp4 = rollfour;
			temp3 = rollthree;
			temp2 = rolltwo;
		}
		if (rollthree > rollfive)
		{
			rollthree = rollfive;
			rollfour = temp3;
			rollfive = temp4;
			temp5 = rollfive;
			temp4 = rollfour;
			temp3 = rollthree;
		}
		if (rollfour > rollfive)
		{
			rollfour = rollfive;
			rollfive = temp4;
			temp5 = rollfive;
			temp4 = rollfour;
		}

		/////////////////// Dice TWO
		int tempB5 = rollBfive;
		int tempB4 = rollBfour;
		int tempB3 = rollBthree;
		int tempB2 = rollBtwo;
		int tempB1 = rollBone;

		if (rollBone > rollBtwo)
		{
			rollBone = rollBtwo;
			rollBtwo = tempB1;
			tempB1 = rollBone;
			tempB2 = rollBtwo;
		}

		if (rollBone > rollBthree)
		{
			rollBone = rollBthree;
			rollBtwo = tempB1;
			rollBthree = tempB2;
			tempB3 = rollBthree;
			tempB2 = rollBtwo;
			tempB1 = rollBone;
		}
		if (rollBtwo > rollBthree)
		{
			rollBtwo = rollBthree;
			rollBthree = tempB2;
			tempB3 = rollBthree;
			tempB2 = rollBtwo;
		}

		if (rollBone > rollBfour)
		{
			rollBone = rollBfour;
			rollBtwo = tempB1;
			rollBthree = tempB2;
			rollBfour = tempB3;
			tempB4 = rollBfour;
			tempB3 = rollBthree;
			tempB2 = rollBtwo;
			tempB1 = rollBone;
		}
		if (rollBtwo > rollBfour)
		{
			rollBtwo = rollBfour;
			rollBthree = tempB2;
			rollBfour = tempB3;
			tempB4 = rollBfour;
			tempB3 = rollBthree;
			tempB2 = rollBtwo;
		}
		if (rollBthree > rollBfour)
		{
			rollBthree = rollBfour;
			rollBfour = tempB3;
			tempB4 = rollBfour;
			tempB3 = rollBthree;
		}
		if (rollBone > rollBfive)
		{
			rollBone = rollBfive;
			rollBtwo = tempB1;
			rollBthree = tempB2;
			rollBfour = tempB3;
			rollBfive = tempB4;
			tempB5 = rollBfive;
			tempB4 = rollBfour;
			tempB3 = rollBthree;
			tempB2 = rollBtwo;
			tempB1 = rollBone;
		}
		if (rollBtwo > rollBfive)
		{
			rollBtwo = rollBfive;
			rollBthree = tempB2;
			rollBfour = tempB3;
			rollBfive = tempB4;
			tempB5 = rollBfive;
			tempB4 = rollBfour;
			tempB3 = rollBthree;
			tempB2 = rollBtwo;
		}
		if (rollBthree > rollBfive)
		{
			rollBthree = rollBfive;
			rollBfour = tempB3;
			rollBfive = tempB4;
			tempB5 = rollBfive;
			tempB4 = rollBfour;
			tempB3 = rollBthree;
		}
		if (rollBfour > rollBfive)
		{
			rollBfour = rollBfive;
			rollBfive = tempB4;
			tempB5 = rollBfive;
			tempB4 = rollBfour;
		}

	} while (rollone != rollBone || rolltwo != rollBtwo || rollthree != rollBthree || rollfour != rollBfour || rollfive != rollBfive || rollsix != rollBsix);

	cout << endl;
	cout << endl;
	cout << endl;
	cout << rollone << " " << rolltwo << " " << rollthree << " " << rollfour << " " << rollfive << " " << rollsix << endl;
	cout << rollBone << " " << rollBtwo << " " << rollBthree << " " << rollBfour << " " << rollBfive << " " << rollBsix << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	return counter;
}

unsigned long long playLottery(const Lottery &L, int processSpeed)
{

	cout << "\n\n\nLet's play " << L.name << "!\n\n";

	unsigned long long counter = 0;

	vector<Dice> pots;

	int wCt = L.whiteCount;

	for (int i = 0; i < L.whiteCount; i++)
	{
		pots.push_back(Dice(L.whiteSides));
	}

	int totalPots = wCt;
	int lastPotIndex = wCt - 1;
	bool withMega = false;

	if (L.redSides != 0) // if with mega
	{
		withMega = true;
		totalPots = wCt + 1;
		lastPotIndex = wCt;
		pots.push_back(Dice(L.redSides));
	}

	int winningRolls[totalPots];

	for (int i = 0; i < L.whiteCount; i++)
	{
		do
		{
			winningRolls[i] = pots[i].Roll();

		} while (checkDuplicates(winningRolls, i));
	}

	if (withMega)
	{
		winningRolls[lastPotIndex] = pots[lastPotIndex].Roll();

		insertionSort(winningRolls, lastPotIndex);
	}
	else
	{
		insertionSort(winningRolls, totalPots);
	}

	int currentRoll[totalPots];
	int closestRoll[totalPots];

	// do
	// {
	// 	currentRoll[i] = pots[i].Roll();

	// } while (checkDuplicates(currentRoll, i));

	// the big repeating part // // / / / /// /// //// / //// /// / ///// // // / / / / / // / / // / / // / // /

	int frameRate = 10;
	switch (processSpeed)
	{
	case 2:
		frameRate = 9;
		break;
	case 3:
		frameRate = 13;
		break;
	case 4:
		frameRate = 19;
		break;
	case 5:
		frameRate = 20;

	default:
		break;
	}

	int slowDownRate = 0;
	switch (processSpeed)
	{
	case 2:
		slowDownRate = 700;
		break;
	case 3:
		slowDownRate = 70;
		break;
	case 4:
		slowDownRate = 0;
		break;
	case 5:
		slowDownRate = 0;

	default:
		break;
	}

	bool won = false;
	bool foundMatch = false;

	int winningMagicNumber = setMagicNumber(winningRolls, winningRolls, totalPots);
	int closestMagicNumber = 1000000000;
	string closestSetString = "";
	string allLastMinuteClosestsString = "none";
	long closeStringCutOff = 1000000; // onemillion
	if (processSpeed == 2) closeStringCutOff = 10000; //tenK
	if (L.name == "MATCH4") closeStringCutOff = 1000; //matchfour

	int filled;
	do
	{
		counter++;

		// tiny_delay(slowDownRate);

		if (((counter & ((1ULL << ((processSpeed * 7) - 10)) - 1)) == 0) && processSpeed != 4 && processSpeed != 5) 
		{
			this_thread::sleep_for(std::chrono::microseconds(1800));
		}

		for (int i = 0; i < L.whiteCount; i++)
		{
			do
			{
				currentRoll[i] = pots[i].Roll();

			} while (checkDuplicates(currentRoll, i));
		}

		if (withMega)
		{
			currentRoll[lastPotIndex] = pots[lastPotIndex].Roll(); // roll the last mega, not checking for duplicate.
			insertionSort(currentRoll, lastPotIndex);
		}
		else
		{
			insertionSort(currentRoll, totalPots);
		}

		if (counter == 1)
		{
			closestMagicNumber = setMagicNumber(winningRolls, currentRoll, totalPots);
		}

		/////

		// cout << "Winning Roll: ";

		// for (int i = 0; i < totalPots; i++)
		// {
		// 	cout << winningRolls[i] << " ";
		// }

		// cout << "\nCurrent Roll: ";

		// // for (int i = 0; i < totalPots; i++)
		// // {
		// // 	cout << "\n" << i << ": ";
		// // 	cin >> currentRoll[i];
		// // }

		// for (int i = 0; i < totalPots; i++)
		// {
		// 	cout << currentRoll[i] << " ";
		// }
		// cout << endl;

		// int n;
		// cin >> n;
		//////

		int candidate = setMagicNumber(winningRolls, currentRoll, totalPots);

		if (abs(winningMagicNumber - closestMagicNumber) > abs(winningMagicNumber - candidate))
		{ // if new close one

			if (counter > closeStringCutOff) // one million
			{
				if (allLastMinuteClosestsString == "none")
					allLastMinuteClosestsString = "";
				allLastMinuteClosestsString += " [";
				allLastMinuteClosestsString += closestSetString;
				allLastMinuteClosestsString += " ]";
			}
			closestSetString = "";
			for (int i = 0; i < totalPots; i++)
			{
				closestMagicNumber = candidate;
				closestRoll[i] = currentRoll[i];
				closestSetString += " ";
				closestSetString += to_string(currentRoll[i]);
			}
		}

		if ((counter & (1ULL << frameRate) - 1) == 0)
		{ // every ~1 million
			cout << "\r" << string(120, ' ') << '\r' << "The number of rolls thus far: " << formatWithComma(counter) << " with the closet roll being" << closestSetString << ". " << flush;
		}

		foundMatch = true;
		for (int i = 0; i < L.whiteCount; ++i)
		{
			if (winningRolls[i] != currentRoll[i])
			{
				foundMatch = false;
				break;
			}
		}
		if (withMega && currentRoll[lastPotIndex] != winningRolls[lastPotIndex])
			foundMatch = false;

		won = foundMatch;

	} while (!won);

	// end of the big repeating part

	// old repeating
	//  unsigned int digits = 1;
	//  unsigned long long temp = counter;
	//  while (temp >= 10)
	//  {
	//  	temp /= 10;
	//  	++digits;
	//  }
	//  for (unsigned int i = 0; i < digits; ++i)
	//  {
	//  	// cout << '\b';

	// }

	// cout << counter;
	// end old

	cout << "\r" << string(200, ' ') << '\r' << "It took " << formatWithComma(counter) << " rolls to win the lotto! The winning roll was" << closestSetString << ". ";

	cout << endl
		 << "\n\n\nAll close sets after attempt " << formatWithComma(closeStringCutOff) << " are listed: " << allLastMinuteClosestsString << endl;

	// for (int i = 0; i < totalPots; i++)
	// {
	// 	cout << currentRoll[i] << " ";
	// }
	// cout << "\n\nWinning Roll: ";

	// for (int i = 0; i < totalPots; i++)
	// {
	// 	cout << winningRolls[i] << " ";
	// }
	// cout << endl;

	// cout << "\nIt took " << formatWithComma(counter) << " rolls to win the lotto!" << endl;

	cout << "\nThe computer spent $" << formatWithComma(counter * L.cost) << " on tickets and won the initial $" << formatWithComma(L.cashpotStart) << ", that is, before taxes and fees...\n";
	// cout << "You won  $" << formatWithComma(counter * L.cost + L.cashpotStart) << " dollars before taxes and fees...";

	return counter;
}

int main()
{

	cout << "\n\nWelcome to lotto!\n\n";

	try
	{

		int processSpeed = chooseProcessSpeed();

		if (processSpeed == 1)
		{
			string y = "n";
			do
			{
				int sides, mega_number;
				cout << "How many different numbers are in the pot? ";
				cin >> sides;

				if (sides < 5)
				{
					cout << "You cannot do less than 5. Setting it to five.\n";
					sides = 5;
				}

				cout << endl;
				cout << "How many mega numbers are there? ";
				cin >> mega_number;

				int rolls = doubles(sides, mega_number);

				cout << "It took " << formatWithComma(rolls) << " rolls to win the lotto." << endl
					 << endl
					 << endl
					 << endl;
				cout << "Would you like play again?  ";
				cin >> y;
			} while (y == "y" || y == "yes" || y == "Y" || y == "Yes" || y == "yep" || y == "Yep" || y == "yeah" || y == "yup" || y == "yes please" || y == "Yes please" || y == "Yes Please");

			return 1;
		}

		Lottery chosen = chooseLottery();

		// cout << "\nChosen Lottery:\n";
		// cout << "Name: " << chosen.name << endl;
		// cout << "White Balls: " << chosen.whiteCount << endl;
		// cout << "White Sides: " << chosen.whiteSides << endl;
		// cout << "Red Sides: " << chosen.redSides << endl;
		// cout << "Cashpot Start: " << chosen.cashpotStart << endl;
		// cout << "Cost: $" << chosen.cost << endl;
		// cout << "Odds: 1 in " << chosen.odds << endl
		// 	 << endl;

		string y = "firstOne";

		vector<unsigned long long> totalRolls;

		int unsigned long long total = 0;

		int unsigned long long avg;

		int lottoCount = 0;

		int repeatCount = 1;
		int secondRptCt = 1;

		do
		{
			secondRptCt = repeatCount; // so the message shows later...

			for (int i = 0; i < repeatCount; i++)
			{

				auto start = chrono::high_resolution_clock::now();

				totalRolls.push_back(playLottery(chosen, processSpeed));

				auto end = chrono::high_resolution_clock::now();

				chrono::duration<double> elapsed = end - start;

				cout << "\nIt took " << elapsed.count() << " seconds. \n";

				total += totalRolls.back();
				lottoCount++;

				avg = total / totalRolls.size();

				if (y != "firstOne")
				{
					cout << "\n\nThe average roll count across " << lottoCount << " lotteries is: " << formatWithComma(avg) << " rolls. ";
				}
			}

			if (repeatCount == 1)
			{
				cout << endl
					 << "\n\nNote: In the next prompt, you can instead enter a number for many plays averaged. \n\nWould you like play again?  ";
			}
			else
			{
				cout << endl
					 << "\n\n\nNote: The next average will compound onto the " << lottoCount << ". \n\nWould you like play again?  ";
			}
			cin >> y;

			if (isNumber(y))
			{
				repeatCount = stoi(y);
				total = 0;
				totalRolls.pop_back();
				lottoCount--;
				y = "y";
			}

			if (y == "y" || y == "yes" || y == "Y" || y == "Yes" || y == "yep" || y == "Yep" || y == "yeah" || y == "yup" || y == "yes please" || y == "Yes please" || y == "Yes Please" || y == "sure")
			{

				if (secondRptCt == 1)
				{
					cout << "\nWould you like to change the lottery?  ";
				}
				else
				{
					cout << "\nWould you like to change the lottery and reset the average?  ";
				}
				cin >> y;
				if (y == "y" || y == "yes" || y == "Y" || y == "Yes" || y == "yep" || y == "Yep" || y == "yeah" || y == "yup" || y == "yes please" || y == "Yes please" || y == "Yes Please" || y == "sure")
				{
					cout << endl;
					total = 0;
					// repeatCount = 1;
					lottoCount = 0;
					totalRolls.clear();
					chosen = chooseLottery();
				}
			}
			else
			{
				cout << endl
					 << "\n\n\nGoodbye!\n\n";
				break;
			}

		} while (true);
	}
	catch (const exception &e)
	{
		cerr << e.what() << endl;
	}

	return 0;
}