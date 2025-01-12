#include <iostream>
#include <memory>
#include "player.h"
#include "canvas.h"
#include "queue.h"
#include "level.h"
#include "effect.h" // Include effect header

using namespace std;

Player::Player(int playerID, int score, std::shared_ptr<Level> level, Queue& queue, Canvas& canvas, std::shared_ptr<Shape> currentShape)
    : playerID{playerID}, score{score}, level{std::move(level)}, queue{queue}, canvas{canvas}, currentShape{currentShape} {}


int Player::getPlayerID() const {
    return playerID;
}

std::shared_ptr<Shape> Player::getCurrentShape() const {
    return currentShape;
}

void Player::setCurrentShape(std::shared_ptr<Shape> shape) {
    currentShape = shape;
    return;
}

void Player::levelUp() {
    int dif = level->getDifficulty();
    if (dif == 0) {
        level = std::make_shared<Level1>(level->getSequence());
    } else if (dif == 1) {
        level = std::make_shared<Level2>(level->getSequence());
    } else if (dif == 2) {
        level = std::make_shared<Level3>(level->getSequence());
    } else if (dif == 3) {
        level = std::make_shared<Level4>(level->getSequence());
    } else {
        std::cerr << "Cannot level up anymore." << std::endl;
    }
}

void Player::levelDown() {
    int dif = level->getDifficulty();
    if (dif == 0) {
        std::cerr << "Cannot level down anymore." << std::endl;
    } else if (dif == 1) {
        level = std::make_shared<Level0>(level->getSequence());
    } else if (dif == 2) {
        level = std::make_shared<Level1>(level->getSequence());
    } else if (dif == 3) {
        level = std::make_shared<Level2>(level->getSequence());
    } else {
        level = std::make_shared<Level3>(level->getSequence());
    }
}

int Player::getDifficulty() const {
    return level->getDifficulty();
}

Level* Player::getLevel() const {
    return level.get();
}

void Player::addScore(int points) {
    score += points;
}

int Player::getScore() const {
    return score;
}

Canvas& Player::getCanvas() const {
    return canvas;
}

Queue& Player::getQueue() const {
    return queue;
}

