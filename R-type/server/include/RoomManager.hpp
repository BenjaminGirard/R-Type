//
// Created by matteo on 24/01/2018.
//

#ifndef CPP_RTYPE_ROOMMANAGER_HPP
#define CPP_RTYPE_ROOMMANAGER_HPP

#include <list>
#include "Alias.hpp"
#include "Room.hpp"

class RoomManager {
    std::list<SolidEngine::Uptr<Room>> _rooms;

public:
    RoomManager() = default;

    ~RoomManager() = default;

    RoomManager(RoomManager const &) = delete;

    RoomManager &operator=(RoomManager const &) = delete;

    std::list<SolidEngine::Uptr<Room>> const &getRooms() const { return _rooms; }

    bool addPlayerToRoom(SolidEngine::Sptr<IPlayer> const &player,
                         uint64_t roomId, std::string const &pwd);

    SolidEngine::Uptr<Room> const &createRoom(uint8_t roomSize, std::string const &pwd);

    void removePlayerFromRoom(uint64_t roomId, uint64_t playerId);

    void setPlayerStatus(uint64_t playerId, SolidRType::TCPData::CONFIRM status);
};


#endif //CPP_RTYPE_ROOMMANAGER_HPP
