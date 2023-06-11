//
// Created by MingF on 2023/6/9.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H


#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <iostream>


class Sudoku {
public:
    Sudoku(): board(9, std::vector<int>(9)), solution(9, std::vector<int>(9)), gen(std::random_device()()) {
        generate(0, 0);
        dig_holes();
    }

    explicit Sudoku(int seed): board(9, std::vector<int>(9)), solution(9, std::vector<int>(9)), gen(std::mt19937(seed)) {
        generate(0, 0);
        dig_holes();
    }

    [[nodiscard]] std::vector<int> get_available_values(int x, int y) const;

    bool generate(int x, int y);

    void dig_holes();

    void display();
private:
    std::vector<std::vector<int>> board;

    std::vector<std::vector<int>> solution;

    std::mt19937 gen;
};


#endif //SUDOKU_SUDOKU_H
