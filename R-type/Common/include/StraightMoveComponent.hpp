//
// Created by tetard on 25/01/18.
//

#ifndef CPP_RTYPE_STRAIGHTMOVECOMPONENT_HPP
#define CPP_RTYPE_STRAIGHTMOVECOMPONENT_HPP

#include <cstdint>
#include "AMovementComponent.hpp"

class StraightMoveComponent : public AMovementComponent {
public:
    StraightMoveComponent() : AMovementComponent() {}

    const std::pair<int32_t, int32_t> move(int32_t x, int32_t y, double dirX, double dirY, uint32_t speed) override {

      std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - _lastTimeCheck;

//      if (diff.count() > 0.001)
//        _lastTimeCheck = std::chrono::high_resolution_clock::now();

      speed = speed * 1000;
      std::pair<int32_t, int32_t> res(static_cast<int16_t >(x + (dirX * speed * diff.count())), static_cast<int16_t >(y + (dirY * speed * diff.count())));

      return res;
    }

};

#endif //CPP_RTYPE_STRAIGHTMOVECOMPONENT_HPP
