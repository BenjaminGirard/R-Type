#include "BoostServer.hpp"

BoostServer::~BoostServer() {
    _ioService.stop();
    if (_running.joinable())
        _running.join();
}

void BoostServer::startServer(unsigned short port,
                              std::list<SolidEngine::Sptr<IPlayer>> &clients,
                              std::mutex &clientMutex,
                              std::condition_variable &dataAvailable) {
    std::cout << "Allocating Server" << std::endl;
    _server = std::make_unique<Server>(_ioService, port, clients,
                                       clientMutex, dataAvailable);
    std::cout << "Starting ioservice thread" << std::endl;
    _running = std::thread([this]() {
        try {
            _ioService.run();
        }
        catch (std::exception const &error) {
            std::cerr << "Exception in thread ioService : " << error.what() << std::endl;
        }
    });
}
