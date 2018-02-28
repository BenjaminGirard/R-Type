//
// Created by tetard on 22/01/18.
//

#ifndef CPP_RTYPE_COOLDOWN_HPP
#define CPP_RTYPE_COOLDOWN_HPP

#include <cstdint>
#include <chrono>

class CoolDown {
private:
    double _coolDownSet;
    double _currentCoolDown;

    std::chrono::time_point<std::chrono::high_resolution_clock> _lastTimeCheck;

public:
  CoolDown() = default;

   CoolDown(double coolDown) :
            _coolDownSet(coolDown / 1000),
            _currentCoolDown(coolDown / 1000),
            _lastTimeCheck(std::chrono::high_resolution_clock::now()) {}

    ~CoolDown() = default;

    bool isCoolDownOver() {
      std::chrono::duration<double> timeSpent = std::chrono::high_resolution_clock::now() - _lastTimeCheck;
      _lastTimeCheck = std::chrono::high_resolution_clock::now();

      _currentCoolDown -= timeSpent.count();
      if (_currentCoolDown <= 0) {
        _currentCoolDown = _coolDownSet;
        return true;
      }
      return false;
    }

    const double    getCoolDownSet(void) const {
      return _coolDownSet;
    }

    const double    getCurrentCoolDown(void) const {
        return _currentCoolDown;
    }

    CoolDown(const CoolDown &cp) :
    _coolDownSet(cp.getCoolDownSet()),
    _currentCoolDown(cp.getCurrentCoolDown()),
    _lastTimeCheck(std::chrono::high_resolution_clock::now())
    {}

    CoolDown &operator=(const CoolDown &cp) {
      if (&cp != this) {
        _coolDownSet = cp.getCoolDownSet();
        _currentCoolDown = cp.getCurrentCoolDown();
        _lastTimeCheck = std::chrono::high_resolution_clock::now();
      }
      return *this;
    }

};

#endif //CPP_RTYPE_COOLDOWN_HPP
