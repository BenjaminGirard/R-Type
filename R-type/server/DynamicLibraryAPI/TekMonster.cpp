//
// Created by yohann on 27/01/18.
//

#include "TekMonster.hpp"
#include <LifeComponent.hpp>
#include <PowerComponent.hpp>
#include <SizeComponent.hpp>
#include <SpeedComponent.hpp>
#include <StraightMoveComponent.hpp>
#include <CosHorizontalMovementComponent.hpp>
#include <TeamComponent.hpp>
#include <GeneratorContainerComponent.hpp>
#include <BalancePowerComponent.hpp>
#include <GiantProjectileGeneratorComponent.hpp>
#include <CooldownComponent.hpp>
#include "PositionComponent.hpp"
#include "GraphicComponent.hpp"
#include "CollisionComponent.hpp"
#include "DirectionComponent.hpp"

TekMonster::TekMonster() : ADynamicEntity() {}

void TekMonster::createEntity(std::shared_ptr<SolidEngine::Mediator> &mediator,
                              int32_t posx, int32_t posy, double dirx, double diry) const {
    auto &tek = mediator->pingCreateEntity();

    tek.addComp<BalancePowerComponent>(10);
    tek.addComp<CollisionComponent>();
    tek.addComp<DirectionComponent>(dirx, diry);
    tek.addComp<SolidEngine::GraphicComponent>("../Assets/monster300x257.png");
    tek.addComp<LifeComponent>(15);
    tek.addComp<PositionComponent>(posx, posy);
    tek.addComp<PowerComponent>(1);
    tek.addComp<SizeComponent>(300, 257);
    tek.addComp<SpeedComponent>(200);
    tek.addComp<StraightMoveComponent>();
    tek.addComp<TeamComponent>(Team::ENEMY);

    auto &generatorContainer = tek.getComp<GeneratorContainerComponent>();

    auto &gun = mediator->pingCreateEntity();
    gun.addComp<BalancePowerComponent>(10);
    gun.addComp<CoolDownComponent>(1000);
    gun.addComp<DirectionComponent>(dirx, diry);
    gun.addComp<PositionComponent>(posx, posy);
    gun.addComp<SpeedComponent>(200);
    gun.addComp<CosHorizontalMovementComponent>();
    gun.addComp<TeamComponent>(Team::ENEMY);
    gun.addComp<GiantProjectileGeneratorComponent>("../Assets/projectile160x162.png");
    generatorContainer.addGenerator(&gun);

}

std::string TekMonster::getEntityInfo() const { return ("20"); }

//extern "C" {
//PLUGIN_EXPORT ADynamicEntity* createEntity()
//{
//    return new TekMonster();
//}
//
//PLUGIN_EXPORT void deleteEntity(ADynamicEntity* object )
//{
//    delete object;
//}
//}