bool Player::takeTurn(Player& opponent) {

    string command;
    cout << "Player " << playerID << "，enter command （left, right, down, drop）: ";
    cin >> command;

    // Handle effect-related movements
    bool hasHeavy = EffectManager::getInstance().hasEffect(*this, "heavy");

    if(getDifficulty() == 4 || getDifficulty() == 3) {
        // Apply the heavy effect
        EffectManager::getInstance().addEffect(*this, std::make_shared<BlindEffect>());
    }

    // Handle command multipliers
    int multiplier = 1;
    size_t pos = 0;
    while (isdigit(command[pos])) {
        pos++;
    }
    if (pos > 0) {
        multiplier = stoi(command.substr(0, pos));
        command = command.substr(pos);
    }

    for (int i = 0; i < multiplier; ++i) {
        if (command == "left") {
            auto newShape = currentShape->left();
            if (canvas.check_fit(newShape.get())) {
                currentShape = newShape;
                if (hasHeavy) {
                    auto heavyShape = currentShape->down()->down();
                    if (canvas.check_fit(heavyShape.get())) {
                        currentShape = heavyShape;
                    } else {
                        cout << "Cannot move down due to heavy effect!" << endl;
                    }
                }
            } else {
                cout << "Invalid move!" << endl;
            }
        } else if (command == "right") {
            auto newShape = currentShape->right();
            if (canvas.check_fit(newShape.get())) {
                currentShape = newShape;
                if (hasHeavy) {
                    auto heavyShape = currentShape->down()->down();
                    if (canvas.check_fit(heavyShape.get())) {
                        currentShape = heavyShape;
                    } else {
                        cout << "Cannot move down due to heavy effect!" << endl;
                    }
                }
            } else {
                cout << "Invalid move!" << endl;
            }
        } else if (command == "down") {
            auto newShape = currentShape->down();
            if (canvas.check_fit(newShape.get())) {
                currentShape = newShape;
            } else {
                cout << "Invalid move!" << endl;
            }
        } else if (command == "clockwise") {
            auto newShape = currentShape->clockwise();
            if (canvas.check_fit(newShape.get())) {
                currentShape = newShape;
                if (hasHeavy) {
                    auto heavyShape = currentShape->down()->down();
                    if (canvas.check_fit(heavyShape.get())) {
                        currentShape = heavyShape;
                    } else {
                        cout << "Cannot move down due to heavy effect!" << endl;
                    }
                }
            } else {
                cout << "Invalid move!" << endl;
            }

        } else if (command == "counterclockwise") {
            // check if the counter- clockwise shape will fit
            auto newShape = currentShape->counter();
            if (canvas.check_fit(newShape.get())) {
                currentShape = newShape;
                if (hasHeavy) {
                    auto heavyShape = currentShape->down()->down();
                    if (canvas.check_fit(heavyShape.get())) {
                        currentShape = heavyShape;
                    } else {
                        cout << "Cannot move down due to heavy effect!" << endl;
                    }
                }
            } else {
                cout << "Invalid move!" << endl;
            }

        } else if (command == "drop") {
            multiplier = 0;
            canvas.drop(currentShape);
            // Clear lines and calculate score
            int linesCleared = canvas.clearLine();

            // Remove blind effect if present
            if (EffectManager::getInstance().hasEffect(*this, "blind")) {
                EffectManager::getInstance().removeEffect(*this, "blind");
            }

            if(getDifficulty() == 4) {
                if (linesCleared == 0) {
                    if(noClears == 5) {
                        // spawn in a block in the middle of the canvas!!!!!!!!!
                        noClears = 0;
                    }
                } else {
                    noClears++;
                }
            }

            if(linesCleared > 0) {
                addScore(((linesCleared + getDifficulty()) * (linesCleared + getDifficulty())));
            }

            // Check for special actions
            if (linesCleared >= 2) {
                string effectChoice;
                cout << "Choose an effect to apply to your opponent (blind/heavy/force [shape]): ";
                cin >> effectChoice;

                if (effectChoice == "blind") {
                    EffectManager::getInstance().addEffect(opponent, std::make_shared<BlindEffect>());
                } else if (effectChoice == "heavy") {
                    EffectManager::getInstance().addEffect(opponent, std::make_shared<HeavyEffect>());
                } else if (effectChoice.substr(0, 5) == "force") {
                    
                    string shapeType;
                    cin >> shapeType;
                    if (std::string("IJLOSTZ").find(shapeType) != std::string::npos) {
                        EffectManager::getInstance().addEffect(opponent, std::make_shared<ForceEffect>(shapeType));
                    }
                }
            }
            // Get next shape
            queue.findNext(level.get());
            currentShape = queue.getCurrent();

            return true; // Turn ends after drop

        } else if (command == "levelup") {
            multiplier = 0;
            levelUp();
            cout << "Your level is now " << getDifficulty() << "." << endl;
        } else if (command == "leveldown") {
            multiplier = 0;
            levelDown();
            cout << "Your level is now " << getDifficulty() << "." << endl;
        } else if (command == "sequence") {
            if (getDifficulty() == 1 || getDifficulty() == 2) {
                cout << "You are not the correct level to change the sequence file";
                continue;
            }
            //******** */
            try {
                std::string filename;
                cin >> filename;

                // Check if the input is empty
                if (filename.empty()) {
                    throw std::runtime_error("Invalid input. File name cannot be empty.");
                }

                // Try to open the file
                std::ifstream file(filename);
                if (!file) {
                    throw std::runtime_error("This file does not exist, try again.");
                }


            } catch (const std::runtime_error &e) {
                std::cerr << e.what() << std::endl;
            }

        } else if (command == "random") {
            if (getDifficulty() == 3 || getDifficulty() == 4) {
                level->setRng(true);
            } else {
                cout << "You are in the wrong difficulty to be changing to random!" << endl;
                
            }
        } else {
            cout << "Unknown command!" << endl;
        }
    }

    return false; // Turn continues
}

void Player::reset(std::shared_ptr<Level> newLevel) {
    score = 0;
    level = std::move(newLevel);
    currentShape = queue.getCurrent();
    for (int i = 0; i < canvas.getHeight(); ++i) {
        for (int j = 0; j < canvas.getWidth(); ++j) {
            canvas.setState(i, j, ' ');
        }
    }
    canvas.notifyObservers();
}

bool Player::gameOver() const {

    // gameover did not fix
    if (!canvas.check_fit(currentShape.get())) {
        return true;
    }
    return false;
}

Player::~Player() {
    // Automatic cleanup for unique_ptr
}
