//
// Created by tetard on 23/01/18.
//

#ifndef CPP_RTYPE_PROJECTILEGENERATORCOMPONENT_HPP
#define CPP_RTYPE_PROJECTILEGENERATORCOMPONENT_HPP

#include "Rtype.hpp"
#include "AGeneratorComponent.hpp"
#include "CollisionComponent.hpp"
#include "GraphicComponent.hpp"
#include "AutoMoveComponent.hpp"
#include "CosHorizontalMovementComponent.hpp"
#include "Mediator.hpp"

class BasicProjectileGeneratorComponent : public AGeneratorComponent {

public:
    BasicProjectileGeneratorComponent(const std::string &picPath) : AGeneratorComponent(picPath, 200) {}

    ~BasicProjectileGeneratorComponent() override = default;

    void generate(std::shared_ptr<SolidEngine::Mediator> &med,
                  const PositionComponent &pos,
                  const DirectionComponent &dir,
                  const TeamComponent &team) override {

          if (!_cd.isCoolDownOver())
                return ;
          auto &projectile = med->pingCreateEntity();

          projectile.addComp<CollisionComponent>();
          projectile.addComp<DirectionComponent>(dir.getX(), dir.getY());
          projectile.addComp<SolidEngine::GraphicComponent>(_picturePath);
          projectile.addComp<LifeComponent>(1, 0);
          projectile.addComp<PositionComponent>(pos.x + (5 * dir.getX()), pos.y + (5 * dir.getY()));
          projectile.addComp<PowerComponent>(1);
          projectile.addComp<SizeComponent>(70, 71);
          projectile.addComp<SpeedComponent>(800);
          projectile.addComp<AutoMoveComponent>(std::make_shared<CosHorizontalMovementComponent>());
          projectile.addComp<TeamComponent>(team.getTeam());
    }
};

#endif //CPP_RTYPE_PROJECTILEGENERATORCOMPONENT_HPP
