//
// Created by yohann on 27/01/18.
//

#include "SolidMonster.hpp"
#include <LifeComponent.hpp>
#include <PowerComponent.hpp>
#include <SizeComponent.hpp>
#include <SpeedComponent.hpp>
#include <StraightMoveComponent.hpp>
#include <TeamComponent.hpp>
#include <GeneratorContainerComponent.hpp>
#include <BalancePowerComponent.hpp>
#include <LongGiantProjectileGeneratorComponent.hpp>
#include <CooldownComponent.hpp>
#include "PositionComponent.hpp"
#include "GraphicComponent.hpp"
#include "CollisionComponent.hpp"
#include "DirectionComponent.hpp"

SolidMonster::SolidMonster() : ADynamicEntity() {}

void SolidMonster::createEntity(std::shared_ptr<SolidEngine::Mediator> &mediator,
                                int32_t posx, int32_t posy, double dirx, double diry) const {
    auto &solid = mediator->pingCreateEntity();

    solid.addComp<BalancePowerComponent>(30);
    solid.addComp<CollisionComponent>();
    solid.addComp<DirectionComponent>(dirx, diry);
    solid.addComp<SolidEngine::GraphicComponent>("../Assets/laser_monster300x219.png");
    solid.addComp<LifeComponent>(80);
    solid.addComp<PositionComponent>(posx, posy);
    solid.addComp<PowerComponent>(1);
    solid.addComp<SizeComponent>(300, 219);
    solid.addComp<SpeedComponent>(200);
    solid.addComp<StraightMoveComponent>();
    solid.addComp<TeamComponent>(Team::ENEMY);

    auto &generatorContainer = solid.getComp<GeneratorContainerComponent>();

    auto &gun = mediator->pingCreateEntity();
    gun.addComp<BalancePowerComponent>(10);
    gun.addComp<CoolDownComponent>(1000);
    gun.addComp<DirectionComponent>(dirx, diry);
    gun.addComp<PositionComponent>(posx, posy);
    gun.addComp<SpeedComponent>(200);
    gun.addComp<StraightMoveComponent>();
    gun.addComp<TeamComponent>(Team::ENEMY);
    gun.addComp<LongGiantProjectileGeneratorComponent>("../Assets/laser170x19.png");
    generatorContainer.addGenerator(&gun);
}

std::string SolidMonster::getEntityInfo() const { return ("40"); }

//extern "C" {
//PLUGIN_EXPORT ADynamicEntity* createEntity()
//{
//    return new SolidMonster();
//}
//
//PLUGIN_EXPORT void deleteEntity(ADynamicEntity* object )
//{
//    delete object;
//}
//}