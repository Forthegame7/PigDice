#include "PigGame.h"
#include <iostream>

using namespace std;

PigGame::PigGame() {
    m_gameScore = 0;
    m_turnCount = 1;
    m_scoreThisTurn = 0;
    m_isGameOver = false;
}

void PigGame::displayRules() const {
    cout << "Let's Play PIG Dice!\n\n";
    cout << "* See how many turns it takes you to get to 20 points.\n";
    cout << "* Turn ends when you hold or roll a 1.\n";
    cout << "* If you roll a 1, you lose all points for the turn.\n";
    cout << "* If you hold, you bank all points for the turn to the game score.\n\n";
}

void PigGame::hold() {
    m_gameScore += m_scoreThisTurn;
    cout << "Score Banked This Turn: " << m_scoreThisTurn << "\n\n";
    m_turnCount++;
    m_scoreThisTurn = 0;
}

void PigGame::takeTurn() {
    bool turnOver = false;
    cout << "TURN " << m_turnCount << " - Game Score: " << m_gameScore << "\n";

    while (!turnOver) {
        char choice;
        cout << "roll or hold? (r/h): ";
        cin >> choice;

        if (choice == 'r') {
            int rolledVal = m_die.rollDie();
            if (rolledVal == 1) {
                cout << "Die: 1\n";
                cout << "Turn over. No score.\n";
                cout << "Score Banked This Turn: 0\n\n";
                m_turnCount++;
                m_scoreThisTurn = 0;
                turnOver = true;
            } else {
                m_scoreThisTurn += rolledVal;
                cout << "Die: " << rolledVal << " - Running score this turn: " << m_scoreThisTurn << "\n";
            }
        } else if (choice == 'h') {
            hold();
            turnOver = true;
        }
    }
}

void PigGame::playGame() {
    displayRules();
    while (m_gameScore < 20) {
        takeTurn();
    }

    m_isGameOver = true;
    cout << "You finished with a final score of " << m_gameScore
         << " in " << (m_turnCount - 1) << " turns!\n";
    cout << "Thanks for playing PIG Dice!\n";
}