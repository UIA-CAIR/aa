//
// Created by per on 20.02.18.
//

#include "Battlesim.h"
#include <algorithm>

// https://www.axisandallies.org/wp-content/uploads/2013/03/Axis-Allies-1914.pdf
// ABSORBED HITS FOR TANKS ARE IGNORED // TODO
/*
 * However, attacking (but not defending) tanks have a special ability to absorb hits.  You, as the attacker, reduce the number of
hits scored against you by the number of tanks you have in the battle (to a minimum of zero).  For each tank you have, you
remove one die that scored a hit from your side of the battle board.
 */
// The Reason for this is that there must be done a selection of which units to eliminate. This complicate things...
// Currently Infantry == Tanks

Battlesim::Battlesim() {

}

Battlesim::Battlesim(size_t ensemble_size) {

}

void Battlesim::setup(Board &board) {
    // TODO
}

void Battlesim::setup_generate(int min_units, int max_units) {
    /// Generates a composition of units to battle

    // Initial Attacker Composition
    attacking_infantry = std::min(min_units, int(dice.roll_f() * max_units));
    attacking_tanks = std::min(min_units, int(dice.roll_f() * max_units));
    attacking_artillery = std::min(min_units, int(dice.roll_f() * max_units));
    attacking_fighters = std::min(min_units, int(dice.roll_f() * max_units));
    attacking_infantry_artillery = 0;
    attacking_artillery_air_supremacy = 0;
    attacking_tanks_artillery = 0;
    attacking_hits = 0;
    attacking_hits_fighter = 0;

    // Initial Defender Composition
    defending_infantry = std::min(min_units, int(dice.roll_f() * max_units));
    defending_tanks = std::min(min_units, int(dice.roll_f() * max_units));
    defending_artillery = std::min(min_units, int(dice.roll_f() * max_units));
    defending_fighters = std::min(min_units, int(dice.roll_f() * max_units));
    defending_artillery_air_supremacy = 0;
    defending_hits = 0;
    defending_hits_fighter = 0;



    // Determine Artillery Support - Attacker
    // Distribute artillery bonus on inf and tanks
    // Todo, do distribution of artillery support matter?
    // Todo, cleanup this
    int i = 0;
    while(i < attacking_artillery && attacking_tanks > 0){
        attacking_tanks -= 1;
        attacking_tanks_artillery += 1;
        i++;
    }
    while(i < attacking_artillery && attacking_infantry > 0){
        attacking_infantry -= 1;
        attacking_infantry_artillery += 1;
        i++;
    }


    // Determine Air Supremacy
    air_supremacy();

    if(attacking_fighters > 0 && defending_fighters == 0) {
        attacking_artillery_air_supremacy = attacking_artillery;
        attacking_artillery = 0;
    } else if(defending_fighters > 0 && attacking_fighters == 0) {
        defending_artillery_air_supremacy = defending_artillery;
        defending_artillery = 0;
    } else if(attacking_fighters != 0 && defending_fighters != 0) {
        // Both still have units. this is a error
        std::runtime_error("A illegal state happens where both players have more than 1 fighter alive. This makes air supremacy logic faulty!");
    }



}

void Battlesim::air_supremacy() {

    bool attacker = true;
    while(attacking_fighters > 0 && defending_fighters > 0) {

        // Attacker - Roll Dice
        auto d = dice.roll();


        if(attacker && d > DICE_FIGHTER_DEFEAT_MIN && d <= DICE_FIGHTER_DEFEAT_MAX) {
            defending_fighters -= 1;
        }
        else if(!attacker && d > DICE_FIGHTER_DEFEAT_MIN && d <= DICE_FIGHTER_DEFEAT_MAX){
            attacking_fighters -= 1;
        }

        attacker = !attacker;
    }



}

