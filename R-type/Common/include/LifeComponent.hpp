//
// Created by tetard on 20/01/18.
//

#ifndef CPP_RTYPE_LIFECOMPONENT_HPP
#define CPP_RTYPE_LIFECOMPONENT_HPP

#include <AComponent.hpp>
#include <cstdint>

class LifeComponent : public SolidEngine::AComponent {
public:
    LifeComponent(int64_t life = 0, uint64_t shield = 0) : AComponent(std::type_index(typeid(LifeComponent))),
                                                            _life(life), _shield(shield) {}

    ~LifeComponent() override = default;

    uint64_t getLife() const {return _life;}
    int64_t getShield() const {return _shield;}

    void    takeDmg(int64_t power) {
        if (_shield > 0) {
            _shield -= power;
            if (_shield < 0){
                _life += _shield;
                _shield = 0;
            }
        }
        else
            _life -= power;
    }

private:
    int64_t _life;
    int64_t _shield;

};

#endif //CPP_RTYPE_LIFECOMPONENT_HPP
