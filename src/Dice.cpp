//
// Created by per on 19.02.18.
//

#include "Dice.h"



Dice::Dice(): dice(1, 6), dice_f(0.0, 1.0) {
    init();
}

Dice::Dice(int min, int max): dice(min, max) {
    init();
}

int Dice::roll() {
    return dice(dre);
}

float Dice::roll_f(){
    return dice_f(dre);
};

int *Dice::sample(int n) {
    auto * samples = new int[n];

    for(int i = 0; i < n; i++) {
        samples[i] = dice(dre);
    }

    return samples;
}

void Dice::init() {
    tClock::duration d = tClock::now().time_since_epoch();
    dre.seed(static_cast<unsigned long>(d.count()));
}
