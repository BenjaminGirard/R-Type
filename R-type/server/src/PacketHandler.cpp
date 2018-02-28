//
// Created by matteo on 24/01/2018.
//

#include <iostream>
#include <cstring>
#include "Protocol.hpp"
#include "Binary.hpp"
#include "PacketHandler.hpp"

PacketHandler::PacketHandler() :
        _actions({{SolidRType::TCPData::COMMAND_TYPE::USER_ID,
                          &PacketHandler::userId},
                  {SolidRType::TCPData::COMMAND_TYPE::USER_AUTHENTICATION_REQUEST,
                          &PacketHandler::authenticationRequest},
                  {SolidRType::TCPData::COMMAND_TYPE::USER_CREATE_ROOM_REQUEST,
                          &PacketHandler::createRoom},
                  {SolidRType::TCPData::COMMAND_TYPE::USER_ASK_LIST_ROOM_REQUEST,
                          &PacketHandler::listRoom},
                  {SolidRType::TCPData::COMMAND_TYPE::USER_ASK_JOIN_ROOM_REQUEST,
                          &PacketHandler::joinRoom},
                  {SolidRType::TCPData::COMMAND_TYPE::USER_LEAVE_ROOM,
                          &PacketHandler::leaveRoom},
                  {SolidRType::TCPData::COMMAND_TYPE::USER_READY,
                          &PacketHandler::userReady}}),
        _toSend(BUFFER_SIZE) {}

void PacketHandler::handleRawData(std::vector<char> &data,
                                  SolidEngine::Sptr<IPlayer> const &player) {
    uint8_t requestId = getRequestId(data);
    if (requestId != 255) {
        if (_actions.find(requestId) != _actions.end()) {
            printReceivedAction(requestId, player->getId());
            (this->*_actions[requestId])(data, player);
        }
    }
}

uint8_t PacketHandler::getRequestId(std::vector<char> &data) {
    uint8_t tmpId = 255;

    if (data.size() < sizeof(uint8_t))
        return (tmpId);
    std::memcpy(&tmpId, data.data(), sizeof(uint8_t));
    return tmpId;
}

void PacketHandler::printReceivedAction(uint8_t requestId, uint64_t playerId) {
    switch (requestId) {
        case SolidRType::TCPData::COMMAND_TYPE::USER_ID:
            std::cout << "Player [" << playerId << "] sent USER_ID" << std::endl;
            break;
        case SolidRType::TCPData::COMMAND_TYPE::USER_AUTHENTICATION_REQUEST:
            std::cout << "Player [" << playerId << "] sent USER_AUTHENTICATION_REQUEST" << std::endl;
            break;
        case SolidRType::TCPData::COMMAND_TYPE::USER_CREATE_ROOM_REQUEST:
            std::cout << "Player [" << playerId << "] sent USER_CREATE_ROOM_REQUEST" << std::endl;
            break;
        case SolidRType::TCPData::COMMAND_TYPE::USER_ASK_LIST_ROOM_REQUEST:
            std::cout << "Player [" << playerId << "] sent USER_ASK_LIST_ROOM_REQUEST" << std::endl;
            break;
        case SolidRType::TCPData::COMMAND_TYPE::USER_READY:
            std::cout << "Player [" << playerId << "] sent USER_READY" << std::endl;
            break;
        case SolidRType::TCPData::COMMAND_TYPE::ROOM_INFO:
            std::cout << "Player [" << playerId << "] sent ROOM_INFO" << std::endl;
            break;
        case SolidRType::TCPData::COMMAND_TYPE::USER_ASK_JOIN_ROOM_REQUEST:
            std::cout << "Player [" << playerId << "] sent USER_ASK_JOIN_ROOM_REQUEST" << std::endl;
            break;
        case SolidRType::TCPData::COMMAND_TYPE::USER_LEAVE_ROOM:
            std::cout << "Player [" << playerId << "] sent USER_LEAVE_ROOM" << std::endl;
            break;
        default:
            break;
    }
}

void PacketHandler::userId(std::vector<char> &data,
                           SolidEngine::Sptr<IPlayer> const &player) {
    SolidRType::TcpPkg<uint64_t> tmp{SolidRType::TCPData::COMMAND_TYPE::USER_ID,
                                     player->getId()};
    _toSend << tmp;
    player->sendData(_toSend);
}

