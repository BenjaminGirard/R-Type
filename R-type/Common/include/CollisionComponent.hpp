//
// Created by tetard on 19/01/18.
//

#ifndef CPP_RTYPE_COLLISIONCOMPONENT_HPP
#define CPP_RTYPE_COLLISIONCOMPONENT_HPP

#include <queue>
#include "AComponent.hpp"
#include "Alias.hpp"
#include "AEntity.hpp"

class CollisionComponent : public SolidEngine::AComponent {
public:
    std::queue<SolidEngine::Sptr<SolidEngine::AEntity> > _collisionsEntity;

public:
    CollisionComponent() : AComponent(std::type_index(typeid(CollisionComponent))) {}

    ~CollisionComponent() override = default;

    void addCollisionEntity(const SolidEngine::Sptr<SolidEngine::AEntity> &e) {
      _collisionsEntity.push(e);
    }

    bool tryPop() {
        if (_collisionsEntity.empty())
            return false;
        _collisionsEntity.pop();
        return true;
    }

    //void removeCollisionEntity() { _collisionsEntity = nullptr; }
};

#endif //CPP_RTYPE_COLLISIONCOMPONENT_HPP
