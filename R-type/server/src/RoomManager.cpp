//
// Created by matteo on 24/01/2018.
//

#include <algorithm>
#include "RoomManager.hpp"

SolidEngine::Uptr<Room> const &RoomManager::createRoom(uint8_t roomSize, std::string const &pwd) {
    if (!pwd.empty())
        _rooms.push_back(std::make_unique<Room>(roomSize, pwd));
    else
        _rooms.push_back(std::make_unique<Room>(roomSize));
    std::cout << "Creating room size [" << std::to_string(roomSize) << "] pwd ["
              << pwd << "] id [" << _rooms.back()->getId() << "]" << std::endl;
    return (_rooms.back());
}

bool RoomManager::addPlayerToRoom(SolidEngine::Sptr<IPlayer> const &player, uint64_t roomId,
                                  std::string const &pwd) {
    auto const &it = std::find_if(_rooms.begin(), _rooms.end(), [&](SolidEngine::Uptr<Room> const &room) {
        return room->getId() == roomId;
    });
    if (it == _rooms.end())
        return false;
    return (*it)->addPlayer(player->getId(), player->getUsername(), pwd, player);
}

void RoomManager::removePlayerFromRoom(uint64_t roomId, uint64_t playerId) {
    auto const &it = std::find_if(_rooms.begin(), _rooms.end(), [&](SolidEngine::Uptr<Room> const &room) {
        return room->getId() == roomId;
    });
    if (it != _rooms.end())
    {
        (*it)->removePlayer(playerId);
        if ((*it)->nbPlayers() == 0)
        {
            std::cout << "Removing room with id [" << (*it)->getId() << "]" << std::endl;
            _rooms.erase(it);
        }
    }
}

void RoomManager::setPlayerStatus(uint64_t playerId, SolidRType::TCPData::CONFIRM status) {
    for (auto const &room : _rooms) {
        std::list<SolidEngine::Uptr<Room::RoomPlayerInfo>> const &players = room->getPlayers();
        for (auto const &it : players) {
            if (it->id == playerId) {
                it->isPlayerReady = status;
                room->tryStartGame();
                break;
            }
        }
    }
}