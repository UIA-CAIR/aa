//
// Created by per on 19.02.18.
//



#include "game/Game.h"
#include "Dice.h"
#include "Board.h"
#include "battlesim/Battlesim.h"

int main(char* arg) {


    Game game = Game();


    Battlesim sim = Battlesim();

    sim.setup_generate(1, 5);
    sim.evaluate();



}