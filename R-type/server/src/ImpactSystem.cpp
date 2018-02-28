#include <GameInstance.hpp>
#include "ImpactSystem.hpp"
#include "CollisionComponent.hpp"
#include "LifeComponent.hpp"
#include "PowerComponent.hpp"
#include "TeamComponent.hpp"

ImpactSystem::ImpactSystem(const std::shared_ptr<SolidEngine::Mediator> &mediator)
    : ASystem(mediator)
{
    _requiredComp = {
        std::type_index(typeid(CollisionComponent)),
        std::type_index(typeid(LifeComponent)),
        std::type_index(typeid(PowerComponent)),
        std::type_index(typeid(TeamComponent))
    };
}

void ImpactSystem::execute(void) {
    for (auto &it : _entityVec) {
        auto &colComp = it->getComp<CollisionComponent>();
        if (!colComp._collisionsEntity.empty()) {
            auto &powComp = it->getComp<PowerComponent>();
            while (!colComp._collisionsEntity.empty()) {
                auto &Other = colComp._collisionsEntity.front();
                auto &lifeOther = Other->getComp<LifeComponent>();
                if (it->getComp<TeamComponent>().getTeam() != Other->getComp<TeamComponent>().getTeam())
                    lifeOther.takeDmg(powComp.getPower());
                colComp.tryPop();
            }
        }
    }
}