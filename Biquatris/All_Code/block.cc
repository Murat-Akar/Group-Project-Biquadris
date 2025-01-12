#include "block.h"

Block::Block(int x, int y, char c/*, int life*/): x{x}, y{y}, c{c}/*, lifespan{life}*/ {}

int Block::getX() const {
    return x;
}
int Block::getY() const {
    return y;
}

void Block::setX(int n) {
    x = n;
    return;
}
void Block::setY(int n) {
    y = n;
    return;
}
/*bool Block::isDead(int turn) const {
    int deadIn = 10; // turns
    if (lifespan + deadIn == turn) {
        return true;
    }
    return false;
}

int Block::getLife() const {
    return lifespan;
}*/

char Block::getC() const {
    return c;
}
void Block::setC(char other) {
    c = other;
}

bool Block::isEmpty() const {
    if (c == ' ') {
        return true;
    }
    return false;
}
