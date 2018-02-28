//
// Created by yohann on 27/01/18.
//

#ifndef CPP_RTYPE_SMARTIEMONSTER_HPP
#define CPP_RTYPE_SMARTIEMONSTER_HPP

#include <Mediator.hpp>
#include "ADynamicEntity.hpp"

class SmartieMonster : public ADynamicEntity {
public:
    SmartieMonster();
    ~SmartieMonster() override = default;

    void createEntity(std::shared_ptr<SolidEngine::Mediator> &mediator,
                      int32_t posx, int32_t posy, double dirx, double diry) const override;

    std::string getEntityInfo() const override;
};

#endif //CPP_RTYPE_SMARTIEMONSTER_HPP
