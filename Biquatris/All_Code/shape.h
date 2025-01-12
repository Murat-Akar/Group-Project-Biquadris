#ifndef SHAPE_H
#define SHAPE_H

#include "block.h"
#include <vector>
#include <memory>

class Shape {
    protected:
        char letter;
        int rotationState;
        std::vector<Block> blocks;

    public:
        Shape(char letter);
        Shape(const Shape& other);
        virtual ~Shape() = default;
        virtual std::shared_ptr<Shape> clockwise() = 0;
        virtual std::shared_ptr<Shape> counter() = 0;
        virtual std::shared_ptr<Shape> clone() const = 0;
        
        std::shared_ptr<Shape> left();
        std::shared_ptr<Shape> right();
        std::shared_ptr<Shape> down();

        char getLetter() const;
        std::vector<Block> getBlocks() const;
};

class L : public Shape {
    public:
        L(int startX, int startY/*, int turn*/);
        L(const L& other);
        std::shared_ptr<Shape> clockwise() override;
        std::shared_ptr<Shape> counter() override;
        std::shared_ptr<Shape> clone() const override;

};

class J : public Shape {
    public:
        J(int startX, int startY/*, int turn*/);
        J(const J& other);
        std::shared_ptr<Shape> clockwise() override;
        std::shared_ptr<Shape> counter() override;
        std::shared_ptr<Shape> clone() const override;
};

class I : public Shape {
    public:
        I(int startx, int startY/*, int turn*/);
        I(const I& other);
        std::shared_ptr<Shape> clockwise() override;
        std::shared_ptr<Shape> counter() override;
        std::shared_ptr<Shape> clone() const override;
};

class O : public Shape {
    public:
        O(int startx, int startY/*, int turn*/);
        O(const O& other);
        std::shared_ptr<Shape> clockwise() override;
        std::shared_ptr<Shape> counter() override;
        std::shared_ptr<Shape> clone() const override;
};

class Z : public Shape {
    public:
        Z(int startx, int startY/*, int turn*/);
        Z(const Z& other);
        std::shared_ptr<Shape> clockwise() override;
        std::shared_ptr<Shape> counter() override;
        std::shared_ptr<Shape> clone() const override;
};

class S : public Shape {
    public:
        S(int startx, int startY/*, int turn*/);
        S(const S& other);
        std::shared_ptr<Shape> clockwise() override;
        std::shared_ptr<Shape> counter() override;
        std::shared_ptr<Shape> clone() const override;
};

class T : public Shape {
    public:
        T(int startx, int startY/*, int turn*/);
        T(const T& other);
        std::shared_ptr<Shape> clockwise() override;
        std::shared_ptr<Shape> counter() override;
        std::shared_ptr<Shape> clone() const override;
};
#endif
