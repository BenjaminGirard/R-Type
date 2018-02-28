//
// Created by matteo on 24/01/2018.
//

#ifndef CPP_RTYPE_ROOM_HPP
#define CPP_RTYPE_ROOM_HPP

#include <cstdint>
#include <list>
#include <cstring>
#include <thread>
#include <atomic>
#include "Protocol.hpp"
#include "Alias.hpp"
#include "Id.hpp"
#include "IPlayer.hpp"

class Room {
public:
    struct RoomPlayerInfo {
        uint64_t id;
        char username[256];
        SolidRType::TCPData::CONFIRM isPlayerReady;
        SolidEngine::Sptr<IPlayer> const &player;
//        std::string ip;
//        SolidEngine::Sptr<IPlayer> playerPtr;
    };
private:
    uint64_t _id;
    std::list<SolidEngine::Uptr<RoomPlayerInfo>> _players;
    uint8_t _roomSize;
    std::string _roomPwd;
    SolidRType::TCPData::CONFIRM _isGameRunning;
    std::thread _gameInstance;
    std::atomic<bool> _instanceIsRunning;

    void copyUsername(char (&dest)[256], std::string const &src);

    friend void operator<<(SolidRType::TCPData::PlayerInfo &dest, RoomPlayerInfo &src);

    void startGame();

public:
    explicit Room(uint8_t roomSize);

    Room(uint8_t roomSize, std::string const &pwd);

    ~Room();

    uint64_t getId() const { return _id; }

    uint8_t getRoomSize() const { return _roomSize; }

    uint8_t nbPlayers() const { return static_cast<uint8_t>(_players.size()); }

    bool hasPwd() const { return !_roomPwd.empty(); }

    std::list<SolidEngine::Uptr<RoomPlayerInfo>> const &getPlayers() const { return _players; }

    SolidRType::TCPData::CONFIRM isGameRunning() const { return _isGameRunning; }

    void getPlayersInfo(SolidRType::TCPData::PlayerInfo (&players)[4]);

    bool addPlayer(uint64_t id, std::string const &username,
                   std::string const &pwd, SolidEngine::Sptr<IPlayer> const &player);

    void removePlayer(uint64_t playerId);

    void tryStartGame();
};


#endif //CPP_RTYPE_ROOM_HPP
