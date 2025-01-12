#include "graphicsobserver.h"
#include "canvas.h"
#include "queue.h"
#include "effect.h"
#include "shape.h"
#include <vector>

GraphicObserver::GraphicObserver(Player* p1, Player* p2, int width, int height)
    : player1{p1}, player2{p2}, 
      window{(width + 1) * 10 * 2 + 30, (height + 1) * 10 + 100},
      previousCanvas1(height, std::vector<char>(width, ' ')), // Initialize previous canvases
      previousCanvas2(height, std::vector<char>(width, ' ')) {

    player1->getCanvas().attach(this);
    player2->getCanvas().attach(this);

    drawBorders(); // Draw borders once during initialization
    notify();      // Initial rendering of the board
}

void GraphicObserver::drawBorders() {
    const int blockSize = 10; // Multiplier for size
    const int offsetX = (player1->getCanvas().getWidth() + 2) * blockSize; // Offset for Player 2 board
    const int textHeight = 50; // Space reserved for text above the board

    // Helper to draw borders for a player
    auto drawBorder = [&](int xOffset, int yOffset) {
        for (int i = 0; i <= player1->getCanvas().getHeight(); ++i) {
            int x1 = xOffset;
            int x2 = xOffset + player1->getCanvas().getWidth() * blockSize + blockSize; // Adjusted for right border
            int y = yOffset + i * blockSize;
            window.fillRectangle(x1, y, blockSize, blockSize, Xwindow::Black); // Left border
            window.fillRectangle(x2, y, blockSize, blockSize, Xwindow::Black); // Right border
        }
        int top = yOffset, bottom = yOffset + player1->getCanvas().getHeight() * blockSize;
        window.fillRectangle(xOffset, top, player1->getCanvas().getWidth() * blockSize + blockSize, blockSize, Xwindow::Black); // Top border
        window.fillRectangle(xOffset, bottom, player1->getCanvas().getWidth() * blockSize + blockSize, blockSize, Xwindow::Black); // Bottom border
    };

    const int borderYOffset = textHeight; // Start borders below the text area
    drawBorder(0, borderYOffset);           // Player 1's border
    drawBorder(offsetX, borderYOffset);     // Player 2's border
}

void GraphicObserver::notify() {
    const int blockSize = 10; // Multiplier for size
    const int offsetX = (player1->getCanvas().getWidth() + 2) * blockSize; // Offset for Player 2 board
    const int textHeight = 50; // Space reserved for text above the board
    const int borderYOffset = textHeight; // Ensure the border starts below the text area

    // Clear the text area
    window.fillRectangle(0, 0, window.getWidth(), textHeight, Xwindow::White);

    // Draw Scores and Levels
    int textYOffset = 20; // Vertical position for the first line of text
    int textStep = 20;    // Line spacing for subsequent lines
    window.drawString(10, textYOffset, "Level: " + std::to_string(player1->getDifficulty()));
    window.drawString(offsetX + 10, textYOffset, "Level: " + std::to_string(player2->getDifficulty()));

    textYOffset += textStep;
    window.drawString(10, textYOffset, "Score: " + std::to_string(player1->getScore()));
    window.drawString(offsetX + 10, textYOffset, "Score: " + std::to_string(player2->getScore()));

    // Clear the canvas area inside the borders
    auto clearCanvas = [&](int xOffset, int yOffset) {
        int canvasWidth = player1->getCanvas().getWidth() * blockSize;
        int canvasHeight = player1->getCanvas().getHeight() * blockSize;

        // Reduce the height by one block size to avoid clearing the bottom border
        window.fillRectangle(xOffset + blockSize, yOffset + blockSize, canvasWidth, canvasHeight - blockSize, Xwindow::White);
    };

    clearCanvas(0, borderYOffset);           // Player 1's canvas area
    clearCanvas(offsetX, borderYOffset);     // Player 2's canvas area

    // Draw Canvas for Player 1 and Player 2
    auto drawCanvas = [&](Player *player, std::vector<std::vector<char>> &prevCanvas, int xOffset, int yOffset) {
        for (int i = 0; i < player->getCanvas().getHeight(); ++i) {
            for (int j = 0; j < player->getCanvas().getWidth(); ++j) {
                char currentChar = player->getCanvas().getState(i, j);
                char previousChar = prevCanvas[i][j];

                // Draw only if changed
                if (currentChar != previousChar) {
                    int x = j * blockSize + xOffset + blockSize; // Offset to move blocks inside the board
                    int y = i * blockSize + yOffset;

                    // Erase old block (draw white)
                    if (previousChar != ' ') {
                        window.fillRectangle(x, y, blockSize, blockSize, Xwindow::White);
                    }

                    // Draw new block
                    if (currentChar != ' ') {
                        static std::unordered_map<char, int> colorMap = {
                            {'I', Xwindow::Aqua},   {'O', Xwindow::Yellow},
                            {'T', Xwindow::Purple}, {'S', Xwindow::Green},
                            {'Z', Xwindow::Red},    {'J', Xwindow::Blue},
                            {'L', Xwindow::Orange}, {'?', Xwindow::Gray}};
                        int color = colorMap.count(currentChar) ? colorMap[currentChar] : Xwindow::Black;
                        window.fillRectangle(x, y, blockSize, blockSize, color);
                    }

                    // Update previous canvas
                    prevCanvas[i][j] = currentChar;
                }
            }
        }
    };

    drawCanvas(player1, previousCanvas1, 0, borderYOffset);          // Player 1's canvas
    drawCanvas(player2, previousCanvas2, offsetX, borderYOffset);    // Player 2's canvas

    // Draw Current Shape for Player 1 and Player 2
    auto drawCurrentShape = [&](Player *player, int xOffset, int yOffset) {
        Shape *currentShape = player->getCurrentShape().get();
        for (const auto &block : currentShape->getBlocks()) {
            int x = block.getX() * blockSize + xOffset + blockSize; // Offset to move blocks inside the board
            int y = block.getY() * blockSize + yOffset;
            window.fillRectangle(x, y, blockSize, blockSize, Xwindow::Green); // Current shape in green
        }
    };

    drawCurrentShape(player1, 0, borderYOffset);
    drawCurrentShape(player2, offsetX, borderYOffset);

    // Draw Next Shape
    auto drawNextShape = [&](Player *player, int xOffset, int yOffset) {
        Shape *nextShape = player->getQueue().getNext();
        if (nextShape) {
            for (const auto &block : nextShape->getBlocks()) {
                int x = (block.getX() + 1) * blockSize + xOffset + blockSize; // Offset for "Next" position
                int y = (block.getY() + player1->getCanvas().getHeight() + 2) * blockSize + yOffset;
                window.fillRectangle(x, y, blockSize, blockSize, Xwindow::Blue); // Next shape in blue
            }
        }
    };

    drawNextShape(player1, 0, borderYOffset + player1->getCanvas().getHeight() * blockSize + 10); // Below Player 1 board
    drawNextShape(player2, offsetX, borderYOffset + player2->getCanvas().getHeight() * blockSize + 10); // Below Player 2 board
}



GraphicObserver::~GraphicObserver() {
    player1->getCanvas().detach(this);
    player2->getCanvas().detach(this);
}
