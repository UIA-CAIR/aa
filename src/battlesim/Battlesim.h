//
// Created by per on 20.02.18.
//

#ifndef AA_BATTLESIM_H
#define AA_BATTLESIM_H


#include <cstddef>
#include "../Board.h"
#include "../Dice.h"


// Air supremacy dice
#define DICE_FIGHTER_DEFEAT_MIN 0
#define DICE_FIGHTER_DEFEAT_MAX 2

// Attacker artillery
#define DICE_ATK_ARTILLERY_MIN 0
#define DICE_ATK_ARTILLERY_MAX 3
#define DICE_ATK_ARTILLERY_AIR_MAX 4

// Attacker tanks
#define DICE_ATK_TANKS_MIN 0
#define DICE_ATK_TANKS_MAX 2
#define DICE_ATK_TANKS_ARTILLERY_MAX 3

// Attacker infantry
#define DICE_ATK_INFANTRY_MIN 0
#define DICE_ATK_INFANTRY_MAX 2
#define DICE_ATK_INFANTRY_ARTILLERY_MAX 3

// Defender infantry
#define DICE_DEF_INFANTRY_MIN 0
#define DICE_DEF_INFANTRY_MAX 3


// Defender tanks
#define DICE_DEF_TANKS_MIN 0
#define DICE_DEF_TANKS_MAX 1


// Defender Artillery
#define DICE_DEF_ARTILLERY_MIN 0
#define DICE_DEF_ARTILLERY_MAX 3
#define DICE_DEF_ARTILLERY_AIR_MAX 4

// Fighter
#define DICE_FIGHTER_MIN 0
#define DICE_FIGHTER_MAX 2



class Battlesim {
private:
    Dice dice;

    size_t ensemble_size;

    // Attacker
    int attacking_artillery;
    int attacking_artillery_air_supremacy;

    int attacking_infantry;
    int attacking_infantry_artillery;

    int attacking_tanks;
    int attacking_tanks_artillery;

    int attacking_fighters;

    int attacking_hits;
    int attacking_hits_fighter;

    // Defender
    int defending_infantry;
    int defending_tanks;

    int defending_artillery;
    int defending_artillery_air_supremacy;

    int defending_fighters;

    int defending_hits;
    int defending_hits_fighter;

public:

    // Constructor
    Battlesim();
    Battlesim(size_t ensemble_size);

    // Stage 1
    void setup(Board &board);
    void setup_generate(int min_units, int max_units);

    // Stage 2
    void air_supremacy();

    // Stage 3
    void units_fire(bool is_attacker);

    // Stage 4
    void remove_casualties();

    void remove_casualties_attacker();

    void remove_casualties_defender();

    // Stage 5
    void evaluate();

};


#endif //AA_BATTLESIM_H
