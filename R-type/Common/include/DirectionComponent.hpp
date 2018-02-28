//
// Created by tetard on 21/01/18.
//

#ifndef CPP_RTYPE_DIRECTIONCOMPONENT_HPP
#define CPP_RTYPE_DIRECTIONCOMPONENT_HPP

#include <AComponent.hpp>
#include <cstdint>

class DirectionComponent : public SolidEngine::AComponent {
private:
    // X and y should always be between -1 and 1
    double _x;
    double _y;

public:
    DirectionComponent(double x, double y) : AComponent(std::type_index(typeid(DirectionComponent))), _x(x), _y(y) {}

    ~DirectionComponent() override = default;

    const double getX() const { return _x; }
    const double getY() const { return _y; }

    void setX(double x) { _x = x; }
    void setY(double y) { _y = y; }
};

#endif //CPP_RTYPE_DIRECTIONCOMPONENT_HPP
