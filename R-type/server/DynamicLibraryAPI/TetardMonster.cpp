//
// Created by flakyyx on 26/01/18.
//

#include <BalancePowerComponent.hpp>
#include "TetardMonster.hpp"
#include "GraphicComponent.hpp"
#include "LifeComponent.hpp"
#include "CollisionComponent.hpp"
#include "DirectionComponent.hpp"
#include "PositionComponent.hpp"
#include "PowerComponent.hpp"
#include "SizeComponent.hpp"
#include "SpeedComponent.hpp"
#include "TeamComponent.hpp"
#include "Rtype.hpp"

TetardMonster::TetardMonster() : ADynamicEntity() {}

void  TetardMonster::createEntity(std::shared_ptr<SolidEngine::Mediator> &mediator,
                                 int32_t posx, int32_t posy, double dirx, double diry) const {
  auto &Tetard = mediator->pingCreateEntity();

  Tetard.addComp<BalancePowerComponent>(10);
  Tetard.addComp<CollisionComponent>();
  Tetard.addComp<DirectionComponent>(dirx, diry);
  Tetard.addComp<SolidEngine::GraphicComponent>("../Assets/tetard50x11.png");
  Tetard.addComp<LifeComponent>(100);
  Tetard.addComp<PositionComponent>(posx, posy);
  Tetard.addComp<PowerComponent>(1);
  Tetard.addComp<SizeComponent>(50, 50);
  Tetard.addComp<SpeedComponent>(1000);
  Tetard.addComp<TeamComponent>(Team::ENEMY);
}

std::string  TetardMonster::getEntityInfo() const {
  /* Returns the balancePowerComponent */
  return ("10");
}

//extern "C" {
//PLUGIN_EXPORT ADynamicEntity* createEntity()
//{
//  return new TetardMonster();
//}
//
//PLUGIN_EXPORT void deleteEntity(ADynamicEntity* object )
//{
//  delete object;
//}
//}