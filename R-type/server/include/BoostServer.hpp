#ifndef BOOSTSERVER_HPP_
#define BOOSTSERVER_HPP_

#include "Alias.hpp"
#include "INetwork.hpp"
#include "Server.hpp"
#include "boost/asio.hpp"

class BoostServer : public INetwork {
    boost::asio::io_service _ioService;
    SolidEngine::Uptr<Server> _server;
    std::thread _running;

public:
    BoostServer() = default;

    ~BoostServer() override;

    void startServer(uint16_t port,
                     std::list<SolidEngine::Sptr<IPlayer>> &clients,
                     std::mutex &clientMutex,
                     std::condition_variable &dataAvailable) override;

private:
    BoostServer(const BoostServer &cp) = delete;

    BoostServer &operator=(const BoostServer &cp) = delete;
};

#endif // BOOSTSERVER_HPP_
