//
// Created by jacquat on 17/01/18.
//

#ifndef ACTION_HPP_
# define ACTION_HPP_

namespace SolidEngine {

    enum Action {
        UNKOWN = -1,
        TEXT_ENTERED = 0,
        SELECTED,
        /* TCP CONNECTION ACTIONS */
        CONNECTIONTCP,
        NAME_AUTHORIZATION,
        ASK_ROOM_LIST,
        JOIN_ROOM_ID,
        JOIN_ROOM,
        CREATE_ROOM,
        LEAVE_ROOM,
        CHANGE_TO_UDP,
        UPDATE_ROOM,
        /* MENU ACTIONS */
        CREATE_CONNECTION_MENU,
        PROFILE_MENU,
        MENU,
        CREATE_MENU,
        JOIN_MENU,
        JOIN_MENU_PASSWORD,
        WAITING_ROOM_MENU,
        START_GAME,
        OPTION,
        QUIT,
        USER_INPUT,
        ADD_ELEMENT,
        UPDATE_ELEMENT,
        DELETE_ELEMENT,
        CHANGE_GAME_STATUS,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        PAUSE_INPUT,
        SHOOT
    };
}

#endif /* ACTION_HPP_ */
