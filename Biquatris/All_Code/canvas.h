#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <memory>
#include "subject.h"
#include "shape.h"
#include "block.h"

class Canvas : public Subject {
    std::vector<std::vector<char>> canvas;
    int width;
    int height;

  public:
    Canvas(int width, int height);
    char getState(int row, int col) const;
    void setState(int row, int col, char c);
    int getHeight() const;
    int getWidth() const;
    bool check_fit(Shape *shape) const;
    void drop(std::shared_ptr<Shape> shape);
    int clearLine();
    void display() const;
    ~Canvas() = default;
};

#endif
