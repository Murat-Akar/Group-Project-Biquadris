#include "block.h"
#include "shape.h"
#include <vector>
#include <memory>

using namespace std;

// the third rowfrom the top, bottom parts of shapes will start at 2 and build upwards towards the top of the screen
// Each shape will work in a "3x3" grid

Shape::Shape(char letter) : letter{letter}, rotationState(1) {}

Shape::Shape(const Shape& other)
    : letter(other.letter),
      rotationState(other.rotationState),
      blocks(other.blocks) {}
      
std::vector<Block> Shape::getBlocks() const {
    return blocks;
}

char Shape::getLetter() const {
    return letter;
}

// move shape left
std::shared_ptr<Shape> Shape::left() {
    auto newShape = this->clone();
    //std::make_shared<Shape>(*this);
    for(auto & block: newShape->blocks) {
        block.setX(block.getX() - 1);
        
    }
    return newShape;
}

// move shape right
std::shared_ptr<Shape> Shape::right() {
    // making a new shape
    auto newShape = this->clone();
    // std::make_shared<Shape>(*this);

    // looping through the vector and adding 1 to move right
    for(auto & block: newShape->blocks) {
        block.setX(block.getX() + 1);
    }
    
    return newShape;
}

// Move shape down
std::shared_ptr<Shape> Shape::down() {
    auto newShape = this->clone();
    //std::make_shared<Shape>(*this);
    for(auto & block: newShape->blocks) {
        block.setY(block.getY() + 1);
    }
    return newShape;
}

// ctor
L::L(int startX, int startY): Shape('L') {
    // this is de default L rotation state

    Block head = {startX - 1, startY, letter};
    // 
    // L

    Block c2 = {startX, startY, letter};
    //
    // LL

    Block c3 = {startX + 1, startY, letter};
    // 
    // LLL

    Block c4 = {startX + 1, startY - 1, letter};
    //   L
    // LLL
    blocks.emplace_back(head);
    blocks.emplace_back(c2);
    blocks.emplace_back(c3);
    blocks.emplace_back(c4);
}

// L copy ctor
L::L(const L&other) : Shape(other) {}

// L clockwise
std::shared_ptr<Shape> L::clockwise() {
    // axis of rotation does not change!

    int x = blocks.front().getX(); // get the x-axis of the axis
    int y = blocks.front().getY(); // get the y-axis of the axis

    L newShape(*this);
    
    // do not change
    int defaultRotation = 1;
    //   *
    // ***

    int rotation2 = 2;
    // *
    // *
    // **

    int rotation3 = 3;
    // ***
    // *

    int rotation4 = 4;
    // **
    //  *
    //  *

    if(newShape.rotationState == defaultRotation) { // default -> rotation2
        newShape.rotationState = rotation2;
        // do the math to properly rotate in in the cartiasian cordinates
        //NOTE: THE AXIS DOES NOT CHANGE FOR L!
        newShape.blocks[1].setX(x + 1);
        newShape.blocks[1].setY(y + 0);
        // LL

        newShape.blocks[2].setX(x + 0);
        newShape.blocks[2].setY(y - 1);
        // L
        // LL

        newShape.blocks[3].setX(x + 0);
        newShape.blocks[3].setY(y - 2);
        // L
        // L
        // LL

    } else if (newShape.rotationState == rotation2) { // rotation2 -> rotation3
        newShape.rotationState = rotation3;
        // NOTE: THE AXIS DOES NOT CHANGE FOR L
        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);
        // L
        // L

        newShape.blocks[2].setX(x + 1);
        newShape.blocks[2].setY(y - 1);
        // LL
        // L

        newShape.blocks[3].setX(x + 2);
        newShape.blocks[3].setY(y - 1);
        // LLL
        // L
    } else if (newShape.rotationState == rotation3) { // rotation3 -> rotation4
        newShape.rotationState = rotation4;
        // NOTE: THE HEAD WILL SHIFT OVER BY X + 1
        x += 1;
        newShape.blocks[0].setX(x);
        // y does not change
        //
        //
        //  L

        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);
        //
        //  L
        //  L

        newShape.blocks[2].setX(x + 0);
        newShape.blocks[2].setY(y - 2);
        //  L
        //  L
        //  L

        newShape.blocks[3].setX(x - 1);
        newShape.blocks[3].setY(y - 2);
        // LL
        //  L
        //  L

    } else if (newShape.rotationState == rotation4) { // rotation 4 -> defaultRotation
        newShape.rotationState = defaultRotation;
        // NOTE: THE HEAD MUST CHANGE BACK
        x -= 1;
        newShape.blocks[0].setX(x);
        //
        // L

        newShape.blocks[1].setX(x + 1);
        newShape.blocks[1].setY(y + 0);

        newShape.blocks[2].setX(x + 2);
        newShape.blocks[2].setY(y + 0);

        newShape.blocks[3].setX(x + 2);
        newShape.blocks[3].setY(y - 1);

    }
    return std::make_shared<L>(newShape);
}

