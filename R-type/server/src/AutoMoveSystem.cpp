//
// Created by tetard on 28/01/18.
//

#include <PositionComponent.hpp>
#include <SpeedComponent.hpp>
#include <Component/GeneratorContainerComponent.hpp>
#include <AMovementComponent.hpp>
#include <GameInstance.hpp>
#include "AutoMoveSystem.hpp"
#include "AutoMoveComponent.hpp"

AutoMoveSystem::AutoMoveSystem(const std::shared_ptr<SolidEngine::Mediator> &mediator) : SolidEngine::ASystem(mediator) {
  _requiredComp = {
          std::type_index(typeid(AutoMoveComponent)),
          std::type_index(typeid(PositionComponent)),
          std::type_index(typeid(SpeedComponent)),
          std::type_index(typeid(DirectionComponent))
  };
}

void AutoMoveSystem::execute() {
  for (auto &en : _entityVec) {
    auto &EntityPos = en->getComp<PositionComponent>();
    auto &EntitySpeed = en->getComp<SpeedComponent>();
    auto &EntityDirection = en->getComp<DirectionComponent>();
    auto newPlayerPos = en->getComp<AutoMoveComponent>().autoMove(EntityPos.x, EntityPos.y, EntityDirection.getX(), EntityDirection.getY(),
                                                                      EntitySpeed.getSpeed());

    EntityPos.x = newPlayerPos.first;
    EntityPos.y = newPlayerPos.second;
  }
}