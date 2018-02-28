//
// Created by matteo on 24/01/2018.
//

#include <algorithm>
#include <Binary.hpp>
#include <PacketHandler.hpp>
#include <GameInstance.hpp>

Room::Room(uint8_t roomSize) :
        _id(SolidEngine::IntIDFactory::getNextId()), _roomSize(roomSize),
        _isGameRunning(SolidRType::TCPData::CONFIRM::KO),
        _instanceIsRunning(false) {}

Room::Room(uint8_t roomSize, std::string const &pwd) :
        _id(SolidEngine::IntIDFactory::getNextId()),
        _roomSize(roomSize), _roomPwd(pwd),
        _isGameRunning(SolidRType::TCPData::CONFIRM::KO),
        _instanceIsRunning(false) {}

Room::~Room() {
    _instanceIsRunning.store(false);
    if (_gameInstance.joinable())
        _gameInstance.join();
}

bool Room::addPlayer(uint64_t id, std::string const &username, std::string const &pwd,
                     SolidEngine::Sptr<IPlayer> const &player) {
    if (_players.size() >= _roomSize)
        return false;
    if (!_roomPwd.empty())
        if (pwd != _roomPwd)
            return false;
    RoomPlayerInfo tmp{id, "", SolidRType::TCPData::CONFIRM::KO, player};
    copyUsername(tmp.username, username);
    _players.push_back(std::make_unique<RoomPlayerInfo>
                               (tmp));
    return true;
}

void Room::getPlayersInfo(SolidRType::TCPData::PlayerInfo (&players)[4]) {
    uint8_t i = 0;
    for (auto const &it : _players) {
        players[i] << (*it);
        ++i;
    }
}

void Room::removePlayer(uint64_t playerId) {
    _players.erase(std::remove_if(_players.begin(), _players.end(),
                                  [&](SolidEngine::Uptr<RoomPlayerInfo> const &player) {
                                      return player->id == playerId;
                                  }));
}

void operator<<(SolidRType::TCPData::PlayerInfo &dest, Room::RoomPlayerInfo &src) {
    std::memcpy(&dest, &src, sizeof(SolidRType::TCPData::PlayerInfo));
}

void Room::copyUsername(char (&dest)[256], std::string const &src) {
    uint32_t i = 0;
    for (auto &it : src) {
        dest[i] = it;
        ++i;
    }
    dest[i] = 0;
}

void Room::tryStartGame() {
    if (_players.size() == _roomSize) {
        for (auto const &it : _players) {
            if (it->isPlayerReady == SolidRType::TCPData::CONFIRM::KO)
                return;
        }
        if (_isGameRunning == SolidRType::TCPData::CONFIRM::KO)
            startGame();
    }
}

void Room::startGame() {
    std::vector<uint64_t> playersId(_players.size());
    uint64_t i = 0;
    for (auto const &it : _players)
        if (!it->player->isDead())
        {
            SolidRType::TcpPkg<SolidRType::TCPData::COMMAND_TYPE> tmp
                    {SolidRType::TCPData::START_GAME, SolidRType::TCPData::START_GAME};
            std::vector<char> toSend(PacketHandler::BUFFER_SIZE);
            toSend << tmp;
            it->player->sendData(toSend);
            playersId[i] = it->id;
            ++i;
        }
    if (_gameInstance.joinable())
        _gameInstance.join();
    _isGameRunning = SolidRType::TCPData::CONFIRM::OK;
    _instanceIsRunning.store(true);
    _gameInstance =
            std::thread([](uint64_t roomId,
                           std::vector<uint64_t> const &playersId,
                           std::atomic<bool> &isInstanceRunning) {
                std::cout << "Lauching Game in room " << roomId << std::endl;
                std::vector<uint64_t> playersIdLocal(playersId);
                GameInstance gameInstance(playersIdLocal);
                while (isInstanceRunning.load())
                {
                    if (!gameInstance.isInstanceRunning())
                        isInstanceRunning.store(false);
                    gameInstance.executeSystems();
                }
            }, _id, playersId, std::ref(_instanceIsRunning));
}
