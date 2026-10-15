#include <iostream>
#include <random>

using namespace std;

struct GameState {
    int gameScore;
    int turnCount;
    int scoreThisTurn;
    bool isGameOver;
};

void displayRules();
int rollDie(mt19937 &generator);
void hold(GameState &state);
void takeTurn(GameState &state, mt19937 &generator);
void playGame(GameState &state, mt19937 &generator);

int main() {
    GameState state = {0, 1, 0, false};

    random_device rd;
    mt19937 generator(rd());

    playGame(state, generator);
    return 0;
}

void displayRules() {
    cout << "Let's Play PIG Dice!\n\n";
    cout << "* See how many turns it takes you to get to 20 points.\n";
    cout << "* Turn ends when you hold or roll a 1.\n";
    cout << "* If you roll a 1, you lose all points for the turn.\n";
    cout << "* If you hold, you bank all points for the turn to the game score.\n\n";
}

int rollDie(mt19937 &generator) {
    uniform_int_distribution<int> dist(1, 6);
    return dist(generator);
}

void hold(GameState &state) {
    state.gameScore += state.scoreThisTurn;
    cout << "Score Banked This Turn: " << state.scoreThisTurn << "\n\n";
    state.turnCount++;
    state.scoreThisTurn = 0;
}

void takeTurn(GameState &state, mt19937 &generator) {
    bool turnOver = false;
    cout << "TURN " << state.turnCount << " - Game Score: " << state.gameScore << "\n";

    while (!turnOver) {
        char choice;
        cout << "roll or hold? (r/h): ";
        cin >> choice;

        if (choice == 'r') {
            int rolledVal = rollDie(generator);
            if (rolledVal == 1) {
                cout << "Die: 1\n";
                cout << "Turn over. No score.\n";
                cout << "Score Banked This Turn: 0\n\n";
                state.turnCount++;
                state.scoreThisTurn = 0;
                turnOver = true;
            } else {
                state.scoreThisTurn += rolledVal;
                cout << "Die: " << rolledVal << " - Running score this turn: " << state.scoreThisTurn << "\n";
            }
        } else if (choice == 'h') {
            hold(state);
            turnOver = true;
        }
    }
}

void playGame(GameState &state, mt19937 &generator) {
    displayRules();
    while (state.gameScore < 20) {
        takeTurn(state, generator);
    }

    state.isGameOver = true;
    cout << "You finished with a final score of " << state.gameScore
         << " in " << (state.turnCount - 1) << " turns!\n";
    cout << "Thanks for playing PIG Dice!\n";
}
