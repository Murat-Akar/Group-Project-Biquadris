#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>
#include "level.h"
#include "shape.h"

// Starting point!
const int x = 1, y = 3;

Level::Level(int difficulty, std::ifstream& stream): difficulty{difficulty}, sequence{stream}, rng{true}  {}

int Level::getDifficulty() const {
    return difficulty;
}

std::ifstream& Level::getSequence() const {
    return sequence;
}

/*void Level::setSequence() {

}*/

void Level::setRng(bool dif) {
    if (difficulty == 3 || difficulty == 4) {
        rng = dif;
    }
}

Level0::Level0(std::ifstream& stream): Level(0, stream) {}

std::shared_ptr<Shape> Level0::genShape() {
    // uses files
    char shapeType;

    // read from file
    sequence >> shapeType;
    
    // Read each character from the file and create the corresponding shape
        std::shared_ptr<Shape> shape;
        if(sequence.eof()) {
            sequence.clear();
            // moves to beginning
            sequence.seekg(0, std::ios::beg);
            sequence >> shapeType;
        }

        // Create the shape based on the character read
        switch (shapeType) {
            case 'S':
                shape = std::make_shared<S>(x, y); // You can adjust x, y, turn as needed
                break;
            case 'Z':
                shape = std::make_shared<Z>(x, y);
                break;
            case 'T':
                shape = std::make_shared<T>(x, y);
                break;
            case 'I':
                shape = std::make_shared<I>(x, y);
                break;
            case 'O':
                shape = std::make_shared<O>(x, y);
                break;
            case 'L':
                shape = std::make_shared<L>(x, y);
                break;
            case 'J':
                shape = std::make_shared<J>(x, y);
                break;
            default:
                std::cerr << "Unknown shape type: " << shapeType << std::endl;
                sequence >> shapeType; // go to next shape
        }
    return shape;  // Return the vector of generated shapes
}

Level1::Level1(std::ifstream& stream): Level(1, stream) {}

std::shared_ptr<Shape> Level1::genShape() {
    int random = 1 + (rand() % 12);

    std::shared_ptr<Shape> shape;

    switch (random) {
        case 1: // 1/12 chance for Z
            shape = std::make_shared<Z>(x, y);
            break;
        case 2: // 1/12 chance for S
            shape = std::make_shared<S>(x, y);
            break;
        case 3: // 2/12 chance for L
            shape = std::make_shared<L>(x, y);
            break;
        case 4:
            shape = std::make_shared<L>(x, y);
            break;
        case 5: // 2/12 chance for J
            shape = std::make_shared<J>(x, y);
            break;
        case 6:
            shape = std::make_shared<J>(x, y);
            break;
        case 7: // 2/12 chance for T
            shape = std::make_shared<T>(x, y);
            break;
        case 8:
            shape = std::make_shared<T>(x, y);
            break;
        case 9: // 2/12 chance for O
            shape = std::make_shared<O>(x, y);
            break;
        case 10:
            shape = std::make_shared<O>(x, y);
            break;
        case 11: // 2/12 chance for I
            shape = std::make_shared<I>(x, y);
            break;
        case 12:
            shape = std::make_shared<I>(x, y);
            break;
        default:
            std::cerr << "Unexpected random number: " << random << std::endl;
            break;
    }

    return shape;
}

Level2::Level2(std::ifstream& stream): Level(2, stream) {}

std::shared_ptr<Shape> Level2::genShape() {
    int random = 1 + (rand() % 7);

    std::shared_ptr<Shape> shape;

    switch (random) {
        case 1: // 1/7 chance for Z
            shape = std::make_shared<Z>(x, y);
            break;
        case 2: // 1/7 chance for S
            shape = std::make_shared<S>(x, y);
            break;
        case 3: // 1/7 chance for L
            shape = std::make_shared<L>(x, y);
            break;
        case 4: // 1/7 chance for J
            shape = std::make_shared<J>(x, y);
            break;;
        case 5: // 1/7 chance for T
            shape = std::make_shared<T>(x, y);
            break;
        case 6: // 1/7 chance for O
            shape = std::make_shared<O>(x, y);
            break;
        case 7: // 1/7 chance for I
            shape = std::make_shared<I>(x, y);
            break;
        default:
            break;
    }

    return shape;
}

Level3::Level3(std::ifstream& stream): Level(3, stream) {}

