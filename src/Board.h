//
// Created by per on 20.02.18.
//

#ifndef AA_BOARD_H
#define AA_BOARD_H


#include <cstddef>
#include "util/matrix.cpp"


class Board {
public:
    matrix<float> state;



    Board(std::size_t rows, std::size_t cols);


};


#endif //AA_BOARD_H
