#include <StraightMoveComponent.hpp>
#include <PositionComponent.hpp>
#include <GeneratorContainerComponent.hpp>
#include <SizeComponent.hpp>
#include <Component/CooldownComponent.hpp>
#include <Component/AutoMoveComponent.hpp>
#include "InputMoveComponent.hpp"
#include <MessageComponent.hpp>
#include <GameInstance.hpp>
#include "InputSystem.hpp"
#include "InputComponent.hpp"
#include "SizeComponent.hpp"
#include "IdPlayerComponent.hpp"

InputSystem::InputSystem(const std::shared_ptr<SolidEngine::Mediator> &med)
    : ASystem(med), _actions({
        {SolidRType::UDPData::INPUT::DOWN, &InputSystem::moveDown},
        {SolidRType::UDPData::INPUT::UP, &InputSystem::moveUp},
        {SolidRType::UDPData::INPUT::LEFT, &InputSystem::moveLeft},
        {SolidRType::UDPData::INPUT::RIGHT, &InputSystem::moveRight},
        {SolidRType::UDPData::INPUT::PAUSE_INPUT, &InputSystem::Pause},
        {SolidRType::UDPData::INPUT::QUIT, &InputSystem::Quit},
        {SolidRType::UDPData::INPUT::SHOOT, &InputSystem::shoot}
    }) {
      _requiredComp = {
              std::type_index(typeid(DirectionComponent)),
              std::type_index(typeid(GeneratorContainerComponent)),
              std::type_index(typeid(IdPlayerComponent)),
              std::type_index(typeid(InputComponent)),
              std::type_index(typeid(InputMoveComponent)),
              std::type_index(typeid(MessageComponent)),
              std::type_index(typeid(PositionComponent)),
              std::type_index(typeid(SizeComponent)),
              std::type_index(typeid(SpeedComponent)),
      };
}

void InputSystem::execute(void) {
  for (auto &it : _entityVec) {
    auto &inputComp = it->getComp<InputComponent>();
    SolidRType::UDPData::INPUT inTmp;
    while ((inTmp = inputComp.tryPop()) != SolidRType::UDPData::INPUT::NONE) {
      _actions[inTmp](*this, it);
    }
    it->getComp<InputMoveComponent>().updateTimeCheck();
  }
}

void InputSystem::pushUpdate(std::shared_ptr<SolidEngine::AEntity> &entity,
                             int32_t x, int32_t y, SolidRType::UDPData::COMMAND_TYPE type) {
  auto & EntityMsg = entity->getComp<MessageComponent>();
  SolidRType::UDPData::UpdateElementInfo tmp;
  std::memset(&tmp, 0, sizeof(SolidRType::UDPData::UpdateElementInfo));
  tmp.elementId = entity->getComp<IdPlayerComponent>()._playerId;
  tmp.PhysicalInfo.x = x;
  tmp.PhysicalInfo.y = y;
  tmp.PhysicalInfo.sizex = 0;
  tmp.PhysicalInfo.sizey = 0;
  tmp.MetaInfo.isPlayer = 1;
  tmp.MetaInfo.level = 0;
  tmp.MetaInfo.nbLives = 1;
  EntityMsg.pushInfoToSend<SolidRType::UDPData::UpdateElementInfo>(entity->getId(), type, tmp);
}

void InputSystem::moveUp(std::shared_ptr<SolidEngine::AEntity> &entity) {
  auto &EntityPos = entity->getComp<PositionComponent>();
  auto &EntitySpeed = entity->getComp<SpeedComponent>();

  auto newPlayerPos = entity->getComp<InputMoveComponent>().inputMove(EntityPos.x, EntityPos.y, 0.0, -1.0, EntitySpeed.getSpeed());
  if (newPlayerPos.second < 0)
    return ;
  EntityPos.x = newPlayerPos.first;
  EntityPos.y = newPlayerPos.second;

  this->pushUpdate(entity, EntityPos.x, EntityPos.y, SolidRType::UDPData::COMMAND_TYPE::UPDATE_ELEMENT);

}

void InputSystem::moveLeft(std::shared_ptr<SolidEngine::AEntity> &entity){
  auto &EntityPos = entity->getComp<PositionComponent>();
  auto &EntitySpeed = entity->getComp<SpeedComponent>();

  auto newPlayerPos = entity->getComp<InputMoveComponent>().inputMove(EntityPos.x, EntityPos.y, -1.0, 0.0, EntitySpeed.getSpeed());
  if (newPlayerPos.first < 0)
    return ;
  EntityPos.x = newPlayerPos.first;
  EntityPos.y = newPlayerPos.second;

  this->pushUpdate(entity, EntityPos.x, EntityPos.y, SolidRType::UDPData::COMMAND_TYPE::UPDATE_ELEMENT);
}

void InputSystem::moveRight(std::shared_ptr<SolidEngine::AEntity> &entity){
  auto &EntityPos = entity->getComp<PositionComponent>();
  auto &EntitySpeed = entity->getComp<SpeedComponent>();

  auto &EntitySize = entity->getComp<SizeComponent>();
  auto newPosPlayer = entity->getComp<InputMoveComponent>().inputMove(EntityPos.x, EntityPos.y, 1.0, 0.0, EntitySpeed.getSpeed());
  if (newPosPlayer.first + EntitySize.width > 1920)
    return ;
  EntityPos.x = newPosPlayer.first;
  EntityPos.y = newPosPlayer.second;

  this->pushUpdate(entity, EntityPos.x, EntityPos.y, SolidRType::UDPData::COMMAND_TYPE::UPDATE_ELEMENT);
}

void InputSystem::moveDown(std::shared_ptr<SolidEngine::AEntity> &entity) {
  auto &EntityPos = entity->getComp<PositionComponent>();
  auto &EntitySpeed = entity->getComp<SpeedComponent>();

  auto &EntitySize = entity->getComp<SizeComponent>();
  auto newEntityPos = entity->getComp<InputMoveComponent>().inputMove(EntityPos.x, EntityPos.y, 0.0, 1.0, EntitySpeed.getSpeed());
  if (newEntityPos.second + EntitySize.height > 1080)
    return ;

  EntityPos.x = newEntityPos.first;
  EntityPos.y = newEntityPos.second;

  this->pushUpdate(entity, EntityPos.x, EntityPos.y, SolidRType::UDPData::COMMAND_TYPE::UPDATE_ELEMENT);
}

void InputSystem::Pause(std::shared_ptr<SolidEngine::AEntity> &entity){
}

void InputSystem::Quit(std::shared_ptr<SolidEngine::AEntity> &entity){

}

void InputSystem::shoot(std::shared_ptr<SolidEngine::AEntity> &entity){
  entity->getComp<GeneratorContainerComponent>().shoot(_mediator,
                                                       entity->getComp<PositionComponent>(),
                                                       entity->getComp<DirectionComponent>(),
                                                       entity->getComp<TeamComponent>());
}

