#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "queue.h"
#include "canvas.h"
#include "level.h"
#include "shape.h"

class Player {
  protected:
    int playerID;
    int score;
    std::shared_ptr<Level> level;
    Queue& queue; // Pointer to Queue
    Canvas& canvas; // Reference to Canvas
    std::shared_ptr<Shape> currentShape;
    
    int noClears; // relevant only for level 4

  public:
    Player(int playerID, int score, std::shared_ptr<Level> level, Queue& queue, Canvas& canvas, std::shared_ptr<Shape> currentShape);

    void levelUp();
    void levelDown();
    void addScore(int points);

    int getScore() const;
    Level* getLevel() const;
    int getDifficulty() const;
    int getPlayerID() const; // New method
    Canvas& getCanvas() const;
    Queue& getQueue() const;

    std::shared_ptr<Shape> getCurrentShape() const; // New method
    void setCurrentShape(std::shared_ptr<Shape> shape); // New method

    bool takeTurn(Player& opponent); // Modified to accept opponent reference
    void reset(std::shared_ptr<Level> newLevel);

    bool gameOver() const;
    ~Player();
};

#endif
