#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <atomic>
#include <list>
#include <mutex>
#include <thread>
#include "Session.hpp"
#include "UsernameHandler.hpp"

class Server {
    std::condition_variable _threadDeath;
    std::condition_variable &_dataAvailable;
    std::mutex &_clientMutex;
    boost::asio::ip::tcp::acceptor _acceptor;
    std::atomic<bool> _end;
    std::thread _clientCheck;
    std::list<SolidEngine::Sptr<IPlayer>> &_clients;
    boost::asio::ssl::context _context;
    UsernameHandler _usernameHandler;

public:
    Server(boost::asio::io_service &ioService, uint16_t port,
           std::list<SolidEngine::Sptr<IPlayer>> &clients, std::mutex &clientMutex,
           std::condition_variable &dataAvailable);

    ~Server();

private:
    Server(const Server &cp) = delete;

    Server &operator=(const Server &cp) = delete;

    void startAccept();

    void handleAccept(Session::sessionPointer &newClient,
                      const boost::system::error_code &error);

    bool checkSSLFiles();
};

#endif // SERVER_HPP_
