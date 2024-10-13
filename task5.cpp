#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <set>

using state = std::vector<std::vector<int>>;

bool can_move(int card1, int card2) {
    return card1 < card2;
}

bool can_remove(const std::vector<int>& vec) {
    std::vector<int> sequence{14, 13, 12, 11, 10, 9, 8, 7, 6};
    if (vec.size() != sequence.size()) {
        return false;
    }
    if (vec[0] != 14 || vec[sequence.size() - 1] != 6) {
        return false;
    }
    for (int i = 0; i < sequence.size(); ++i) {
        if (vec[i] != sequence[i]) {
            return false;
        }
    }
    return true;
}

int bfs_solve(std::vector<std::vector<int>>& piles) {
    std::queue<std::pair<state, int>> pair;  // Очередь для BFS (состояние + количество ходов)
    std::set<state> visited;  // Множество для посещенных состояний

    std::vector<std::vector<int>> copy(8);
    for (int i = 0; i < 8; ++i) {
        if (!can_remove(piles[i])) {
            copy[i] = piles[i];
        }
        else {
            std::vector<int> emp;
            copy[i] =  emp;
        }
    }
    pair.push({copy, 0});
    visited.insert(copy);
    

    while (!pair.empty()) {
        auto [current_state, moves] = pair.front();
        pair.pop();

        // Если все стопки пусты, мы нашли решение
        bool all_empty = true;
        for (const auto& pile : current_state) {
            if (!pile.empty()) {
                all_empty = false;
                break;
            }
        }
        if (all_empty) {
            return moves;
        }

        for (int from = 0; from < 8; ++from) {
            if (current_state[from].empty()) {
                continue;
            }
            int from_top = current_state[from].back();
            
            for (int to = 0; to < 8; ++to) {
                if (from == to) {
                    continue;
                }
                if (current_state[to].empty()) {
                    continue;
                }
                if (can_move(from_top, current_state[to].back())) {
                    state next = current_state;
                    next[to].push_back(next[from].back());
                    next[from].pop_back();

                    if (can_remove(next[to])) {
                        while (!next[to].empty()) {
                            next[to].pop_back();
                        }
                    }

                    if (visited.find(next) == visited.end()) {
                            visited.insert(next);
                            pair.push({next, moves + 1});
                        }
                }
            }
        }
    }
    return -1;
}

int main() {
    // Пример входных данных: 8 кучек по 9 карт
    std::vector<std::vector<int>> piles = {
        {14, 13, 12, 11, 10, 9, 8, 7, 6},
        {14, 13, 12, 11, 10, 9, 8, 7, 6},
        {14, 13, 12, 11, 10, 9, 8, 7, 6},
        {14, 13, 12, 11, 10, 9, 8, 7, 6},
        {14, 13, 12, 11, 10, 9, 8, 7, 6},
        {14, 13, 12, 11, 10, 9, 8, 7, 6},
        {14, 13, 12, 11, 10, 9, 8, 7, 6},
        {14, 13, 12, 11, 10, 9, 8, 7, 6}
    };

    int result = bfs_solve(piles);
    if (result != -1) {
        std::cout << "Минимальное количество ходов: " << result << '\n';
    } else {
        std::cout << "Решение не найдено" << '\n';
    }

    return 0;
}
