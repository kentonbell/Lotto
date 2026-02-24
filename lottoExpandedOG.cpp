////////////////////////////////////////////////////////
//	Name:		Lott Game
//	Author:		Alen Bell
//	Date:		December 2002
//	Course:		CS 171-2
//	Purpose:	Lotto game
////////////////////////////////////////////////////////

#include <iostream>
#include <string>
using namespace std;
#include "dice.h"

int doubles(int sides, int mega)
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
	unsigned long long int counter = 0;
	cout << endl;
	cout << endl;



	cout << "The number of rolls to win the lotto:              ";


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



int main()
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

		cout << "It took " << rolls << " rolls to win the lotto." << endl
			 << endl
			 << endl
			 << endl;
		cout << "Would you like play again?  ";
		cin >> y;
	} while (y == "y" || y == "yes" || y == "Y" || y == "Yes" || y == "yep" || y == "Yep" || y == "yeah" || y == "yup" || y == "yes please" || y == "Yes please" || y == "Yes Please");

	return 1;
}
