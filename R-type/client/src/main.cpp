#include "PositionComponent.hpp"
#include "Client.hpp"
#include "SizeComponent.hpp"
#include "GraphicComponent.hpp"
#include <csignal>
#include <UDPSystem.hpp>

int main()
{
    try {
        SolidEngine::Manager manager;
        std::mutex mutex;

        auto &eventSys = manager.addSystem<SolidEngine::EventSystem>();

      eventSys.addEvent(SolidEngine::Event::KEY_ESC, SolidEngine::Action::QUIT);
      eventSys.addEvent(SolidEngine::Event::KEY_UP, SolidEngine::Action::UP);
      eventSys.addEvent(SolidEngine::Event::KEY_DOWN, SolidEngine::Action::DOWN);
      eventSys.addEvent(SolidEngine::Event::KEY_LEFT, SolidEngine::Action::LEFT);
      eventSys.addEvent(SolidEngine::Event::KEY_RIGHT, SolidEngine::Action::RIGHT);
      eventSys.addEvent(SolidEngine::Event::KEY_SPACE, SolidEngine::Action::SHOOT);
      boost::asio::io_service io_service;
      boost::asio::ssl::context context(boost::asio::ssl::context_base::sslv23);
      context.load_verify_file("../R-type/Common/ssl_files/server.crt");

      manager.addSystem<SolidEngine::NetworkTCPSystem>(io_service, context);
      manager.addSystem<SolidEngine::UDPSystem>(io_service, mutex);
      manager.addSystem<SolidEngine::MenuSystem>();
      manager.addSystem<SolidEngine::GraphicSystem>();
      manager.addSystem<SolidEngine::QuitSystem>();

      while (manager.isRunning()) {
        mutex.lock();
        manager.executeSystems();
        mutex.unlock();
      }
      io_service.stop();
    } catch (std::exception &e) { std::cout << "Error in main : " << e.what() << std::endl; }

}
