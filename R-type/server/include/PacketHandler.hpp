//
// Created by matteo on 24/01/2018.
//

#ifndef CPP_RTYPE_PACKETHANDLER_HPP
#define CPP_RTYPE_PACKETHANDLER_HPP

#include <unordered_map>
#include <functional>
#include "IPlayer.hpp"
#include "RoomManager.hpp"

class PacketHandler {
    using Action = void (PacketHandler::*)(std::vector<char> &,
                                           SolidEngine::Sptr<IPlayer> const &);

    RoomManager _roomManager;
    std::unordered_map<uint8_t, Action> _actions;
    std::vector<char> _toSend;

public:
    PacketHandler();

    ~PacketHandler() = default;

    void handleRawData(std::vector<char> &data, SolidEngine::Sptr<IPlayer> const &player);

    static const uint32_t BUFFER_SIZE = 8192;
private:
    uint8_t getRequestId(std::vector<char> &data);

    void printReceivedAction(uint8_t requestId, uint64_t playerId);

    // Actions
    void userId(std::vector<char> &data,
                SolidEngine::Sptr<IPlayer> const &player);

    void authenticationRequest(std::vector<char> &data,
                               SolidEngine::Sptr<IPlayer> const &player);

    void listRoom(std::vector<char> &data,
                  SolidEngine::Sptr<IPlayer> const &player);

    void createRoom(std::vector<char> &data,
                    SolidEngine::Sptr<IPlayer> const &player);

    void joinRoom(std::vector<char> &data,
                  SolidEngine::Sptr<IPlayer> const &player);

    void leaveRoom(std::vector<char> &data,
                   SolidEngine::Sptr<IPlayer> const &player);

    void userReady(std::vector<char> &data,
                   SolidEngine::Sptr<IPlayer> const &player);
};


#endif //CPP_RTYPE_PACKETHANDLER_HPP
