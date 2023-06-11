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
    Sudoku(): board(9, std::vector<int>(9)), seeds(9, std::vector<unsigned int>(9)) {
        std::random_device rd;
        std::mt19937 gen(rd());
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                seeds[i][j] = gen();
            }
        }
        generate(0, 0);
        dig_holes(gen);
    }

    Sudoku(int seed): board(9, std::vector<int>(9)), seeds(9, std::vector<unsigned int>(9)) {
        std::mt19937 gen(seed);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                seeds[i][j] = gen();
            }
        }
        generate(0, 0);
        dig_holes(gen);
    }

    [[nodiscard]] std::vector<int> get_available_values(int x, int y) const;

    bool generate(int x, int y);

    void dig_holes(std::mt19937 generator);

    void display();
private:
    std::vector<std::vector<int>> board;

    std::vector<std::vector<int>> solution;

    std::vector<std::vector<unsigned int>> seeds;
};


#endif //SUDOKU_SUDOKU_H
