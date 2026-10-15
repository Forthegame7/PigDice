#ifndef PIGGAME_H
#define PIGGAME_H

#include "die.h"

class PigGame {
private:
    int m_gameScore;
    int m_turnCount;
    int m_scoreThisTurn;
    bool m_isGameOver;
    Die m_die;

public:
    PigGame();
    void displayRules() const;
    void hold();
    void takeTurn();
    void playGame();
};

#endif