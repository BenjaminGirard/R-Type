//
// Created by yohann on 27/01/18.
//

#include "MatteusMonster.hpp"
#include <LifeComponent.hpp>
#include <PowerComponent.hpp>
#include <SizeComponent.hpp>
#include <SpeedComponent.hpp>
#include <StraightMoveComponent.hpp>
#include <CosHorizontalMovementComponent.hpp>
#include <TeamComponent.hpp>
#include <GeneratorContainerComponent.hpp>
#include <BalancePowerComponent.hpp>
#include <SmallProjectileGeneratorComponent.hpp>
#include <CooldownComponent.hpp>
#include "PositionComponent.hpp"
#include "GraphicComponent.hpp"
#include "CollisionComponent.hpp"
#include "DirectionComponent.hpp"

MatteusMonster::MatteusMonster() : ADynamicEntity() {}

void MatteusMonster::createEntity(std::shared_ptr<SolidEngine::Mediator> &mediator,
                                  int32_t posx, int32_t posy, double dirx, double diry) const {
    auto &matteus = mediator->pingCreateEntity();

    matteus.addComp<BalancePowerComponent>(2);
    matteus.addComp<CollisionComponent>();
    matteus.addComp<DirectionComponent>(dirx, diry);
    matteus.addComp<SolidEngine::GraphicComponent>("../Assets/monster50x42.png");
    matteus.addComp<LifeComponent>(2);
    matteus.addComp<PositionComponent>(posx, posy);
    matteus.addComp<PowerComponent>(1);
    matteus.addComp<SizeComponent>(50, 42);
    matteus.addComp<SpeedComponent>(700);
    matteus.addComp<StraightMoveComponent>();
    matteus.addComp<TeamComponent>(Team::ENEMY);

    auto &generatorContainer = matteus.getComp<GeneratorContainerComponent>();

    auto &gun = mediator->pingCreateEntity();
    gun.addComp<BalancePowerComponent>(5);
    gun.addComp<CoolDownComponent>(300);
    gun.addComp<DirectionComponent>(dirx, diry);
    gun.addComp<PositionComponent>();
    gun.addComp<SpeedComponent>(700);
    gun.addComp<CosHorizontalMovementComponent>();
    gun.addComp<TeamComponent>(Team::ENEMY);
    gun.addComp<SmallProjectileGeneratorComponent>("../Assets/projectile30x30.png");

    generatorContainer.addGenerator(&gun);

}

std::string MatteusMonster::getEntityInfo() const { return ("7"); }

//extern "C" {
//PLUGIN_EXPORT ADynamicEntity* createEntity()
//{
//    return new MatteusMonster();
//}
//
//PLUGIN_EXPORT void deleteEntity(ADynamicEntity *object )
//{
//    delete object;
//}
//}