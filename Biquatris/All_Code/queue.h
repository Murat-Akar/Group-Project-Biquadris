#ifndef QUEUE_H
#define QUEUE_H

#include <memory>
#include "level.h"
#include "shape.h"

class Queue {
    std::shared_ptr<Shape> current;
    std::shared_ptr<Shape> next;

public:
    explicit Queue(Level* lv);
    std::shared_ptr<Shape> getCurrent(); 
    Shape* getNext();
    void setCurrent(std::shared_ptr<Shape> newCurrent);

    void findNext(Level* lv);
};

#endif

