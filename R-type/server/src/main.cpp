#include <iostream>
#include <csignal>
#include <condition_variable>
#include <Manager.hpp>
#include "Core.hpp"

bool Core::isRunning = true;
std::condition_variable Core::dataAvailable;

int main(int argc, char *argv[]) {
  std::signal(SIGINT, [](int signum) {
      Core::isRunning = false;
      Core::dataAvailable.notify_all();
  });
  if (argc != 2) {
    std::cerr << "Usage : ./rtype_server [port]" << std::endl;
    return 1;
  }
  try {
    Core core(static_cast<uint16_t>(std::stoi(argv[1])));
    core.start();
  }
  catch (std::exception const &e) {
    std::cerr << "Catched error in Core : " << e.what() << std::endl;
  }

//    std::signal(SIGINT, [](int signum){ Core::isRunning = false; Core::dataAvailable.notify_all(); });
//    if (argc != 2)
//    {
//        std::cerr << "Usage : ./rtype_server [port]" << std::endl;
//        return 1;
//    }
//    try
//    {
//        Core core(static_cast<uint16_t>(std::stoi(argv[1])));
//        core.start();
//    }
//    catch (std::exception const &e)
//    {
//        std::cerr << "Catched error in Core : " << e.what() << std::endl;
//    }
    return 0;
}
