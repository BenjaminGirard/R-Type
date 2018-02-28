//
// Created by jacquat on 17/01/18.
//

#ifndef ONCLICKCOMPONENT_HPP_
#define ONCLICKCOMPONENT_HPP_

# include <cstdint>
#include "Action.hpp"
#include "AComponent.hpp"

namespace SolidEngine {
    enum    INPUT_ID : uint8_t {
        PORT = 1,
        IP,
        PLAYER_NAME,
        CREATE_ROOM_NB_PLAYER,
        CREATE_ROOM_PWD,
        JOIN_ROOM_PWD
    };

    class ClickableComponent : public AComponent {
    public:
        explicit ClickableComponent(Action action = Action::UNKOWN, int64_t id = -1)
                : AComponent(std::type_index(typeid(ClickableComponent))), _id(id)
        { _action = action; }
        int64_t _id;
        Action _action;
    };
}

#endif /* ONCLICKCOMPONENT_HPP_ */