// L counter-clockwise
std::shared_ptr<Shape> L::counter() {
    // axis of rotation does not change!

    int x = blocks.front().getX(); // get the x-axis of the axis
    int y = blocks.front().getY(); // get the y-axis of the axis

    L newShape(*this);
    
    // do not change
    int defaultRotation = 1;
    //   *
    // ***

    int rotation2 = 2;
    // *
    // *
    // **

    int rotation3 = 3;
    // ***
    // *

    int rotation4 = 4;
    // **
    //  *
    //  *

    if(newShape.rotationState == defaultRotation) { // default -> rotation4
        newShape.rotationState = rotation4;
        //             LL
        //   L ----->   L
        // LLL          L
        x += 1;
        newShape.blocks[0].setX(x);

        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);
        // LL

        newShape.blocks[2].setX(x + 0);
        newShape.blocks[2].setY(y - 2);

        newShape.blocks[3].setX(x - 1);
        newShape.blocks[3].setY(y - 2);

    } else if (newShape.rotationState == rotation2) { // rotation2 -> default
        newShape.rotationState = defaultRotation;
        // NOTE: THE AXIS DOES NOT CHANGE FOR L
        // L
        // L  -------->    L
        // LL            LLL
        newShape.blocks[1].setX(x + 1);
        newShape.blocks[1].setY(y + 0);

        newShape.blocks[2].setX(x + 2);
        newShape.blocks[2].setY(y + 0);

        newShape.blocks[3].setX(x + 2);
        newShape.blocks[3].setY(y - 1);
    } else if (newShape.rotationState == rotation3) { // rotation3 -> rotation2
        newShape.rotationState = rotation2;
        //                    L
        // LLL  ------------> L
        // L                  LL

        newShape.blocks[1].setX(x + 1);
        newShape.blocks[1].setY(y + 0);

        newShape.blocks[2].setX(x + 0);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 0);
        newShape.blocks[3].setY(y - 2);

    } else if (newShape.rotationState == rotation4) { // rotation4 -> rotation3
        newShape.rotationState = rotation3;
        // LL
        //  L --------> LLL
        //  L           L

        x -= 1;
        newShape.blocks[0].setX(x);

        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);

        newShape.blocks[2].setX(x + 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 2);
        newShape.blocks[3].setY(y - 1);
    }

    return std::make_shared<L>(newShape);
}

// J ctor
J::J(int startX, int startY): Shape('J') {
    // default rotation state for J
    // J
    // JJJ

    Block head = {startX - 1, startY, letter};
    //
    // J

    Block c2 = {startX - 1, startY - 1, letter};
    // J
    // J

    Block c3 = {startX, startY, letter};
    // J
    // JJ

    Block c4 = {startX + 1, startY, letter};
    // J
    // JJJ

    blocks.emplace_back(head);
    blocks.emplace_back(c2);
    blocks.emplace_back(c3);
    blocks.emplace_back(c4);
}

// J copy ctor
J::J(const J&other) : Shape(other) {}

