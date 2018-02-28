//
// Created by yohann on 27/01/18.
//

#ifndef CPP_RTYPE_LONGBIGPROJECTILEGENERATORCOMPONENT_HPP
#define CPP_RTYPE_LONGBIGPROJECTILEGENERATORCOMPONENT_HPP

#include "AGeneratorComponent.hpp"
#include "CollisionComponent.hpp"
#include "GraphicComponent.hpp"

class LongBigProjectileGeneratorComponent : public AGeneratorComponent {
private:
    std::string _picturePath;

public:
    LongBigProjectileGeneratorComponent(const std::string &picPath) : AGeneratorComponent(), _picturePath(picPath) {}

    ~LongBigProjectileGeneratorComponent() override = default;

    void generate(std::shared_ptr<SolidEngine::Mediator> &med,
                  const PositionComponent &pos,
                  const DirectionComponent &dir,
                  const TeamComponent &team) override {

        auto &projectile = med->pingCreateEntity();

        projectile.addComp<CollisionComponent>();
        projectile.addComp<DirectionComponent>(dir.getX(), dir.getY());
        projectile.addComp<SolidEngine::GraphicComponent>(_picturePath);
        projectile.addComp<LifeComponent>(1, 0);
        projectile.addComp<PositionComponent>(pos.x + (5 * dir.getX()), pos.y + (5 * dir.getY())); // ????
        projectile.addComp<PowerComponent>(1);
        projectile.addComp<SizeComponent>(110, 12);
        projectile.addComp<SpeedComponent>(700);
        projectile.addComp<TeamComponent>(team.getTeam());
    }
};

#endif //CPP_RTYPE_LONGBIGPROJECTILEGENERATORCOMPONENT_HPP
