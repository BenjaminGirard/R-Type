//
// Created by tetard on 21/01/18.
//

#ifndef CPP_RTYPE_SPEEDCOMPONENT_HPP
#define CPP_RTYPE_SPEEDCOMPONENT_HPP

#include <cstdint>
#include <AComponent.hpp>

class SpeedComponent : public SolidEngine::AComponent {
private:
    uint32_t _speed;

public:
    SpeedComponent(uint32_t speed = 1000)
    : AComponent(std::type_index(typeid(SpeedComponent))),
    _speed(speed) {}

    ~SpeedComponent() override = default;

    uint32_t getSpeed() const { return _speed; }
    void setSpeed(uint32_t speed) { _speed = speed; }
};

#endif //CPP_RTYPE_SPEEDCOMPONENT_HPP
