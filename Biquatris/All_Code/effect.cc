#include "effect.h"
#include "player.h"
#include "shape.h"
#include <iostream>
#include <memory>

std::unique_ptr<EffectManager> EffectManager::instance = nullptr;

EffectManager::EffectManager() {}

EffectManager& EffectManager::getInstance() {
    if (instance == nullptr) {
        instance =  std::make_unique<EffectManager> (EffectManager());
    }
    return *instance;
}

void EffectManager::addEffect(Player& player, std::shared_ptr<Effect> effect) {
    playerEffects[&player].push_back(effect);
    effect->apply(player);
}

void EffectManager::removeEffect(Player& player, const std::string& effectName) {
    auto& effects = playerEffects[&player];
    for (auto it = effects.begin(); it != effects.end(); ++it) {
        if ((*it)->getName() == effectName) {
            (*it)->remove(player);
            effects.erase(it);
            break;
        }
    }
}

bool EffectManager::hasEffect(Player& player, const std::string& effectName) const {
    auto it = playerEffects.find(&player);
    if (it == playerEffects.end()) {
        return false;
    }
    for (const auto& effect : it->second) {
        if (effect->getName() == effectName) {
            return true;
        }
    }
    return false;
}

std::vector<std::shared_ptr<Effect>> EffectManager::getEffects(Player& player) {
    auto it = playerEffects.find(&player);
    if (it != playerEffects.end()) {
        return it->second;
    } else {
        return std::vector<std::shared_ptr<Effect>>();
    }
}

// BlindEffect implementation
void BlindEffect::apply(Player& player) {
    // Implementation for applying the blind effect
    std::cout << "Blind effect applied to Player " << player.getPlayerID() << std::endl;
    // !!!!!!Modify display code to check for blind effect!!!!!!
}

void BlindEffect::remove(Player& player) {
    // Implementation for removing the blind effect
    std::cout << "Blind effect removed from Player " << player.getPlayerID() << std::endl;
}

std::string BlindEffect::getName() const {
    return "blind";
}

// HeavyEffect implementation
void HeavyEffect::apply(Player& player) {
    std::cout << "Heavy effect applied to Player " << player.getPlayerID() << std::endl;
    // !!!!!!Modify movement code to apply heavy effect!!!!!!
}

void HeavyEffect::remove(Player& player) {
    std::cout << "Heavy effect removed from Player " << player.getPlayerID() << std::endl;
}

std::string HeavyEffect::getName() const {
    return "heavy";
}

// ForceEffect implementation
ForceEffect::ForceEffect(const std::string& shapeType)
    : shapeType(shapeType) {}

void ForceEffect::apply(Player& player) {
    std::cout << "Force effect applied to Player " << player.getPlayerID() << " with shape " << shapeType << std::endl;

    // Create new shape based on shapeType
    std::shared_ptr<Shape> forcedShape;
    int x = 1; // Starting x position
    int y = 3; // Starting y position

    if (shapeType == "I") {
        forcedShape = std::make_shared<I>(x, y);
    } else if (shapeType == "J") {
        forcedShape = std::make_shared<J>(x, y);
    } else if (shapeType == "L") {
        forcedShape = std::make_shared<L>(x, y);
    } else if (shapeType == "O") {
        forcedShape = std::make_shared<O>(x, y);
    } else if (shapeType == "S") {
        forcedShape = std::make_shared<S>(x, y);
    } else if (shapeType == "Z") {
        forcedShape = std::make_shared<Z>(x, y);
    } else if (shapeType == "T") {
        forcedShape = std::make_shared<T>(x, y);
    } else {
        std::cerr << "Unknown shape type for force effect: " << shapeType << std::endl;
        return;
    }

    // Update the player's queue to set the forced shape as next
    player.getQueue().setCurrent(forcedShape);
    std::cout << "Player " << player.getPlayerID() << "'s next shape has been forced to " << shapeType << "." << std::endl;

    // Set the forced shape as the player's current shape
    player.setCurrentShape(forcedShape);
}

void ForceEffect::remove(Player& player) {
    // No removal action needed for force effect
}

std::string ForceEffect::getName() const {
    return "force";
}
