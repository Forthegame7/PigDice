#include
#include "Die.h"

using namespace std;

// Game state structure
struct GameState {
    char choice;
    int turn_count = 1;
    int game_score = 0;
    int score_this_turn = 0;
    bool game_over = false;
    bool turn_over = false;
};

// Function declarations
void hold(GameState &gs);
void takeTurn(GameState &gs, Die &die);
void playGame(GameState &gs, Die &die);
void displayRules();

int main() {
    Die gameDie; // Instantiates Die object from Die class header
    GameState my_game;

    displayRules();
    playGame(my_game, gameDie);

    return 0;
}

void displayRules() {
    cout << "Let's Play PIG Dice!\n\n";
    cout << "* See how many turns it takes you to get to 20 points.\n";
    cout << "* Turn ends when you hold or roll a 1.\n";
    cout << "* If you roll a 1, you lose all points for the turn.\n";
    cout << "* If you hold, you bank all points for the turn to the game score.\n\n";
}

void hold(GameState &gs) {
    gs.game_score += gs.score_this_turn;
    cout << "Score Banked This Turn: " << gs.score_this_turn << "\n\n";
    gs.turn_count++;
    gs.score_this_turn = 0;
    gs.turn_over = true;
}

void takeTurn(GameState &gs, Die &die) {
    gs.turn_over = false;
    cout << "TURN " << gs.turn_count << " - Game Score: " << gs.game_score << "\n";

    while (!gs.turn_over) {
        cout << "roll or hold? (r/h): ";
        cin >> gs.choice;

        if (gs.choice == 'r') {
            int rolledVal = die.rollDie();
            if (rolledVal == 1) {
                cout << "Die: 1\n";
                cout << "Turn over. No score.\n";
                cout << "Score Banked This Turn: 0\n\n";
                gs.turn_count++;
                gs.score_this_turn = 0;
                gs.turn_over = true;
            } else {
                gs.score_this_turn += rolledVal;
                cout << "Die: " << rolledVal << " - Running score this turn: " << gs.score_this_turn << "\n";
            }
        } else if (gs.choice == 'h') {
            hold(gs);
        }
    }
}

void playGame(GameState &gs, Die &die) {
    while (gs.game_score < 20) {
        takeTurn(gs, die);
    }

    gs.game_over = true;
    cout << "You finished with a final score of " << gs.game_score
         << " in " << (gs.turn_count - 1) << " turns!\n";
    cout << "Thanks for playing PIG Dice!\n";
}