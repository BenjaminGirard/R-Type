//
// Created by jacquat on 17/01/18.
//

#ifndef QUITSYSTEM_HPP_
#define QUITSYSTEM_HPP_

# include "ASystem.hpp"
# include "ActionComponent.hpp"

namespace SolidEngine {

    class QuitSystem : public ASystem {
    public:
        explicit QuitSystem(Sptr<Mediator> &mediator) : ASystem(mediator) {
            _requiredComp.emplace_back(std::type_index(typeid(ActionComponent)));
        }
        void execute() override {
            for(auto const& entity: _entityVec) {
                auto &actionComponent = entity->getComp<ActionComponent>();
                if (actionComponent._action == QUIT)
                    _mediator->stop();
            }
            while (!_entityVec.empty())
                _mediator->pingDeleteEntity(_entityVec.back().get());
        }
    };
}

#endif /* QUITSYSTEM_HPP_ */
