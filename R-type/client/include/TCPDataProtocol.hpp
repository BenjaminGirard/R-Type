//
// Created by nicolas on 24/01/2018.
//

#ifndef CPP_RTYPE_TCPDATAPROTOCOL_HPP
#define CPP_RTYPE_TCPDATAPROTOCOL_HPP

# include <cstdint>
# include "Protocol.hpp"
# include "AComponent.hpp"

namespace SolidRType {

    namespace TCPData {
        class TCPDataProtocol {
        public:
            TCPDataProtocol() {
                _playerInfo.isPlayerReady = SolidRType::TCPData::CONFIRM::KO;
                for (int i = 0; i < sizeof(char[255]); i++) {
                    _create.password[i] = '\0';
                    _askJoin.password[i] = '\0';
                    _playerInfo.username[i] = '\0';
                }
            };
            ~TCPDataProtocol() = default;

            std::string     _host;
            std::string     _port;
            COMMAND_TYPE _cmd;
            CONFIRM   _cnf;
            REQUEST_LIMIT       _requestLimit;

            std::vector<RoomInfo>   _rooms;

            PlayerInfo   _playerInfo;
            CreateRoom   _create;
            AuthorizationCreateRoom _authCreate;
            AskJoinRoom  _askJoin;
        };
    }
}

#endif //CPP_RTYPE_TCPDATAPROTOCOL_HPP
