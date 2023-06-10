//
// Created by MingF on 2023/6/9.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H


#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <iostream>


class IsRemovable{
public:
    IsRemovable(int x, int y): target_x(x), target_y(y), target_x_begin(x / 3 * 3), target_x_end(x / 3 * 3 + 3), target_y_begin(y / 3 * 3), target_y_end(y / 3 * 3 + 3) {}

    bool operator()(int x, int y) const;
private:
    int target_x;

    int target_y;

    int target_x_begin;

    int target_x_end;

    int target_y_begin;

    int target_y_end;
};


class Sudoku {
public:
    Sudoku(): board(9, std::vector<int>(9)) {
        for (int i = 0; i <= 80; i++) {
            const int x = i % 9;
            const int y = i / 9;
            IsRemovable is_removable(x, y);
            std::map<int, int> times;
            std::vector<int> available_values(get_available_values(x, y));
            for (int available_value: available_values) {
                times[available_value] = 0;
            }
            for (int j = 0; j <= 80; j++) {
                const int inner_x = j % 9;
                const int inner_y = j / 9;
                if (is_removable(inner_x, inner_y)) {
                    auto it = std::find(available_values.begin(), available_values.end(), board[inner_y][inner_x]);
                    if (it != available_values.end()) {
                        times[board[inner_y][inner_x]]++;
                    }
                }
            }
            auto it = min_element(times.begin(), times.end(), [](const auto& left, const auto& right) {
                return left.second < right.second;
            });
            available_values.erase(available_values.begin(), available_values.end());
            for (std::pair<const int, int> time: times) {
                if (time.second == it->second) {
                    available_values.push_back(time.first);
                }
            }
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, static_cast<int>(available_values.size()) - 1);
            board[y][x] = available_values[dis(gen)];
        }
    };

    [[nodiscard]] std::vector<int> get_available_values(int target_x, int target_y) const;

    std::vector<std::vector<int>> board;

    void display() const;
};


#endif //SUDOKU_SUDOKU_H
