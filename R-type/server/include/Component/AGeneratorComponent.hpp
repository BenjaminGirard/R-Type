//
// Created by tetard on 22/01/18.
//

#ifndef CPP_RTYPE_GUNCOMPONENT_HPP
#define CPP_RTYPE_GUNCOMPONENT_HPP


#include <typeindex>
#include <AComponent.hpp>
#include "PositionComponent.hpp"
#include "DirectionComponent.hpp"
#include "TeamComponent.hpp"
#include "CoolDown.hpp"

class AGeneratorComponent {
protected:
    std::string _picturePath;
    CoolDown _cd;

public:
    AGeneratorComponent(const std::string &picPath, uint32_t coolDown) : _picturePath(picPath), _cd(coolDown) {}

    virtual ~AGeneratorComponent() = default;

    virtual void generate(std::shared_ptr<SolidEngine::Mediator> &med,
                          const PositionComponent &pos,
                          const DirectionComponent &dir,
                          const TeamComponent &team) = 0;

    bool IsCoolDownOver() { return _cd.isCoolDownOver(); }
};


#endif //CPP_RTYPE_GUNCOMPONENT_HPP
