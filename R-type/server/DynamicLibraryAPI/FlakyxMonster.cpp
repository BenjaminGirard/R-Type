//
// Created by yohann on 27/01/18.
//

#include "FlakyxMonster.hpp"
#include <LifeComponent.hpp>
#include <PowerComponent.hpp>
#include <SizeComponent.hpp>
#include <SpeedComponent.hpp>
#include <StraightMoveComponent.hpp>
#include <CosHorizontalMovementComponent.hpp>
#include <TeamComponent.hpp>
#include <GeneratorContainerComponent.hpp>
#include <BalancePowerComponent.hpp>
#include <BigProjectileGeneratorComponent.hpp>
#include <CooldownComponent.hpp>
#include "PositionComponent.hpp"
#include "GraphicComponent.hpp"
#include "CollisionComponent.hpp"
#include "DirectionComponent.hpp"

FlakyxMonster::FlakyxMonster() : ADynamicEntity() {}

void FlakyxMonster::createEntity(std::shared_ptr<SolidEngine::Mediator> &mediator,
                                 int32_t posx, int32_t posy, double dirx, double diry) const {
    auto &flakyx = mediator->pingCreateEntity();

    flakyx.addComp<BalancePowerComponent>(8);
    flakyx.addComp<CollisionComponent>();
    flakyx.addComp<DirectionComponent>(dirx, diry);
    flakyx.addComp<SolidEngine::GraphicComponent>("/Assets/monster200x171.png");
    flakyx.addComp<LifeComponent>(8);
    flakyx.addComp<PositionComponent>(posx, posy);
    flakyx.addComp<PowerComponent>(1);
    flakyx.addComp<SizeComponent>(200, 171);
    flakyx.addComp<SpeedComponent>(400);
    flakyx.addComp<StraightMoveComponent>();
    flakyx.addComp<TeamComponent>(Team::ENEMY);

    auto &generatorContainer = flakyx.getComp<GeneratorContainerComponent>();

    auto &gun = mediator->pingCreateEntity();
    gun.addComp<BalancePowerComponent>(7);
    gun.addComp<CoolDownComponent>(700);
    gun.addComp<DirectionComponent>(dirx, diry);
    gun.addComp<PositionComponent>(posx, posy);
    gun.addComp<SpeedComponent>(400);
    gun.addComp<CosHorizontalMovementComponent>();
    gun.addComp<TeamComponent>(Team::ENEMY);
    gun.addComp<BigProjectileGeneratorComponent>("../Assets/projectile110x111.png");
    generatorContainer.addGenerator(&gun);

}

std::string FlakyxMonster::getEntityInfo() const { return ("15"); }

//extern "C" {
//PLUGIN_EXPORT ADynamicEntity* createEntity()
//{
//    return new FlakyxMonster();
//}
//
//PLUGIN_EXPORT void deleteEntity(ADynamicEntity* object )
//{
//    delete object;
//}
//}