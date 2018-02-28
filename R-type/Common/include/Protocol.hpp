//
// Created by tetard on 16/01/18.
//

#ifndef CPP_RTYPE_PROTOCOL_H
#define CPP_RTYPE_PROTOCOL_H

#include <cstdint>

namespace SolidRType {
    /**
     * TCP connection for menu communication
     */
    namespace TCPData {
        enum COMMAND_TYPE : uint8_t {
            USER_ID = 0,
            USER_AUTHENTICATION_REQUEST,
            USER_CREATE_ROOM_REQUEST,
            USER_ASK_LIST_ROOM_REQUEST,
            ROOM_INFO,
            USER_ASK_JOIN_ROOM_REQUEST,
            USER_LEAVE_ROOM,
            USER_READY,
            START_GAME
        };

        enum CONFIRM : uint8_t {
            OK = 0,
            KO
        };

        enum REQUEST_LIMIT : uint8_t {
            BEGIN,
            END
        };

        struct PlayerInfo {
            uint64_t id;
            char username[256];
            CONFIRM isPlayerReady;
        };

        struct CreateRoom {
            uint8_t roomSize; // must be from 1 to 4
            char password[256]; // optional
        };

        struct RoomInfo {
            uint64_t roomId;
            CONFIRM isGameInProgress;
            uint8_t nbPlayersMax;
            uint8_t nbPlayersInRoom;
            PlayerInfo players[4];
        };

        struct AuthorizationCreateRoom {
            CONFIRM authorization;
            RoomInfo info;
        };

        struct AskJoinRoom {
            uint64_t roomId;
            char password[256];
        };

        /**
         * uint8_t USER_ID
         * uint64_t id
         */

        /**
         * (client side)
         * uint8_t USER_AUTHENTICATION_REQUEST
         * char username[256]
         */

        /**
         * (server side)
         * uint8_t USER_AUTHENTICATION_REQUEST
         * uint8_t AUTHORIZATION
         */

        /**
         * (client side)
         * uint8_t USER_ASK_LIST_ROOM_REQUEST
         */

        /**
         * (server side)
         * uint8_t USER_ASK_LIST_ROOM_REQUEST
         * REQUEST_LIMIT BEGIN / END
         */

        /**
         * (server side)
         * uint8_t ROOM_INFO
         * RoomInfo info
         * to be sent between BEGIN and END of USER_ASK_LIST_ROOM_REQUEST
         * to be sent when there is an update in a room (create, player joined, Game in progress, etc.)
         */

        /**
         * (client side)
         * uint8_t USER_CREATE_ROOM_REQUEST
         * uint8_t roomSize    | struct CreateRoom
         * char password[256]  |
         */

        /**
         * (server side)
         * uint8_t USER_CREATE_ROOM_REQUEST
         * AuthorizationCreateRoom info
         */ /* Player is automatically moved into the room */

        /**
         * (client side)
         * uint8_t USER_ASK_JOIN_ROOM_REQUEST
         * AskJoinRoom InfoRoomNeeded;
         */

        /**
         * (server side)
         * uint8_t USER_ASK_JOIN_ROOM_REQUEST
         * AUTHORIZATION
         */

        /**
         * (client side only)
         * uint8_t USER_LEAVE_ROOM
         * uint64_t id_room
         */

        /**
         * (client side only)
        * uint8_t USER_READY
        * CONFIRM
        */
    };


    /**
     * UDP connection for game.
     */
    namespace UDPData {
        enum COMMAND_TYPE : uint8_t {
            USER_INPUT,
            ADD_ELEMENT,
            UPDATE_ELEMENT,
            DELETE_ELEMENT,
            CHANGE_GAME_STATUS,
            PING
        };

        enum INPUT : uint8_t {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            PAUSE_INPUT,
            QUIT,
            SHOOT,
            NONE
         // ...
        };

        enum GAME_STATUS : uint8_t {
            PLAYING,
            PAUSE,
            GAME_OVER,
         // ...
        };


        struct PhysicalElementInfo {
            int32_t x;
            int32_t y;
            int64_t sizex;
            int64_t sizey;
        };

        struct MetaElementInfo {
            uint8_t isPlayer; // next variables are maybe useless if is not a player
            uint16_t level;
            uint8_t nbLives;
        };

        struct AddElementInfo {
            uint64_t elementId;
            char path[512];
            PhysicalElementInfo PhysicalInfo;
            MetaElementInfo metaInfo;
        };

        struct UpdateElementInfo {
            uint64_t elementId;
            PhysicalElementInfo PhysicalInfo;
            MetaElementInfo MetaInfo;
        };

        struct DeleteElementInfo {
            uint64_t elementId;
        };

        struct CommonClientHeader {
            COMMAND_TYPE CommandType;
            uint64_t clientId;
        };

        struct UserInput {
            CommonClientHeader Header;
            INPUT inputUser;
        };

        struct addElement {
            COMMAND_TYPE commandType;
            AddElementInfo info;
        };

        struct ChangeGameStatus {
            COMMAND_TYPE commandType;
            GAME_STATUS status;
        };

        struct PingPackage {};

    };

}
#endif //CPP_RTYPE_PROTOCOL_H
