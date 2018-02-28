//
// Created by tetard on 25/01/18.
//

#ifndef CPP_RTYPE_COSMOVEMENTCOMPONENT_HPP
#define CPP_RTYPE_COSMOVEMENTCOMPONENT_HPP

#include <cstdint>
#include <complex>
#include <cstdint>
#include "AMovementComponent.hpp"

class CosHorizontalMovementComponent : public AMovementComponent {
private:
    int _baseY;

public:
    CosHorizontalMovementComponent() : AMovementComponent(), _baseY(std::numeric_limits<int>::min()) {}

    const std::pair<int32_t, int32_t> move(int32_t x, int32_t y, double dirX, double dirY, uint32_t speed) override {

      if (_baseY == std::numeric_limits<int>::min())
        _baseY = y;

      std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - _lastTimeCheck;

      if (diff.count() > 0.001)
        _lastTimeCheck = std::chrono::high_resolution_clock::now();


      std::pair<int32_t, int32_t> res(
              static_cast<int32_t >(x + (dirX * speed * diff.count())),
              static_cast<int32_t >(_baseY + ((_baseY / 5) * cos(x))));

      return res;
    }
};


#endif //CPP_RTYPE_COSMOVEMENTCOMPONENT_HPP
