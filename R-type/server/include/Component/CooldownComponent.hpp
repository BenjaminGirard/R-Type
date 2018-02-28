//
// Created by tetard on 26/01/18.
//

#ifndef CPP_RTYPE_COOLDOWNCOMPONENT_HPP
#define CPP_RTYPE_COOLDOWNCOMPONENT_HPP

#include <CoolDown.hpp>
#include <typeindex>
#include <AComponent.hpp>

class CoolDownComponent : public SolidEngine::AComponent {
private:
    CoolDown _cd;

public:
    CoolDownComponent(double cd) : AComponent(std::type_index(typeid(CoolDownComponent))), _cd(cd) {}

    bool isCoolDownOver() { return _cd.isCoolDownOver(); }
};

#endif //CPP_RTYPE_COOLDOWNCOMPONENT_HPP
