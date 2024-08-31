#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <vector>

class Leaderboard {
public:
    void loadScores();
    void saveScore(int score);
    void showLeaderboard() const;
    
private:
    std::vector<int> scores;
};

#endif // LEADERBOARD_HPP