// J clockwise
std::shared_ptr<Shape> J::clockwise() {
    // axis of rotation does not change!

    int x = blocks.front().getX(); // get the x-axis of the axis
    int y = blocks.front().getY(); // get the y-axis of the axis

    J newShape(*this);
    
    // do not change
    int defaultRotation = 1;
    // *
    // ***

    int rotation2 = 2;
    // **
    // *
    // *

    int rotation3 = 3;
    // ***
    //   *

    int rotation4 = 4;
    //  *
    //  *
    // **

    if(newShape.rotationState == defaultRotation) { // default -> rotation2
        newShape.rotationState = rotation2;
        //            JJ
        // J   -----> J
        // JJJ        J
        
        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);

        newShape.blocks[2].setX(x + 0);
        newShape.blocks[2].setY(y - 2);

        newShape.blocks[3].setX(x + 1);
        newShape.blocks[3].setY(y - 2);

    } else if (newShape.rotationState == rotation2) { // rotation2 -> rotation3
        newShape.rotationState = rotation3;
        // JJ
        // J  ------> JJJ
        // J            J

        // NEED TO MOVE THE HAD TO THE RIGHT
        x += 2;
        newShape.blocks[0].setX(x);

        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);

        newShape.blocks[2].setX(x - 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setY(x - 2);
        newShape.blocks[3].setY(y - 1);
        
    } else if (newShape.rotationState == rotation3) { // rotation3 -> rotation4
        newShape.rotationState = rotation4;
        //               J
        // JJJ ------->  J
        //   J          JJ

        // need to move the head to the lower left
        x -= 2;
        newShape.blocks[0].setX(x);

        newShape.blocks[1].setX(x + 1);
        newShape.blocks[1].setY(y + 0);

        newShape.blocks[2].setX(x + 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 1);
        newShape.blocks[3].setY(y - 2);

    } else if (newShape.rotationState == rotation4) { // rotation 4 -> defaultRotation
        newShape.rotationState = defaultRotation;
        //  J
        //  J  -------->  J
        // JJ             JJJ

        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);

        newShape.blocks[2].setX(x + 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 2);
        newShape.blocks[3].setY(y - 1);

    }
    return std::make_shared<J>(newShape);
}

// J counter-clockwise
std::shared_ptr<Shape> J::counter() {
    // axis of rotation does not change!

    int x = blocks.front().getX(); // get the x-axis of the axis
    int y = blocks.front().getY(); // get the y-axis of the axis

    J newShape(*this);
    
    // do not change
    int defaultRotation = 1;
    // *
    // ***

    int rotation2 = 2;
    // **
    // *
    // *

    int rotation3 = 3;
    // ***
    //   *

    int rotation4 = 4;
    //  *
    //  *
    // **

    if(newShape.rotationState == defaultRotation) { // default -> rotation4
        newShape.rotationState = rotation4;
        //             J
        // J   ----->  J
        // JJJ        JJ
        
        newShape.blocks[1].setX(x + 1);
        newShape.blocks[1].setY(y + 0);

        newShape.blocks[2].setX(x + 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 1);
        newShape.blocks[3].setY(y - 2);

    } else if (newShape.rotationState == rotation2) { // rotation2 -> default
        newShape.rotationState = defaultRotation;
        // JJ
        // J  ------> J
        // J          JJJ

        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);

        newShape.blocks[2].setX(x + 1);
        newShape.blocks[2].setY(y + 0);

        newShape.blocks[3].setY(x + 2);
        newShape.blocks[3].setY(y + 0);
        
    } else if (newShape.rotationState == rotation3) { // rotation3 -> rotation2
        newShape.rotationState = rotation2;
        //              JJ
        // JJJ -------> J
        //   J          J

        // need to move the head to the lower left
        x -= 2;
        newShape.blocks[0].setX(x);

        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);

        newShape.blocks[2].setX(x + 0);
        newShape.blocks[2].setY(y - 2);

        newShape.blocks[3].setX(x + 1);
        newShape.blocks[3].setY(y - 2);

    } else if (newShape.rotationState == rotation4) { // rotation 4 -> rotation3
        newShape.rotationState = rotation3;
        // xJ
        // xJ  -------->  JJJ
        // JJ             xxJ

        x += 2;
        newShape.blocks[0].setX(x);

        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);

        newShape.blocks[2].setX(x - 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x - 2);
        newShape.blocks[3].setY(y - 1);

    }
    return std::make_shared<J>(newShape);
}

