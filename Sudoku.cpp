//
// Created by MingF on 2023/6/9.
//

#include "Sudoku.h"


std::vector<int> Sudoku::get_available_values(const int x, const int y) const {
    const int x_begin = x / 3 * 3;
    const int x_end = x_begin + 3;
    const int y_begin = y / 3 * 3;
    const int y_end = y_begin + 3;
    std::vector<int> available_values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 9; i++) {
        auto it = std::find(available_values.begin(), available_values.end(), board[x][i]);
        if (it != available_values.end()) {
            available_values.erase(it);
        }
    }
    for (int i = 0; i < 9; i++) {
        auto it = std::find(available_values.begin(), available_values.end(), board[i][y]);
        if (it != available_values.end()) {
            available_values.erase(it);
        }
    }
    for (int i = x_begin; i < x_end; i++) {
        for (int j = y_begin; j < y_end; j++) {
            auto it = std::find(available_values.begin(), available_values.end(), board[i][j]);
            if (it != available_values.end()) {
                available_values.erase(it);
            }
        }
    }
    return available_values;
}

bool Sudoku::generate(int x, int y) {
    if (x == 9) {
        x = 0;
        y++;
    }
    if (y == 9) {
        return true;
    }
    std::vector<int> available_values(get_available_values(x, y));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(available_values.begin(), available_values.end(), gen);
    for (int available_value: available_values) {
        board[x][y] = available_value;
        if (generate(x + 1, y)) {
            return true;
        }
        board[x][y] = 0;
    }
    return false;
}

void Sudoku::display() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << board[j][i];
            if (j < 8) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}