void Battlesim::units_fire(bool is_attacker) {
    

    if(is_attacker){
        // Summarize number of hits based on dice value (ranges defined in header)
        int n_hits = 0;
        int n_hits_fighter = 0;
        int roll;

        for(int i = 0; i < attacking_artillery; i++) {
            roll = dice.roll();
            if(roll > DICE_ATK_ARTILLERY_MIN && roll <= DICE_ATK_ARTILLERY_MAX){
                n_hits += 1;
            }
        }

        for(int i = 0; i < attacking_artillery_air_supremacy; i++) {
            roll = dice.roll();
            if(roll > DICE_ATK_ARTILLERY_MIN && roll <= DICE_ATK_ARTILLERY_AIR_MAX){
                n_hits += 1;
            }
        }

        for(int i = 0; i < attacking_infantry; i++) {
            roll = dice.roll();
            if(roll > DICE_ATK_INFANTRY_MIN && roll <= DICE_ATK_INFANTRY_MAX){
                n_hits += 1;
            }
        }

        for(int i = 0; i < attacking_infantry_artillery; i++) {
            roll = dice.roll();
            if(roll > DICE_ATK_INFANTRY_MIN && roll <= DICE_ATK_INFANTRY_ARTILLERY_MAX){
                n_hits += 1;
            }
        }

        for(int i = 0; i < attacking_tanks; i++) {
            roll = dice.roll();
            if(roll > DICE_ATK_TANKS_MIN && roll <= DICE_ATK_TANKS_MAX){
                n_hits += 1;
            }
        }

        for(int i = 0; i < attacking_tanks_artillery; i++) {
            roll = dice.roll();
            if(roll > DICE_ATK_TANKS_MIN && roll <= DICE_ATK_TANKS_ARTILLERY_MAX){
                n_hits += 1;
            }
        }

        for(int i = 0; i < attacking_fighters; i++) {
            roll = dice.roll();
            if(roll > DICE_FIGHTER_MIN && roll <= DICE_FIGHTER_MAX){
                n_hits_fighter += 1;
            }
        }
        
        
        // Set number of hits
        attacking_hits = n_hits;
        attacking_hits_fighter = n_hits_fighter;
        
    } else {

        // Summarize number of hits based on dice value (ranges defined in header)
        int n_hits = 0;
        int n_hits_fighter = 0;
        int roll;

        for(int i = 0; i < defending_artillery; i++) {
            roll = dice.roll();
            if(roll > DICE_DEF_ARTILLERY_MIN && roll <= DICE_DEF_ARTILLERY_MAX){
                n_hits += 1;
            }
        }

        for(int i = 0; i < defending_artillery_air_supremacy; i++) {
            roll = dice.roll();
            if(roll > DICE_DEF_ARTILLERY_MIN && roll <= DICE_DEF_ARTILLERY_AIR_MAX){
                n_hits += 1;
            }
        }

        for(int i = 0; i < defending_infantry; i++) {
            roll = dice.roll();
            if(roll > DICE_DEF_INFANTRY_MIN && roll <= DICE_DEF_INFANTRY_MAX){
                n_hits += 1;
            }
        }
        
        for(int i = 0; i < defending_tanks; i++) {
            roll = dice.roll();
            if(roll > DICE_DEF_TANKS_MIN && roll <= DICE_DEF_TANKS_MAX){
                n_hits += 1;
            }
        }

        for(int i = 0; i < defending_fighters; i++) {
            roll = dice.roll();
            if(roll > DICE_FIGHTER_MIN && roll <= DICE_FIGHTER_MAX){
                n_hits_fighter += 1;
            }
        }


        // Set number of hits
        defending_hits = n_hits;
        defending_hits_fighter = n_hits_fighter;

    }




}

void Battlesim::remove_casualties_attacker() {
    for (int i = 0; i < attacking_hits; i++){

        if(defending_fighters > 0){
            defending_fighters -= 1;
        } else if(defending_tanks > 0) {
            defending_tanks -= 1;
        } else if(defending_artillery_air_supremacy > 0) {
            defending_artillery_air_supremacy -=1;
        } else if(defending_artillery > 0) {
            defending_artillery -= 1;
        } else if(defending_infantry > 0) {
            defending_infantry -= 1;
        } else {
            // None left
            break;
        }
    }

    for (int i = 0; i < attacking_hits_fighter; i++){
        if(defending_infantry > 0){
            defending_infantry -= 1;
        }
    }
}

void Battlesim::remove_casualties_defender() {
    for (int i = 0; i < defending_hits; i++){

        if(attacking_fighters > 0){
            attacking_fighters -= 1;
        } else if(attacking_tanks > 0) {
            attacking_tanks -= 1;
        } else if(attacking_tanks_artillery > 0) {
            attacking_tanks_artillery -= 1;
        } else if(attacking_artillery_air_supremacy > 0) {
            attacking_artillery_air_supremacy -=1;
        } else if(attacking_artillery > 0) {
            attacking_artillery -= 1;
        } else if(attacking_artillery > 0) {
        attacking_artillery -= 1;
        }else if(attacking_infantry > 0) {
            attacking_infantry -= 1;
        }else if(attacking_infantry_artillery > 0) {
            attacking_infantry_artillery -= 1;
        } else {
            // None left
            break;
        }
    }

    for (int i = 0; i < defending_hits_fighter; i++){
        if(attacking_infantry > 0){
            attacking_infantry -= 1;
        }
    }
}


void Battlesim::remove_casualties() {
    // Removal order // TODO this should be selection with some priority?. how can we determine what is more worth?!
    // 1. Fighters
    // 2. Tanks
    // 3. Artillery
    // 4. Infantry

    // Attackers fighters remove defending infantry.
    // TODO - Case: If def infantry == 1 but has other units. Ignore rest of fighter hits?
    // TODO - Current behaviour: Ignore rest of fighters

    remove_casualties_attacker();
    remove_casualties_defender();

    int attacker_sum = attacking_tanks + attacking_tanks_artillery + attacking_artillery_air_supremacy + attacking_artillery + attacking_infantry_artillery + attacking_infantry + attacking_fighters;
    int defender_sum = defending_tanks + defending_artillery_air_supremacy + defending_artillery + defending_infantry + defending_fighters;

    std::cout << attacker_sum << " - " << defender_sum << std::endl;
}




void Battlesim::evaluate() {

    units_fire(true);
    units_fire(false);
    remove_casualties();

}



