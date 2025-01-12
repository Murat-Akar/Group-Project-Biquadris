#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

class Player;

class Effect {
public:
    virtual void apply(Player& player) = 0;
    virtual void remove(Player& player) = 0;
    virtual std::string getName() const = 0;
    virtual ~Effect() = default;
};

class BlindEffect : public Effect {
public:
    void apply(Player& player) override;
    void remove(Player& player) override;
    std::string getName() const override;
};

class HeavyEffect : public Effect {
public:
    void apply(Player& player) override;
    void remove(Player& player) override;
    std::string getName() const override;
};

class ForceEffect : public Effect {
    std::string shapeType;
public:
    explicit ForceEffect(const std::string& shapeType);
    void apply(Player& player) override;
    void remove(Player& player) override;
    std::string getName() const override;
};

class EffectManager {
    static std::unique_ptr<EffectManager> instance;
    std::unordered_map<Player*, std::vector<std::shared_ptr<Effect>>> playerEffects;
    EffectManager();
public:
    static EffectManager& getInstance();

    void addEffect(Player& player, std::shared_ptr<Effect> effect);
    void removeEffect(Player& player, const std::string& effectName);
    bool hasEffect(Player& player, const std::string& effectName) const;

    std::vector<std::shared_ptr<Effect>> getEffects(Player& player);
};

#endif // EFFECT_H
