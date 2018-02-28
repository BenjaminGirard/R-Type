//
// Created by tetard on 19/01/18.
//

#ifndef CPP_RTYPE_COLLISIONSYSTEM_HPP
#define CPP_RTYPE_COLLISIONSYSTEM_HPP

#include <ASystem.hpp>
#include "PositionComponent.hpp"
#include "SizeComponent.hpp"
#include "CollisionComponent.hpp"

class CollisionSystem : public SolidEngine::ASystem {
public:
    CollisionSystem(const std::shared_ptr<SolidEngine::Mediator> &mediator) : ASystem(mediator) {
      _requiredComp = {
              std::type_index(typeid(PositionComponent)),
              std::type_index(typeid(SizeComponent)),
              std::type_index(typeid(CollisionComponent))
      };
    }

    ~CollisionSystem() override = default;

    void execute() override {
      for (auto &me : _entityVec) {
        auto myPos = me->getComp<PositionComponent>();
        auto mySize = me->getComp<SizeComponent>();
        for (auto &other : _entityVec) {
          if (me->getId() == other->getId())
            continue ;
          auto otherPos = other->getComp<PositionComponent>();
          auto otherSize = other->getComp<SizeComponent>();
          if (myPos.x < otherPos.x + otherSize.width &&
              myPos.x + mySize.width > otherPos.x &&
              myPos.y < otherPos.y + otherSize.height &&
              mySize.height + myPos.y > otherPos.y)
            me->getComp<CollisionComponent>().addCollisionEntity(other);
        }
      }
    }
};

#endif //CPP_RTYPE_COLLISIONSYSTEM_HPP
