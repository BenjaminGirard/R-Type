//
// Created by matteo on 30/01/18.
//

#ifndef CPP_RTYPE_GAMEINSTANCE_HPP
#define CPP_RTYPE_GAMEINSTANCE_HPP


#include <cstdint>
#include <vector>
#include <mutex>
#include <Manager.hpp>
#include "boost/asio.hpp"

class GameInstance {
    boost::asio::io_service _ioService;
    SolidEngine::Manager _manager;

public:
    inline static std::mutex mutex;

    explicit GameInstance(std::vector<uint64_t> const &playersId);
    ~GameInstance() = default;

    void executeSystems();
    bool isInstanceRunning();
};


#endif //CPP_RTYPE_GAMEINSTANCE_HPP
