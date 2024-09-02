#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

class Leaderboard {
public:
    void loadScores();
    void saveScore(int score);
    void showLeaderboard();

private:
    static const int max_scores = 20;  // Numero massimo di punteggi
    int scores[max_scores];            // Array per i punteggi
    int num_scores = 0;                // Numero di punteggi attualmente salvati

    void bubbleSort();                 // Metodo per ordinare i punteggi
};

#endif // LEADERBOARD_HPP
