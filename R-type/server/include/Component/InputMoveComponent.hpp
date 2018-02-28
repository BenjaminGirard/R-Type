//
// Created by tetard on 28/01/18.
//

#ifndef CPP_RTYPE_INPUTMOVECOMPONENT_HPP
#define CPP_RTYPE_INPUTMOVECOMPONENT_HPP

#include <AComponent.hpp>
#include <AMovementComponent.hpp>
#include <memory>

class InputMoveComponent : public SolidEngine::AComponent {
private:
    std::shared_ptr<AMovementComponent> _moveBehavior;

public:
    explicit InputMoveComponent(std::shared_ptr<AMovementComponent> move) : AComponent(std::type_index(typeid(InputMoveComponent))), _moveBehavior(move) {}

    ~InputMoveComponent() override = default;

    void updateTimeCheck() { _moveBehavior->updateTimeCheck(); }

    const std::pair<int32_t, int32_t> inputMove(int32_t x, int32_t y, double dirX, double dirY, uint32_t speed) {
      return _moveBehavior->move(x, y, dirX, dirY, speed);
    };
};

#endif //CPP_RTYPE_INPUTMOVECOMPONENT_HPP
