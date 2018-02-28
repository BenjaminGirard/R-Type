//
// Created by tetard on 19/01/18.
//

#ifndef CPP_RTYPE_POSITIONCOMPONENT_HPP
#define CPP_RTYPE_POSITIONCOMPONENT_HPP

#include <cstdint>
#include "AComponent.hpp"

class PositionComponent : public SolidEngine::AComponent {
public:
    int32_t x;
    int32_t y;

    PositionComponent(int32_t X = 0, int32_t Y = 0) :
            AComponent(std::type_index(typeid(PositionComponent))), x(X), y(Y) {}

    ~PositionComponent() override = default;
};

#endif //CPP_RTYPE_POSITIONCOMPONENT_HPP
