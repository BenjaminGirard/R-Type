//
// Created by yohann on 27/01/18.
//

#include "StitchMonster.hpp"
#include <LifeComponent.hpp>
#include <PowerComponent.hpp>
#include <SizeComponent.hpp>
#include <SpeedComponent.hpp>
#include <StraightMoveComponent.hpp>
#include <TeamComponent.hpp>
#include <GeneratorContainerComponent.hpp>
#include <BalancePowerComponent.hpp>
#include <LongBasicProjectileGeneratorComponent.hpp>
#include <CooldownComponent.hpp>
#include "PositionComponent.hpp"
#include "GraphicComponent.hpp"
#include "CollisionComponent.hpp"
#include "DirectionComponent.hpp"

StitchMonster::StitchMonster() : ADynamicEntity() {}

void StitchMonster::createEntity(std::shared_ptr<SolidEngine::Mediator> &mediator,
                                 int32_t posx, int32_t posy, double dirx, double diry) const {
    auto &stitch = mediator->pingCreateEntity();

    stitch.addComp<BalancePowerComponent>(4);
    stitch.addComp<CollisionComponent>();
    stitch.addComp<DirectionComponent>(dirx, diry);
    stitch.addComp<SolidEngine::GraphicComponent>("../Assets/laser_monster125x91.png");
    stitch.addComp<LifeComponent>(8);
    stitch.addComp<PositionComponent>(posx, posy);
    stitch.addComp<PowerComponent>(1);
    stitch.addComp<SizeComponent>(125, 91);
    stitch.addComp<SpeedComponent>(500);
    stitch.addComp<StraightMoveComponent>();
    stitch.addComp<TeamComponent>(Team::ENEMY);

    auto &generatorContainer = stitch.getComp<GeneratorContainerComponent>();

    auto &gun = mediator->pingCreateEntity();
    gun.addComp<BalancePowerComponent>(6);
    gun.addComp<CoolDownComponent>(500);
    gun.addComp<DirectionComponent>(dirx, diry);
    gun.addComp<PositionComponent>(posx, posy);
    gun.addComp<SpeedComponent>(500);
    gun.addComp<StraightMoveComponent>();
    gun.addComp<TeamComponent>(Team::ENEMY);
    gun.addComp<LongBasicProjectileGeneratorComponent>("../Assets/laser70x7.png");

    generatorContainer.addGenerator(&gun);

}

std::string StitchMonster::getEntityInfo() const { return ("10"); }

//extern "C" {
//PLUGIN_EXPORT ADynamicEntity* createEntity()
//{
//    return new StitchMonster();
//}
//
//PLUGIN_EXPORT void deleteEntity(ADynamicEntity* object )
//{
//    delete object;
//}
//}