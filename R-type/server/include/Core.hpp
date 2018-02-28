//
// Created by matteo on 21/01/18.
//

#ifndef CPP_RTYPE_CORE_HPP
#define CPP_RTYPE_CORE_HPP


#include <cstdint>
#include <mutex>
#include "PacketHandler.hpp"
#include "BoostServer.hpp"
#include "Alias.hpp"
#include "IPlayer.hpp"

class Core {
    uint16_t _port;
    PacketHandler _packerHandler;
    std::mutex _serverMutex;
    std::mutex _dataMutex;
    std::list<SolidEngine::Sptr<IPlayer>> _players;
    SolidEngine::Uptr<INetwork> _network;

public:
    explicit Core(uint16_t port);

    ~Core() = default;

    void start();

    static std::condition_variable dataAvailable;
    static bool isRunning;
private:
    Core(const Core &) = delete;

    Core &operator=(const Core &) = delete;
};


#endif //CPP_RTYPE_CORE_HPP
