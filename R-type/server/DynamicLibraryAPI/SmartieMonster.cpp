//
// Created by yohann on 27/01/18.
//

#include "SmartieMonster.hpp"

#include <LifeComponent.hpp>
#include <PowerComponent.hpp>
#include <SizeComponent.hpp>
#include <SpeedComponent.hpp>
#include <StraightMoveComponent.hpp>
#include <TeamComponent.hpp>
#include <GeneratorContainerComponent.hpp>
#include <BalancePowerComponent.hpp>
#include <LongSmallProjectileGeneratorComponent.hpp>
#include <CooldownComponent.hpp>
#include "PositionComponent.hpp"
#include "GraphicComponent.hpp"
#include "CollisionComponent.hpp"
#include "DirectionComponent.hpp"

SmartieMonster::SmartieMonster() : ADynamicEntity() {}

void SmartieMonster::createEntity(std::shared_ptr<SolidEngine::Mediator> &mediator,
                                  int32_t posx, int32_t posy, double dirx, double diry) const {
    auto &smartie = mediator->pingCreateEntity();

    smartie.addComp<BalancePowerComponent>(2);
    smartie.addComp<CollisionComponent>();
    smartie.addComp<DirectionComponent>(dirx, diry);
    smartie.addComp<SolidEngine::GraphicComponent>("../Assets/laser_monster50x36.png");
    smartie.addComp<LifeComponent>(5);
    smartie.addComp<PositionComponent>(posx, posy);
    smartie.addComp<PowerComponent>(1);
    smartie.addComp<SizeComponent>(50, 36);
    smartie.addComp<SpeedComponent>(700);
    smartie.addComp<StraightMoveComponent>();
    smartie.addComp<TeamComponent>(Team::ENEMY);

    auto &generatorContainer = smartie.getComp<GeneratorContainerComponent>();

    auto &gun = mediator->pingCreateEntity();
    gun.addComp<BalancePowerComponent>(5);
    gun.addComp<CoolDownComponent>(300);
    gun.addComp<DirectionComponent>(dirx, diry);
    gun.addComp<PositionComponent>(posx, posy);
    gun.addComp<SpeedComponent>(700);
    gun.addComp<StraightMoveComponent>();
    gun.addComp<TeamComponent>(Team::ENEMY);
    gun.addComp<LongSmallProjectileGeneratorComponent>("../Assets/laser30x3.png");

    generatorContainer.addGenerator(&gun);

}

std::string SmartieMonster::getEntityInfo() const { return ("7"); }

//extern "C" {
//PLUGIN_EXPORT ADynamicEntity* createEntity()
//{
//    return new SmartieMonster();
//}
//
//PLUGIN_EXPORT void deleteEntity(ADynamicEntity* object )
//{
//    delete object;
//}
//}