//
// Created by tetard on 21/01/18.
//

#ifndef CPP_RTYPE_POWERCOMPONENT_HPP
#define CPP_RTYPE_POWERCOMPONENT_HPP

#include <cstdint>
#include <AComponent.hpp>

class PowerComponent : public SolidEngine::AComponent {
private:
    uint32_t _power;

public:
    PowerComponent(uint32_t power = 1000)
            : AComponent(std::type_index(typeid(PowerComponent))),
              _power(power) {}

    ~PowerComponent() override = default;

    uint32_t getPower() const { return _power; }
    void setPower(uint32_t power) { _power = power; }
};

#endif //CPP_RTYPE_POWERCOMPONENT_HPP
