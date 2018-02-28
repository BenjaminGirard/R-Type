//
// Created by tetard on 28/01/18.
//

#ifndef CPP_RTYPE_AUTOMOVECOMPONENT_HPP
#define CPP_RTYPE_AUTOMOVECOMPONENT_HPP

#include <AComponent.hpp>
#include "AMovementComponent.hpp"

class AutoMoveComponent : public SolidEngine::AComponent {
private:
    std::shared_ptr<AMovementComponent> _moveBehavior;

public:
    explicit AutoMoveComponent(std::shared_ptr<AMovementComponent> move) : AComponent(std::type_index(typeid(AutoMoveComponent))), _moveBehavior(move) {}

    ~AutoMoveComponent() override = default;

    const std::pair<int32_t, int32_t> autoMove(int32_t x, int32_t y, double dirX, double dirY, uint32_t speed) {
      return _moveBehavior->move(x, y, dirX, dirY, speed);
    };
};

#endif //CPP_RTYPE_AUTOMOVECOMPONENT_HPP
