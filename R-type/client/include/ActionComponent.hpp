//
// Created by jacquat on 17/01/18.
//

#ifndef EVENTCOMPONENT_HPP_
# define EVENTCOMPONENT_HPP_

# include <cstdint>
# include <any>
# include "Action.hpp"
# include "AComponent.hpp"
# include "Protocol.hpp"

namespace SolidEngine {

    class ActionComponent : public AComponent {
    public:
        explicit ActionComponent(Action action = Action::UNKOWN, std::any data = nullptr)
                : AComponent(std::type_index(typeid(ActionComponent))), _data(std::move(data))
        { _action = action; }
        Action _action;
        std::any _data;
    };
}
#endif /* EVENTCOMPONENT_HPP_ */
