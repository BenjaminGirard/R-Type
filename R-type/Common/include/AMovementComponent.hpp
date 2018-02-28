//
// Created by tetard on 25/01/18.
//

#ifndef CPP_RTYPE_MOVEMENTCOMPONENT_HPP
#define CPP_RTYPE_MOVEMENTCOMPONENT_HPP

#include <typeindex>
#include <AComponent.hpp>
#include <chrono>
#include <utility>

class AMovementComponent {
protected:
    std::chrono::time_point<std::chrono::high_resolution_clock> _lastTimeCheck;

public:
    AMovementComponent() : _lastTimeCheck(std::chrono::high_resolution_clock::now()) {}

    virtual ~AMovementComponent() = default;

    virtual const std::pair<int32_t, int32_t> move(int32_t x, int32_t y, double dirX, double dirY, uint32_t speed) = 0;

    void updateTimeCheck() {_lastTimeCheck = std::chrono::high_resolution_clock::now(); }
};

#endif //CPP_RTYPE_MOVEMENTCOMPONENT_HPP


// (x, y) 3 , 3
// (dix, diy) 0.5, 1
// (speed) 1
// (time)

// x = 3 + (0.5 * 1 * 1) = 4
// y = 4

