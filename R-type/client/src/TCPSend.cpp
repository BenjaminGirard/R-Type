//
// Created by nicolas on 27/01/2018.
//
#include "NetworkTCPSystem.hpp"
/* Send Protocol Info */

void        SolidEngine::NetworkTCPSystem::sendAuthentificationRequest(const SolidRType::TCPData::PlayerInfo& _player) {
    SolidRType::TcpPkg<char[256]> tmp;
    std::vector<char> toSend(BUFFER_SIZE);

    tmp.pkg_id = SolidRType::TCPData::COMMAND_TYPE::USER_AUTHENTICATION_REQUEST;
    for (int i = 0; i < sizeof(char[255]); i++)
        tmp.data[i] = '\0';
    for (int i = 0; i < sizeof(char[255]); i++)
        tmp.data[i] = _player.username[i];
    std::cout << std::to_string(tmp.pkg_id) << std::endl;
    std::cout << tmp.data << std::endl;
    toSend << tmp;
    send(toSend);
}

void        SolidEngine::NetworkTCPSystem::sendCreateRoom(const SolidRType::TCPData::CreateRoom& room) {
    SolidRType::TcpPkg<SolidRType::TCPData::CreateRoom> tmp;
    std::vector<char> toSend(BUFFER_SIZE);

    tmp.pkg_id = SolidRType::TCPData::COMMAND_TYPE::USER_CREATE_ROOM_REQUEST;
    tmp.data.roomSize = room.roomSize;
    for (int i = 0; i < sizeof(char[255]); i++)
        tmp.data.password[i] = '\0';
    for (int i = 0; i < sizeof(char[255]); i++)
        tmp.data.password[i] = room.password[i];
    toSend << tmp;
    send(toSend);
}

void        SolidEngine::NetworkTCPSystem::sendJoinRoom(const SolidRType::TCPData::AskJoinRoom& room) {
    SolidRType::TcpPkg<SolidRType::TCPData::AskJoinRoom> tmp;
    std::vector<char> toSend(BUFFER_SIZE);

    tmp.pkg_id = SolidRType::TCPData::COMMAND_TYPE::USER_ASK_JOIN_ROOM_REQUEST;
    tmp.data.roomId = room.roomId;
    for (int i = 0; i < sizeof(char[255]); i++)
        tmp.data.password[i] = '\0';
    for (int i = 0; i < sizeof(char[255]); i++)
        tmp.data.password[i] = room.password[i];
    toSend << tmp;
    send(toSend);
}

void        SolidEngine::NetworkTCPSystem::sendAskForRoom() {
    SolidRType::TcpPkg<uint8_t>  askRoomInfo{SolidRType::TCPData::USER_ASK_LIST_ROOM_REQUEST, 0};
    std::vector<char> toSend(BUFFER_SIZE);

    toSend << askRoomInfo;
    send(toSend);
}

void        SolidEngine::NetworkTCPSystem::sendLeaveRoom(uint64_t roomId) {
    SolidRType::TcpPkg<uint64_t>  askRoomInfo{SolidRType::TCPData::USER_LEAVE_ROOM, roomId};// id of room
    std::vector<char> toSend(BUFFER_SIZE);

    toSend << askRoomInfo;
    send(toSend);
}

void        SolidEngine::NetworkTCPSystem::sendUserReady(SolidRType::TCPData::CONFIRM cnf) {
    SolidRType::TcpPkg<uint64_t>  ready{SolidRType::TCPData::USER_READY, cnf};
    std::vector<char> tosend(BUFFER_SIZE);

    tosend << ready;
    send(tosend);
}