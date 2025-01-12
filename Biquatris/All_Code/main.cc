#include <iostream>
#include <memory>
#include "canvas.h"
#include "player.h"
#include "observer.h"
#include "textObserver.h"
#include "graphicsobserver.h"
#include "shape.h"
#include "block.h"
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

void welcomeMessage() {
    cout << "Welcome to Biquadris! A turn-based Tetris-inspired game." << endl;
    cout << "*------------------------------------------------------*"<< endl;
    cout << "\n Press enter to start the Game:";
    cin.get();
}

bool gameLogic(Player &player1, Player &player2, vector<std::unique_ptr<Observer>>& observers, int &highscore) {
    while (!player1.gameOver() && !player2.gameOver()) {
        // Player 1's turn
        bool turnEnded = false;
        while (!turnEnded) {
            // Notify all observers
            for (const auto &observer : observers) {
                observer->notify();
            }

            turnEnded = player1.takeTurn(player2);
            if (player1.gameOver()) break;
        }

        if (player1.gameOver()) break;

        // Player 2's turn
        turnEnded = false;
        while (!turnEnded) {
            // Notify all observers
            for (const auto &observer : observers) {
                observer->notify();
            }

            turnEnded = player2.takeTurn(player1);
            if (player2.gameOver()) break;
        }
    }

    // End game message
    if (player1.gameOver()) {
        std::cout << "Player 1 loses!" << std::endl;
    } else if (player2.gameOver()) {
        std::cout << "Player 2 loses!" << std::endl;
    }

    if(player1.getScore() > player2.getScore()) {
        highscore = player1.getScore();
    } else {
        player2.getScore();
    }
}

int main(int argc, char *argv[]) {
    // Command line arguments
    bool textMode = false;
    int seed = 556;
    string scriptfile1 = "sequence1.txt";
    string scriptfile2 = "sequence2.txt";
    int startLevel = 0;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-text") {
            textMode = true;
        } else if (arg == "-seed" && i + 1 < argc) {
            std::string s;
            std::cin >> s; // Read input into string

            std::istringstream iss(s); // Create an istringstream from the string
            if(!(iss >> seed)) {
                cerr << "That is an invalid seed" << endl;
                return 1;
            }

        } else if (arg == "-scriptfile1" && i + 1 < argc) {
            scriptfile1 = argv[++i];
        } else if (arg == "-scriptfile2" && i + 1 < argc) {
            scriptfile2 = argv[++i];
        } else if (arg == "-startlevel" && i + 1 < argc) {

            std::string s;
            std::cin >> s; // Read input into string

            std::istringstream iss(s); // Create an istringstream from the string
            if(!(iss >> startLevel)) {
                cerr << "That is an invalid starting level." << endl;
                return 1;
            }
        } else {
            cerr << "Unknown option: " << arg << "\n";
            return 1;
        }
    }

    welcomeMessage();
    std::srand(seed);

    Canvas game_board1(11, 18);
    Canvas game_board2(11, 18);

    ifstream file1{scriptfile1};
    ifstream file2{scriptfile2};

    // Level setup
    std::shared_ptr<Level> p1LVL, p2LVL;
    if (startLevel == 0) {
        p1LVL = std::make_shared<Level0>(file1);
        p2LVL = std::make_shared<Level0>(file2);
    } else if (startLevel == 1) {
        p1LVL = std::make_shared<Level1>(file1);
        p2LVL = std::make_shared<Level1>(file2);
    } else if (startLevel == 2) {
        p1LVL = std::make_shared<Level2>(file1);
        p2LVL = std::make_shared<Level2>(file2);
    } else if (startLevel == 3) {
        p1LVL = std::make_shared<Level3>(file1);
        p2LVL = std::make_shared<Level3>(file2);
    } else if (startLevel == 4) {
        p1LVL = std::make_shared<Level4>(file1);
        p2LVL = std::make_shared<Level4>(file2);
    } else {
        cerr << "Invalid starting level!" << endl;
        return 1;
    }

    Queue queue1(p1LVL.get());
    Queue queue2(p2LVL.get());

    Player player1(1, 0, std::move(p1LVL), queue1, game_board1, queue1.getCurrent());
    Player player2(2, 0, std::move(p2LVL), queue2, game_board2, queue2.getCurrent());

    // Observer setup
    vector<std::unique_ptr<Observer>> observers;

    if (textMode) {
        observers.push_back(std::make_unique<TextObserver>(&player1, &player2, 11, 15));
    } else {
        observers.push_back(std::make_unique<TextObserver>(&player1, &player2, 11, 15));
        //observers.push_back(std::make_unique<GraphicObserver>(&player1, &player2, 11, 15));
    }

    // Game loop
    int highscore = 0;
    while (true) {
        // Start the game logic
        gameLogic(player1, player2, observers, highscore);

        int temp;
        string highest_score_owner;
        if(player1.getScore() > player2.getScore()) {
            temp = player1.getScore();
            highest_score_owner = "Player 1";
        } else {
            temp = player2.getScore();
            highest_score_owner = "Player 2";
        }

        if(temp > highscore) {
            highscore = temp;
        }
        cout << "The highest score is " << highscore << " by " << highest_score_owner << endl;

        // Prompt to play again
        char c;
        cout << "Do you want to play again? (y / n): ";
        cin >> c;
        if (c == 'y' || c == 'Y') {
            cout << "Starting a new game..." << endl;
            p1LVL = std::make_shared<Level0>(file1);
            p2LVL = std::make_shared<Level0>(file2);
            queue1 = Queue(p1LVL.get());
            queue2 = Queue(p2LVL.get());
            player1.reset(std::move(p1LVL));
            player2.reset(std::move(p2LVL));
        } else if (c == 'n' || c == 'N') {
            cout << "Thank you for playing Biquadris!" << endl;
            break;
        } else {
            cout << "That was not a correct output, please try again." << endl;
        }
    }

    file1.close();
    file2.close();
}