// I ctor
I::I(int startX, int startY): Shape('I') {
    // IIII
    
    Block head = {startX - 1, startY, letter};
    Block c2 = {startX , startY, letter};
    Block c3 = {startX + 1, startY, letter};
    Block c4 = {startX + 2, startY, letter};

    blocks.emplace_back(head);
    blocks.emplace_back(c2);
    blocks.emplace_back(c3);
    blocks.emplace_back(c4);
}

// I copy ctor
I::I(const I&other) : Shape(other) {}

// I clockwise
std::shared_ptr<Shape> I::clockwise() {
    int x = blocks.front().getX(); // get the x-axis of the axis
    int y = blocks.front().getY(); // get the y-axis of the axis

    I newShape(*this);

    int defaultRotation = 1;
    int rotation2 = 2;

    if(newShape.rotationState == defaultRotation) { // default Rotation -> rotation 2
        newShape.rotationState = rotation2;
        // Head will not change!
        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);

        newShape.blocks[2].setX(x + 0);
        newShape.blocks[2].setY(y - 2);

        newShape.blocks[3].setX(x + 0);
        newShape.blocks[3].setY(y - 3);

    } else if (newShape.rotationState == rotation2) { // rotation2 ->default
        newShape.rotationState = defaultRotation;
        
        // Head will not change!
        newShape.blocks[1].setX(x + 1);
        newShape.blocks[1].setY(y + 0);

        newShape.blocks[2].setX(x + 2);
        newShape.blocks[2].setY(y + 0);

        newShape.blocks[3].setX(x + 3);
        newShape.blocks[3].setY(y + 0);
    }
    return std::make_shared<I>(newShape);
}

// I counter-clockwise
std::shared_ptr<Shape> I::counter() {
    // since there are only 2 functions, repeat the steps for counter!
    return clockwise();
}

// O ctor
O::O(int startX, int startY): Shape('O') {
    // OO
    // OO
    Block head = {startX - 1, startY, letter};

    Block c2 = {startX, startY, letter};
    Block c3 = {startX - 1, startY - 1, letter};
    Block c4 = {startX, startY - 1, letter};

    blocks.emplace_back(head);
    blocks.emplace_back(c2);
    blocks.emplace_back(c3);
    blocks.emplace_back(c4);
}

// O copy ctor
O::O(const O&other) : Shape(other) {}

// O clockwise 
std::shared_ptr<Shape> O::clockwise() {
    O newShape(*this);
    return std::make_shared<O>(newShape);
}

// O counter-clockwise 
std::shared_ptr<Shape> O::counter() {
    O newShape(*this);
    return std::make_shared<O>(newShape);
}

// Z ctor
Z::Z(int startX, int startY): Shape('Z') {
    // ZZ
    //  ZZ

    Block head = {startX, startY, letter};
    //
    //  Z

    Block c2 = {startX + 1, startY, letter};
    //
    //  ZZ

    Block c3 = {startX, startY - 1, letter};
    //  Z
    //  ZZ

    Block c4 = {startX - 1, startY - 1, letter};
    // ZZ
    //  ZZ
    blocks.emplace_back(head);
    blocks.emplace_back(c2);
    blocks.emplace_back(c3);
    blocks.emplace_back(c4);
}

// Z copy ctor
Z::Z(const Z&other) : Shape(other) {}

// Z clockwise
std::shared_ptr<Shape> Z::clockwise() {
    int x = blocks.front().getX(); // get the x-axis of the axis
    int y = blocks.front().getY(); // get the y-axis of the axis

    Z newShape(*this);

    int defaultRotation = 1;
    // ZZ
    //  ZZ

    int rotation2 = 2;
    //  Z
    // ZZ
    // Z
    
    if(newShape.rotationState == defaultRotation) { // default -> rotation2
        // head needs to move
        newShape.rotationState = rotation2;
        x -= 1;
        newShape.blocks[0].setX(x);

        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);

        newShape.blocks[2].setX(x + 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 1);
        newShape.blocks[3].setY(y - 2);
    } else if (newShape.rotationState == rotation2) { // rotation2 -> default
        newShape.rotationState = defaultRotation;
        x += 1;
        newShape.blocks[0].setX(x);

        newShape.blocks[1].setX(x + 1);
        newShape.blocks[1].setY(y + 0);

        newShape.blocks[2].setX(x + 0);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x - 1);
        newShape.blocks[3].setY(y - 1);
    }
    return std::make_shared<Z>(newShape);
}

