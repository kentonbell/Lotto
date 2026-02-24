////////////////////////////////////////////////////////
//  File:       dice.h
//  Author:     Alen Bell
//  Date:       December 2002
//  Purpose:    Dice class for Lotto Game
////////////////////////////////////////////////////////

#ifndef DICE_H
#define DICE_H

#include <cstdlib> // for rand()
#include <ctime>   // for time()

class Dice
{
private:
    int sides; // number of sides on the die

public:
    // Constructor: sets number of sides, seeds random generator if first die
    Dice(int s = 6)
    {
        sides = (s > 0) ? s : 6;
        static bool seeded = false;
        if (!seeded)
        {
            srand(static_cast<unsigned int>(time(0)));
            seeded = true;
        }
    }

    // Roll: returns a random number between 1 and number of sides
    inline int Roll()
    {
        return (rand() % sides) + 1;
    }

    uint64_t rng; 
    // inline int newRoll() //not working so ill try and figure this out later
    // {
    //     rng ^= rng << 13;
    //     rng ^= rng >> 7;
    //     rng ^= rng << 17;

    //     return (int)((rng * sides) >> 64) + 1;
    // }
};

#endif