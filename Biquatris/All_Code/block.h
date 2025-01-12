#ifndef BLOCK_h
#define BLOCK_h

class Block {
    int x, y; // coordinated on the grind
    /*int lifespan; // counts how long the block has until it is deleted*/
    char c; // the coresponding char that is printed
    public:
        Block(int x, int y, char c/*, int life*/);

        int getX() const;
        int getY() const;

        void setX(int n);
        void setY(int n);

        /*int getLife() const;
        bool isDead(int turn) const; // checks if lifespan == 10*/

        char getC() const;
        void setC(char other); // used for force
        bool isEmpty() const; // determines if c == ' '
};
#endif
