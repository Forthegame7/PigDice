#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct GameState {
    char choice;
    int turn_count = 0;
    int game_score = 0;
    int score_this_turn = 0;
    bool game_over = false;
    bool turn_over = false;
};

int roll();
bool hold(GameState &gs);
void takeTurn(GameState &gs);
void playGame(GameState &gs);

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    GameState my_game;

    cout << "Let's Play PIG Dice!\n";
    cout << "* See how many turns it takes you to get to 20 points.\n";
    cout << "* Turn ends when you hold or roll a 1.\n";
    cout << "* If you roll a 1, you lose all points for the turn.\n";
    cout << "* If you hold, you bank all points for the turn to the game score.\n";

    playGame(my_game);

    return 0;
}

int roll() {
    return (rand() % 6) + 1;
}

bool hold(GameState &gs) {
    cout << "roll or hold? (r/h): ";
    cin >> gs.choice;
    return (gs.choice == 'h' || gs.choice == 'H');
}

void takeTurn(GameState &gs) {
    gs.turn_count++;
    gs.score_this_turn = 0;
    gs.turn_over = false;

    cout << "\nTURN " << gs.turn_count << " - Game Score: " << gs.game_score << "\n";

    while (!gs.turn_over) {
        if (hold(gs)) {
            gs.game_score += gs.score_this_turn;
            cout << "Score Banked This Turn: " << gs.score_this_turn << "\n";
            gs.turn_over = true;
        } else {
            int die = roll();
            if (die == 1) {
                cout << "Die: 1\n";
                cout << "Turn over. No score.\n";
                cout << "Score Banked This Turn: 0\n";
                gs.turn_over = true;
            } else {
                gs.score_this_turn += die;
                cout << "Die: " << die << " - Running score this turn: " << gs.score_this_turn << "\n";
            }
        }
    }
}

void playGame(GameState &gs) {
    while (gs.game_score < 20) {
        takeTurn(gs);
    }

    cout << "\nYou finished with a final score of " << gs.game_score
         << " in " << gs.turn_count << " turns!\n";
    cout << "Thanks for playing PIG Dice!\n";
}