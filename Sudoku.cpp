//
// Created by MingF on 2023/6/9.
//

#include "Sudoku.h"


std::vector<int> Sudoku::get_available_values(const int x, const int y) const {
    const int x_begin = x / 3 * 3;
    const int y_begin = y / 3 * 3;
    std::vector<int> available_values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 9; i++) {
        if (i != x) {
            auto it = std::find(available_values.begin(), available_values.end(), board[x][i]);
            if (it != available_values.end()) {
                available_values.erase(it);
            }
        }
        if (i != y) {
            auto it = std::find(available_values.begin(), available_values.end(), board[i][y]);
            if (it != available_values.end()) {
                available_values.erase(it);
            }
        }
        if (x_begin + i % 3 != x and y_begin + i / 3 != y) {
            auto it = std::find(available_values.begin(), available_values.end(), board[x_begin + i % 3][y_begin + i / 3]);
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
    std::mt19937 gen(seeds[x][y]);
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


void Sudoku::dig_holes(std::mt19937 generator) {
    std::vector<std::pair<int, int>> remove_indices;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            remove_indices.emplace_back(i, j);
        }
    }
    std::shuffle(remove_indices.begin(), remove_indices.end(), generator);
    for (std::pair<int, int> remove_index: remove_indices) {
        if (get_available_values(remove_index.first, remove_index.second).size() == 1) {
            board[remove_index.first][remove_index.second] = 0;
        }
    }

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

