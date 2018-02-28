//
// Created by yohann on 27/01/18.
//

#include "YougoMonster.hpp"
#include <LifeComponent.hpp>
#include <PowerComponent.hpp>
#include <SizeComponent.hpp>
#include <SpeedComponent.hpp>
#include <StraightMoveComponent.hpp>
#include <TeamComponent.hpp>
#include <GeneratorContainerComponent.hpp>
#include <BalancePowerComponent.hpp>
#include <LongBigProjectileGeneratorComponent.hpp>
#include <CooldownComponent.hpp>


YougoMonster::YougoMonster() : ADynamicEntity() {}

void YougoMonster::createEntity(std::shared_ptr<SolidEngine::Mediator> &mediator,
                                int32_t posx, int32_t posy, double dirx, double diry) const {
    auto &yougo = mediator->pingCreateEntity();

    yougo.addComp<BalancePowerComponent>(7);
    yougo.addComp<CollisionComponent>();
    yougo.addComp<DirectionComponent>(dirx, diry);
    yougo.addComp<SolidEngine::GraphicComponent>("../Assets/laser_monster200x146.png");
    yougo.addComp<LifeComponent>(15);
    yougo.addComp<PositionComponent>(posx, posy);
    yougo.addComp<PowerComponent>(1);
    yougo.addComp<SizeComponent>(200, 146);
    yougo.addComp<SpeedComponent>(400);
    yougo.addComp<StraightMoveComponent>();
    yougo.addComp<TeamComponent>(Team::ENEMY);

    auto &generatorContainer = yougo.getComp<GeneratorContainerComponent>();

    auto &gun = mediator->pingCreateEntity();
    gun.addComp<BalancePowerComponent>(13);
    gun.addComp<CoolDownComponent>(700);
    gun.addComp<DirectionComponent>(dirx, diry);
    gun.addComp<PositionComponent>(posx, posy);
    gun.addComp<SpeedComponent>(400);
    gun.addComp<StraightMoveComponent>();
    gun.addComp<TeamComponent>(Team::ENEMY);
    gun.addComp<LongBigProjectileGeneratorComponent>("../Assets/laser110x12.png");
    generatorContainer.addGenerator(&gun);

}

std::string YougoMonster::getEntityInfo() const { return ("20"); }

//extern "C" {
//PLUGIN_EXPORT ADynamicEntity* createEntity()
//{
//    return new YougoMonster();
//}
//
//PLUGIN_EXPORT void deleteEntity(ADynamicEntity* object )
//{
//    delete object;
//}
//}