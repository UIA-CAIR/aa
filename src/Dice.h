//
// Created by per on 19.02.18.
//
#include <iostream>
#include <random>
#include <chrono>

#ifndef AA_DICE_H
#define AA_DICE_H



class Dice {
private:
    typedef std::chrono::high_resolution_clock tClock;
    std::uniform_int_distribution<int> dice;
    std::uniform_real_distribution<float> dice_f;
    std::default_random_engine dre;
    void init();

public:
    Dice();
    Dice(int min, int max);
    int roll();
    float roll_f();
    int* sample(int n);
};


#endif //AA_DICE_H
