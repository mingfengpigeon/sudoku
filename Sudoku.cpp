//
// Created by MingF on 2023/6/9.
//

#include "Sudoku.h"


bool IsRemovable::operator()(int x, int y) const {
    if (x == target_x and y != target_y) {
        return true;
    }
    if (y == target_y and x != target_x) {
        return true;
    }
    if (x >= target_x_begin and x < target_x_end and y >= target_y_begin and y < target_y_end and
        x != target_x and y != target_y) {
        return true;
    }
    return false;
}

std::vector<int> Sudoku::get_available_values(const int target_x, const int target_y) const {
    IsRemovable is_removable(target_x, target_y);
    std::vector<int> available_values;
    for (int i = 0; i <= 9; i++) {
        available_values.push_back(i);
    }
    for (int i = 0; i <= 80; i++) {
        const int x = i % 9;
        const int y = i / 9;
        if (is_removable(x, y)) {
            auto it = std::find(available_values.begin(), available_values.end(), board[y][x]);
            if (it != available_values.end()) {
                available_values.erase(it);
            }
        }
    }
    return available_values;
}

void Sudoku::display() const {
    for (int i = 0; i <= 80; i++) {
        const int x = i % 9;
        const int y = i / 9;
        if (x == 0) {
            std::cout << std::endl;
        }
        if (x != 9) {
            std::cout << " ";
        }
        std::cout << board[y][x];
    }
}
