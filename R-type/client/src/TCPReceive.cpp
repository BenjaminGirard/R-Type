//
// Created by nicolas on 27/01/2018.
//

#include "NetworkTCPSystem.hpp"

/* Receive Protocol Info */

int        SolidEngine::NetworkTCPSystem::receiveAuthentificationRequest(std::vector<char>& buf) {
    uint8_t auth = static_cast<uint8_t>(buf[1]);
    std::cout << "USER_AUTHENTICATION_REQUEST " << std::to_string(auth) << std::endl;

    return auth;
}

int        SolidEngine::NetworkTCPSystem::receiveUserID(std::vector<char>& buf) {
    _dataProtocol._playerInfo.id = static_cast<uint64_t>(buf[1]);
    setId(_dataProtocol._playerInfo.id);
    std::cout << "USER_ID " << std::to_string(_dataProtocol._playerInfo.id) << std::endl;
    return 0;
}

int        SolidEngine::NetworkTCPSystem::receiveCreateRoom(std::vector<char>& buf) {
    SolidRType::TcpPkg<SolidRType::TCPData::AuthorizationCreateRoom> auth;

    auth << buf;
    _dataProtocol._authCreate = auth.data;
    std::cout << "USER_CREATE_ROOM_REQUEST" << std::endl;

    std::cout << _dataProtocol._authCreate.authorization << std::endl;
    std::cout << std::to_string(_dataProtocol._authCreate.info.nbPlayersMax) << std::endl;
    std::cout << std::to_string(_dataProtocol._authCreate.info.nbPlayersMax) << std::endl;


    return 0;
}

int        SolidEngine::NetworkTCPSystem::receiveJoinRoom(std::vector<char>& buf) {
    uint8_t auth = static_cast<uint8_t>(buf[1]);
    std::cout << "USER_ASK_JOIN_ROOM_REQUEST" << std::endl;

    return auth;
}

int        SolidEngine::NetworkTCPSystem::receiveRoomInfo(std::vector<char>& buf) {
    SolidRType::TcpPkg<SolidRType::TCPData::RoomInfo> room;

    room << buf;
    _dataProtocol._rooms.push_back(room.data);
    std::cout << "ROOM_INFO" << std::endl;
    return receive();
}

int        SolidEngine::NetworkTCPSystem::receiveAskForRoom(std::vector<char>& buf) {
    std::cout << "USER_ASK_LIST_ROOM_REQUEST" << std::endl;

    if (static_cast<uint8_t>(buf[1]) == SolidRType::TCPData::REQUEST_LIMIT::BEGIN) {
        _dataProtocol._rooms.clear();
        std::cout << "BEGIN" << std::endl;
        return receive();
    }
    if (static_cast<uint8_t>(buf[1]) == SolidRType::TCPData::REQUEST_LIMIT::END) {
        std::cout << "END" << std::endl;
        return 0;
    }
    return 0;
}

int        SolidEngine::NetworkTCPSystem::receiveLaunchGame(std::vector<char>& buf) {
    return static_cast<uint8_t>(buf[0]);
}
