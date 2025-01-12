#ifndef LEVEL_H
#define LEVEL_H

#include "shape.h"
#include <string>
#include <fstream>
#include <memory>

class Level {
    protected:
        int difficulty;
        std::ifstream& sequence;
        bool rng;
    public:
        Level(int difficulty, std::ifstream& sequence);
        // will generate shapes based on the properties of each level
        virtual std::shared_ptr<Shape> genShape() = 0;
        // will be any additional modifiers or things levels will add
        // such as heavy and others
        //virtual void levelEffects();

        int getDifficulty() const;
        std::ifstream& getSequence() const;
        virtual void setRng(bool dif); // only necessary for 3 and 4

        //void setSequence();


        virtual ~Level() = default;
};

class Level0: public Level {
    public:
        Level0(std::ifstream& stream);
        std::shared_ptr<Shape> genShape() override;
        //void levelEffects() override; // this function will do nothing
};

class Level1: public Level {
    public:
        Level1(std::ifstream& stream);
        std::shared_ptr<Shape> genShape() override;
        //void levelEffects() override;
};

class Level2 : public Level {
    public:
        Level2(std::ifstream& stream);
        std::shared_ptr<Shape> genShape()override;
        //void levelEffects() override;
};

class Level3 : public Level {
    public:
        Level3(std::ifstream& stream);
        std::shared_ptr<Shape> genShape() override;
        std::shared_ptr<Shape> genShapeFile();
        //void levelEffects() override;
};

class Level4 : public Level {
    public:
        Level4(std::ifstream& stream);
        std::shared_ptr<Shape> genShape() override;
        std::shared_ptr<Shape> genShapeFile();
        //void levelEffects() override;
};

#endif