// Z counter-clockwise
std::shared_ptr<Shape> Z::counter() {
    return clockwise();
}

// S ctor
S::S(int startX, int startY): Shape('S') {
    //  SS
    // SS

    Block head = {startX - 1, startY, letter};
    //
    // S

    Block c2 = {startX, startY, letter};
    //
    // SS

    Block c3 = {startX, startY - 1, letter};
    //  S
    // SS

    Block c4 = {startX + 1, startY - 1, letter};
    //  SS
    // SS
    blocks.emplace_back(head);
    blocks.emplace_back(c2);
    blocks.emplace_back(c3);
    blocks.emplace_back(c4);
}

// S copy ctor
S::S(const S &other) : Shape(other) {}

// S clockwise
std::shared_ptr<Shape> S::clockwise() {
    int x = blocks.front().getX(); // get the x-axis of the axis
    int y = blocks.front().getY(); // get the y-axis of the axis

    S newShape(*this);

    int defaultRotation = 1;
    //  SS
    // SS

    int rotation2 = 2;
    // S
    // SS
    //  S

    if(newShape.rotationState == defaultRotation) {  // default -> rotation2
        newShape.rotationState = rotation2;
        //             S
        //  SS ----->  SS
        // SS           S

        x += 1;
        newShape.blocks[0].setX(x);

        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);
        
        newShape.blocks[2].setX(x - 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x - 1);
        newShape.blocks[3].setY(y - 2);
    } else if (newShape.rotationState == rotation2) { // rotation2 ->default
        newShape.rotationState = defaultRotation;
        // S
        // SS ------->  SS
        //  S          SS

        x -= 1;
        newShape.blocks[0].setX(x);

        newShape.blocks[1].setX(x + 1);
        newShape.blocks[1].setY(y + 0);

        newShape.blocks[2].setX(x + 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 2);
        newShape.blocks[3].setY(y - 1);
    }
    return std::make_shared<S>(newShape);
}

// S counter-clockwise
std::shared_ptr<Shape> S::counter() {
    return clockwise();
}

// T ctor
T::T(int startX, int startY): Shape('T') {
    //  T 
    // TTT

    Block head = {startX - 1, startY, letter};
    //
    // T

    Block c2 = {startX, startY, letter};
    //
    // TT

    Block c3 = {startX, startY - 1, letter};
    //  T
    // TT

    Block c4 = {startX + 1, startY, letter};
    blocks.emplace_back(head);
    blocks.emplace_back(c2);
    blocks.emplace_back(c3);
    blocks.emplace_back(c4);
}

// T copy ctor
T::T(const T &other) : Shape(other) {}

