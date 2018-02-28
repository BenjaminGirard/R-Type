//
// Created by yohann on 27/01/18.
//

#include "BibMonster.hpp"
#include <LifeComponent.hpp>
#include <PowerComponent.hpp>
#include <SizeComponent.hpp>
#include <SpeedComponent.hpp>
#include <StraightMoveComponent.hpp>
#include <CosHorizontalMovementComponent.hpp>
#include <TeamComponent.hpp>
#include <GeneratorContainerComponent.hpp>
#include <BalancePowerComponent.hpp>
#include <BasicProjectileGeneratorComponent.hpp>
#include <CooldownComponent.hpp>
#include <Component/AutoMoveComponent.hpp>
#include "Mediator.hpp"

BibMonster::BibMonster()
        : ADynamicEntity() {}

void BibMonster::createEntity(std::shared_ptr<SolidEngine::Mediator> &mediator,
                              int32_t posx, int32_t posy, double dirx, double diry) const {
  auto &bib = mediator->pingCreateEntity();

  bib.addComp<BalancePowerComponent>(3);
  bib.addComp<CollisionComponent>();
  bib.addComp<DirectionComponent>(dirx, diry);
  bib.addComp<SolidEngine::GraphicComponent>("../Assets/monster125x106.png");
  bib.addComp<LifeComponent>(4);
  bib.addComp<PositionComponent>(posx, posy);
  bib.addComp<PowerComponent>(1);
  bib.addComp<SizeComponent>(125, 106);
  bib.addComp<SpeedComponent>(500);
  bib.addComp<AutoMoveComponent>(std::make_shared<StraightMoveComponent>());
  bib.addComp<TeamComponent>(Team::ENEMY);
  bib.addComp<GeneratorContainerComponent>();

  auto &generatorContainer = bib.getComp<GeneratorContainerComponent>();

  generatorContainer.addGenerator(std::make_shared<BasicProjectileGeneratorComponent>("../Assets/projectile70x71.png"));

}

std::string BibMonster::getEntityInfo() const { return ("8"); }

//extern "C" {
//PLUGIN_EXPORT ADynamicEntity* createEntity()
//{
//    return new BibMonster();
//}
//
//PLUGIN_EXPORT void deleteEntity(ADynamicEntity* object )
//{
//    delete object;
//}
//}