std::shared_ptr<Shape> Level3::genShape() {
    if (rng == false) {
        return Level3::genShapeFile();
    }

    int random = 1 + (rand() % 9);

    std::shared_ptr<Shape> shape;

    switch (random) {
        case 1: // 1/9 chance for Z
            shape = std::make_shared<Z>(x, y);
            break;
        case 2: // 1/9 chance for S
            shape = std::make_shared<S>(x, y);
            break;
        case 3: // 1/9 chance for L
            shape = std::make_shared<L>(x, y);
            break;
        case 4: // 1/9 chance for J
            shape = std::make_shared<J>(x, y);
            break;;
        case 5: // 1/9 chance for T
            shape = std::make_shared<T>(x, y);
            break;
        case 6: // 1/9 chance for O
            shape = std::make_shared<O>(x, y);
            break;
        case 7: // 1/9 chance for I
            shape = std::make_shared<I>(x, y);
            break;
        case 8: // 2/9 chance for Z
            shape = std::make_shared<Z>(x, y);
            break;
        case 9: // 2/9 chance for S
            shape = std::make_shared<S>(x, y);
            break;
        default:
            random = 1 + (rand() % 7);
    }

    return shape;
}

std::shared_ptr<Shape> Level3::genShapeFile() {
    char shapeType;

    // read from file
    sequence >> shapeType;
    
    // Read each character from the file and create the corresponding shape
        std::shared_ptr<Shape> shape;
        if(sequence.eof()) {
            sequence.clear();
            // moves to beginning
            sequence.seekg(0, std::ios::beg);
            sequence >> shapeType;
        }

    
    
    // Read each character from the file and create the corresponding shape
        
        // Create the shape based on the character read
        switch (shapeType) {
            case 'S':
                shape = std::make_shared<S>(x, y); // You can adjust x, y, turn as needed
                break;
            case 'Z':
                shape = std::make_shared<Z>(x, y);
                break;
            case 'T':
                shape = std::make_shared<T>(x, y);
                break;
            case 'I':
                shape = std::make_shared<I>(x, y);
                break;
            case 'O':
                shape = std::make_shared<O>(x, y);
                break;
            case 'L':
                shape = std::make_shared<L>(x, y);
                break;
            case 'J':
                shape = std::make_shared<J>(x, y);
                break;
            default:
                sequence >> shapeType; // go to next shape
        }
    return shape;  // Return the vector of generated shapes
}

Level4::Level4(std::ifstream& stream): Level(4, stream) {}

std::shared_ptr<Shape> Level4::genShape() {
    if (rng == false) {
        return this->genShapeFile();
    }
    
    int random = 1 + (rand() % 9);

    std::shared_ptr<Shape> shape;

    switch (random) {
        case 1: // 1/9 chance for Z
            shape = std::make_shared<Z>(x, y);
            break;
        case 2: // 1/9 chance for S
            shape = std::make_shared<S>(x, y);
            break;
        case 3: // 1/9 chance for L
            shape = std::make_shared<L>(x, y);
            break;
        case 4: // 1/9 chance for J
            shape = std::make_shared<J>(x, y);
            break;;
        case 5: // 1/9 chance for T
            shape = std::make_shared<T>(x, y);
            break;
        case 6: // 1/9 chance for O
            shape = std::make_shared<O>(x, y);
            break;
        case 7: // 1/9 chance for I
            shape = std::make_shared<I>(x, y);
            break;
        case 8: // 2/9 chance for Z
            shape = std::make_shared<Z>(x, y);
            break;
        case 9: // 2/9 chance for S
            shape = std::make_shared<S>(x, y);
            break;
        default:
            random = 1 + (rand() % 7);
    }

    return shape;
}

std::shared_ptr<Shape> Level4::genShapeFile() {
    char shapeType;

    // read from file
    sequence >> shapeType;
    
    // Read each character from the file and create the corresponding shape
        std::shared_ptr<Shape> shape;
        if(sequence.eof()) {
            sequence.clear();
            // moves to beginning
            sequence.seekg(0, std::ios::beg);
            sequence >> shapeType;
        }
    
    // Read each character from the file and create the corresponding shape
        
        // Create the shape based on the character read
        switch (shapeType) {
            case 'S':
                shape = std::make_shared<S>(x, y); // You can adjust x, y, turn as needed
                break;
            case 'Z':
                shape = std::make_shared<Z>(x, y);
                break;
            case 'T':
                shape = std::make_shared<T>(x, y);
                break;
            case 'I':
                shape = std::make_shared<I>(x, y);
                break;
            case 'O':
                shape = std::make_shared<O>(x, y);
                break;
            case 'L':
                shape = std::make_shared<L>(x, y);
                break;
            case 'J':
                shape = std::make_shared<J>(x, y);
                break;
            default:
                sequence >> shapeType; // go to next shape
        }
    return shape;  // Return the vector of generated shapes
}
