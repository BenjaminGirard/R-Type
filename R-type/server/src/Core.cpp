//
// Created by matteo on 21/01/18.
//

#include "Core.hpp"

Core::Core(uint16_t port) :
        _port(port),
        _network(new BoostServer) {
}

void Core::start() {
    std::unique_lock<std::mutex> newData(_dataMutex);

    _network->startServer(_port, _players, _serverMutex, dataAvailable);
    while (isRunning) {
        dataAvailable.wait(newData);
        _serverMutex.lock();
        try {
            for (auto &it : _players) {
                if (it->dataAvailable()) {
                    std::queue<std::vector<char>> tmpDataStack = it->receiveData();
                    while (!tmpDataStack.empty()) {
                        _packerHandler.handleRawData(tmpDataStack.front(), it);
                        tmpDataStack.pop();
                    }
                }
            }
        }
        catch (std::exception const &error) {
            std::cerr << "Error in room managing: " << error.what() << std::endl;
        }
        _serverMutex.unlock();
    }
}