// T clockwise
std::shared_ptr<Shape> T::clockwise() {
    int x = blocks.front().getX(); // get the x-axis of the axis
    int y = blocks.front().getY(); // get the y-axis of the axis

    T newShape(*this);

    int defaultRotation = 1;
    //
    //  T
    // TTT

    int rotation2 = 2;
    // T
    // TT
    // T

    int rotation3 = 3;
    //
    // TTT
    //  T

    int rotation4 = 4;
    //  T
    // TT
    //  T

    if(newShape.rotationState == defaultRotation) { // default -> rotation2
        newShape.rotationState = rotation2;
        //            T
        //  T  -----> TT
        // TTT        T

        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);

        newShape.blocks[2].setX(x + 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 0);
        newShape.blocks[3].setY(y - 2);
    } else if (newShape.rotationState == rotation2) { // rotation2 -> rotation3
        newShape.rotationState = rotation3;
        // T
        // TT -----> TTT
        // T          T
        x += 1;
        newShape.blocks[0].setX(x);

        newShape.blocks[1].setX(x - 1);
        newShape.blocks[1].setY(y - 1);

        newShape.blocks[2].setX(x + 0);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 1);
        newShape.blocks[3].setY(y - 1);
    } else if (newShape.rotationState == rotation3) { // rotation3 -> rotation4
        newShape.rotationState = rotation4;
        //                T
        // TTT  -------> TT
        //  T             T

        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);

        newShape.blocks[2].setX(x - 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 0);
        newShape.blocks[3].setX(y - 2);
    } else if (newShape.rotationState == rotation4) { //rotate4 -> defaultRotation
        newShape.rotationState = defaultRotation;
        //  T
        // TT ------>  T
        //  T         TTT
        x -= 1;
        newShape.blocks[0].setX(x);

        newShape.blocks[1].setX(x + 1);
        newShape.blocks[1].setY(y + 0);

        newShape.blocks[2].setX(x + 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 2);
        newShape.blocks[2].setY(y + 0);
    }
    return std::make_shared<T>(newShape);
}

// T counter-clockwise
std::shared_ptr<Shape> T::counter() {
    int x = blocks.front().getX(); // get the x-axis of the axis
    int y = blocks.front().getY(); // get the y-axis of the axis

    T newShape(*this);

    int defaultRotation = 1;
    //
    //  T
    // TTT

    int rotation2 = 2;
    // T
    // TT
    // T

    int rotation3 = 3;
    //
    // TTT
    //  T

    int rotation4 = 4;
    //  T
    // TT
    //  T

    if(newShape.rotationState == defaultRotation) { // default -> rotation4
        newShape.rotationState = rotation4;
        //             T
        //  T  -----> TT
        // TTT         T
        x += 1;
        newShape.blocks[0].setX(x);

        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);

        newShape.blocks[2].setX(x - 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 0);
        newShape.blocks[3].setY(y - 2);
    } else if (newShape.rotationState == rotation2) { // rotation2 -> default
        // T
        // TT ----->  T
        // T         TTT
        newShape.rotationState = defaultRotation;

        newShape.blocks[1].setX(x + 1);
        newShape.blocks[1].setY(y + 0);

        newShape.blocks[2].setX(x + 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 0);
        newShape.blocks[3].setY(y + 2);
        
    } else if (newShape.rotationState == rotation3) { // rotation3 -> rotation2
        newShape.rotationState = rotation2;
        //               T
        // TTT  -------> TT
        //  T            T
        x -= 1;
        
        newShape.blocks[0].setX(x);

        newShape.blocks[1].setX(x + 0);
        newShape.blocks[1].setY(y - 1);
        
        newShape.blocks[2].setX(x + 1);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 0);
        newShape.blocks[3].setY(y - 2);
    } else if (newShape.rotationState == rotation4) { // rotation4 -> rotation3
        newShape.rotationState = rotation3;
        //  T
        // TT --------> TTT
        //  T            T

        newShape.blocks[1].setX(x - 1);
        newShape.blocks[1].setY(y - 1);
        
        newShape.blocks[2].setX(x + 0);
        newShape.blocks[2].setY(y - 1);

        newShape.blocks[3].setX(x + 1);
        newShape.blocks[3].setY(y - 1);
    }
    return std::make_shared<T>(newShape);
}

std::shared_ptr<Shape> L:: clone() const {
    return std::make_shared<L>(*this);
}

std::shared_ptr<Shape> J:: clone() const {
    return std::make_shared<J>(*this);
}

std::shared_ptr<Shape> I:: clone() const {
    return std::make_shared<I>(*this);
}

std::shared_ptr<Shape> O:: clone() const {
    return std::make_shared<O>(*this);
}

std::shared_ptr<Shape> S:: clone() const {
    return std::make_shared<S>(*this);
}

std::shared_ptr<Shape> Z:: clone() const {
    return std::make_shared<Z>(*this);
}

std::shared_ptr<Shape> T:: clone() const {
    return std::make_shared<T>(*this);
}
