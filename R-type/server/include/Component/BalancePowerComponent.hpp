//
// Created by tetard on 23/01/18.
//

#ifndef CPP_RTYPE_BALANCEPOWERCOMPONENT_HPP
# define CPP_RTYPE_BALANCEPOWERCOMPONENT_HPP

#include "AComponent.hpp"
#include <cstdint>

class BalancePowerComponent : public SolidEngine::AComponent {
private:
    int32_t _power;

public:
    BalancePowerComponent(int32_t power) : AComponent(std::type_index(typeid(BalancePowerComponent))), _power(power) {}

    ~BalancePowerComponent() override = default;

    int32_t getPower() const { return _power; }
    void setPower(int32_t power) { _power = power; }
};

#endif //CPP_RTYPE_BALANCEPOWERCOMPONENT_HPP
