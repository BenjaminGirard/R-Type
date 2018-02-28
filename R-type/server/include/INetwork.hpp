#ifndef INETWORK_HPP_
#define INETWORK_HPP_

#include "IPlayer.hpp"
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <cstdint>
#include <condition_variable>

class INetwork {
public:
    virtual ~INetwork() = default;

    virtual void startServer(uint16_t port,
                             std::list<SolidEngine::Sptr<IPlayer>> &clients,
                             std::mutex &clientMutex,
                             std::condition_variable &dataAvailable) = 0;
};

#endif // INETWORK_HPP_
