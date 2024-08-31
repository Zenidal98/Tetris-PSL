#include "Leaderboard.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

void Leaderboard::loadScores() {
    std::ifstream file("leaderboard.txt");
    if (file.is_open()) {
        int score;
        while (file >> score) {
            scores.push_back(score);
        }
        file.close();
    }
    std::sort(scores.begin(), scores.end(), std::greater<int>());
}

void Leaderboard::saveScore(int score) {
    std::ofstream file("leaderboard.txt", std::ios::app);
    if (file.is_open()) {
        file << score << std::endl;
        file.close();
    }
}

void Leaderboard::showLeaderboard() const {
    for (const int score : scores) {
        std::cout << score << std::endl;
    }
}
