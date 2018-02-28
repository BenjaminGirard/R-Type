//
// Created by yohann on 27/01/18.
//

#ifndef CPP_RTYPE_MATTEUSMONSTER_HPP
#define CPP_RTYPE_MATTEUSMONSTER_HPP

#include <Mediator.hpp>
#include "ADynamicEntity.hpp"

class MatteusMonster : public ADynamicEntity {
public:
    MatteusMonster();
    ~MatteusMonster() override = default;

    void createEntity(std::shared_ptr<SolidEngine::Mediator> &mediator,
                      int32_t posx, int32_t posy, double dirx, double diry) const override;

    std::string getEntityInfo() const override;
};


#endif //CPP_RTYPE_MATTEUSMONSTER_HPP
