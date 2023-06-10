//
// Created by MingF on 2023/6/9.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H


#include <vector>
#include <algorithm>
#include <random>
#include <iostream>


class Sudoku {
public:
    Sudoku(): board(9, std::vector<int>(9)) {
        generate(0, 0);
    }

    [[nodiscard]] std::vector<int> get_available_values(int x, int y) const;

    bool generate(int x, int y);

    void display();

    std::vector<std::vector<int>> board;
};


#endif //SUDOKU_SUDOKU_H