void PacketHandler::authenticationRequest(std::vector<char> &data,
                                          SolidEngine::Sptr<IPlayer> const &player) {
    SolidRType::TcpPkg<char[256]> request;
    SolidRType::TcpPkg<uint8_t> tmp;

    request << data;
    tmp.pkg_id = SolidRType::TCPData::COMMAND_TYPE::USER_AUTHENTICATION_REQUEST;
    tmp.data = !player->setUsername(request.data) ?
               SolidRType::TCPData::CONFIRM::KO : SolidRType::TCPData::CONFIRM::OK;
    _toSend << tmp;
    player->sendData(_toSend);
}

void PacketHandler::listRoom(std::vector<char> &data, SolidEngine::Sptr<IPlayer> const &player) {
    SolidRType::TcpPkg<uint8_t> beginEnd{SolidRType::TCPData::COMMAND_TYPE::USER_ASK_LIST_ROOM_REQUEST,
                                         SolidRType::TCPData::REQUEST_LIMIT::BEGIN};
    SolidRType::TcpPkg<SolidRType::TCPData::RoomInfo> roomInfo{SolidRType::TCPData::COMMAND_TYPE::ROOM_INFO};

    _toSend << beginEnd;
    player->sendData(_toSend);
    std::list<SolidEngine::Uptr<Room>> const &rooms = _roomManager.getRooms();
    for (auto const &it : rooms) {
        roomInfo.data.roomId = it->getId();
        roomInfo.data.isGameInProgress = it->isGameRunning();
        roomInfo.data.nbPlayersInRoom = it->nbPlayers();
        roomInfo.data.nbPlayersMax = it->getRoomSize();
        it->getPlayersInfo(roomInfo.data.players);
        _toSend << roomInfo;
        player->sendData(_toSend);
    }
    beginEnd.data = SolidRType::TCPData::REQUEST_LIMIT::END;
    _toSend << beginEnd;
    player->sendData(_toSend);
}

void PacketHandler::createRoom(std::vector<char> &data, SolidEngine::Sptr<IPlayer> const &player) {
    SolidRType::TcpPkg<SolidRType::TCPData::CreateRoom> tmp;
    tmp << data;
    SolidEngine::Uptr<Room> const &room = _roomManager.createRoom(tmp.data.roomSize, tmp.data.password);
    SolidRType::TcpPkg<SolidRType::TCPData::AuthorizationCreateRoom> authorization
            {SolidRType::TCPData::USER_CREATE_ROOM_REQUEST,
             {_roomManager.addPlayerToRoom(player, room->getId(), tmp.data.password) ?
              SolidRType::TCPData::CONFIRM::OK : SolidRType::TCPData::CONFIRM::KO, {room->getId(),
                                                                                    room->isGameRunning(),
                                                                                    tmp.data.roomSize,
                                                                                    1}}};
    room->getPlayersInfo(authorization.data.info.players);
    _toSend << authorization;
    player->sendData(_toSend);
}

void PacketHandler::joinRoom(std::vector<char> &data, SolidEngine::Sptr<IPlayer> const &player) {
    SolidRType::TcpPkg<SolidRType::TCPData::AskJoinRoom> tmp;
    tmp << data;
    SolidRType::TcpPkg<SolidRType::TCPData::CONFIRM> authorization
            {SolidRType::TCPData::USER_ASK_JOIN_ROOM_REQUEST,
             _roomManager.addPlayerToRoom(player, tmp.data.roomId, tmp.data.password) ?
             SolidRType::TCPData::CONFIRM::OK : SolidRType::TCPData::CONFIRM::KO};
    _toSend << authorization;
    player->sendData(_toSend);
}

void PacketHandler::leaveRoom(std::vector<char> &data, SolidEngine::Sptr<IPlayer> const &player) {
    SolidRType::TcpPkg<uint64_t> tmp;
    tmp << data;
    _roomManager.removePlayerFromRoom(tmp.data, player->getId());
}

void PacketHandler::userReady(std::vector<char> &data, SolidEngine::Sptr<IPlayer> const &player) {
    SolidRType::TcpPkg<SolidRType::TCPData::CONFIRM> tmp;
    tmp << data;
    _roomManager.setPlayerStatus(player->getId(), tmp.data);
}

