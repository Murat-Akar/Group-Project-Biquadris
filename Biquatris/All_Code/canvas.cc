#include <iostream>
#include <vector>
#include "subject.h"
#include "shape.h"
#include "block.h"
#include "canvas.h"
using namespace std;

// CONCRETE SUBJECT

Canvas::Canvas(int width, int height) : width{width}, height{height} {
    canvas.resize(height);
    for (int i = 0; i < height; i++) {
        canvas[i].resize(width, ' '); 
    }
}

char Canvas::getState(int row, int col) const {
    return canvas[row][col];
}

int Canvas::getHeight() const {
    return height;
}

int Canvas::getWidth() const {
    return width;
}

bool Canvas::check_fit(Shape* shape) const {
    for (const auto& block : shape->getBlocks()) {
        int row = block.getY();
        int col = block.getX();
        // if it is out of bounds
        if (row < 0 || row >= height - 3 || col < 0 || col >= width) {
            return false;
        }
        // if place is occupied
        if (canvas[row][col] != ' ') {
            return false;
        }
    }
    return true;
}

void Canvas::drop(std::shared_ptr<Shape> shape) {

    while (true) {
        std::shared_ptr<Shape> nextShape = shape->down();
        if (check_fit(nextShape.get())) {
            shape = nextShape;
        } else {
            break;
        }
        
    }
    for (const auto& block : shape->getBlocks()) {
            int row = block.getY();
            int col = block.getX();
            canvas[row][col] = shape->getLetter();
        }
    
}

int Canvas::clearLine() {
    int linesCleared = 0;
    for (int i = 0; i < height; i++) {
        bool line_filled = true;

        for (int j = 0; j < width; j++) {
            if (canvas[i][j] == ' ') {
                line_filled = false;
                break;
            }
        }
        if (line_filled) {
            linesCleared++;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < width; j++) {
                    canvas[k][j] = canvas[k - 1][j];
                }
            }
            // Clear the top row
            for (int j = 0; j < width; j++) {
                canvas[0][j] = ' ';
            }
            i--; // Re-check the same row after shifting
        }
    }
    return linesCleared;
}

void Canvas::setState(int row, int col, char c) {
    canvas[row][col] = c;
}

void Canvas::display() const {
    notifyObservers();
    for (int i = 0; i < height; i++) {
        for (int j = 0; i < width; j++) {
            // i = height / row
            // j = col / width
            cout << canvas[i][j];
        }
        cout << endl;
    }
}
