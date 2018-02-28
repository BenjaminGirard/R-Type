//
// Created by matteo on 30/01/18.
//

#include <mutex>
#include <System/InputSystem.hpp>
#include <System/CollisionSystem.hpp>
#include <System/ImpactSystem.hpp>
#include <System/MonsterGeneratorSystem.hpp>
#include <System/DeathSystem.hpp>
#include <System/AutoMoveSystem.hpp>
#include <UdpServer.hpp>
#include "GameInstance.hpp"

GameInstance::GameInstance(std::vector<uint64_t> const &playersId) {
  _manager.addSystem<CollisionSystem>();
  //_manager.addSystem<AutoMoveSystem>();
  //_manager.addSystem<ImpactSystem>();
  _manager.addSystem<InputSystem>();
  //_manager.addSystem<MonsterGeneratorSystem>();
  //_manager.addSystem<DeathSystem>();
  _manager.addSystem<SolidEngine::UdpServer>(_ioService, GameInstance::mutex, playersId.size());
}

void GameInstance::executeSystems() {
    if (_manager.isRunning())
    {
        mutex.lock();
        _manager.executeSystems();
        mutex.unlock();
    }
}

bool GameInstance::isInstanceRunning() {
    return _manager.isRunning();
}
