#include <Component/GeneratorContainerComponent.hpp>
#include <GameInstance.hpp>
#include "DeathSystem.hpp"
#include "LifeComponent.hpp"
#include "SizeComponent.hpp"
#include "Rtype.hpp"
#include "PositionComponent.hpp"

DeathSystem::DeathSystem(const std::shared_ptr<SolidEngine::Mediator> &mediator) 
    : ASystem(mediator)
{
    _requiredComp = {
        std::type_index(typeid(LifeComponent)),
        std::type_index(typeid(SizeComponent)),
        std::type_index(typeid(PositionComponent))
    };
}

void DeathSystem::execute(void) {
  for (auto &it : _entityVec) {
      auto &lifeComp = it->getComp<LifeComponent>();
      auto &PosComp = it->getComp<PositionComponent>();
      auto &SizeComp = it->getComp<SizeComponent>();
      if ((lifeComp.getLife() <= 0 && lifeComp.getShield() == 0) ||
          !(PosComp.x < 1920 && PosComp.x + SizeComp.width > 0 && PosComp.y < 1080 && SizeComp.height + PosComp.y > 0)) {
          _mediator->pingDeleteEntity(&(*it));
          return execute();
        }
    }
}