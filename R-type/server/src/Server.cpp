#include <stdexcept>
#include <experimental/filesystem>
#include <Id.hpp>
#include "Alias.hpp"
#include "Server.hpp"
#include "boost/bind.hpp"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_service &ioService, uint16_t port,
               std::list<SolidEngine::Sptr<IPlayer>> &clients,
               std::mutex &clientMutex,
               std::condition_variable &dataAvailable)
        : _dataAvailable(dataAvailable),
          _clientMutex(clientMutex),
          _acceptor(ioService, tcp::endpoint(tcp::v4(), port)), _end(false),
          _clients(clients),
          _context(ioService, boost::asio::ssl::context::sslv23) {
    if (!checkSSLFiles())
        throw std::runtime_error("Missing ssl files");
    _clientCheck = std::thread([this]() {
        try {
            std::unique_lock<std::mutex> lck(_clientMutex);
            while (_end == false) {
                _threadDeath.wait(lck);
                auto it = _clients.begin();
                while (it != _clients.end()) {
                    if ((*it) &&
                        std::static_pointer_cast<Session>(*it)->isDead()) {
                        SolidEngine::IntIDFactory::addUnusedId(
                                std::static_pointer_cast<Session>(*it)->getId());
                        std::cout << "Player [" << std::static_pointer_cast<Session>(*it)->getId()
                                  << "] disconnected" << std::endl;
                        it = _clients.erase(it);
                    }
                    else
                        ++it;
                }
            }
        }
        catch (std::exception const &e) {
            std::cerr << "Exception in thread clientCheck : " << e.what() << std::endl;
        }
    });
    _context.set_options(boost::asio::ssl::context::default_workarounds |
                         boost::asio::ssl::context::no_sslv2 |
                         boost::asio::ssl::context::single_dh_use);
    _context.use_certificate_chain_file("../R-type/Common/ssl_files/server.crt");
    _context.use_private_key_file("../R-type/Common/ssl_files/server.key",
                                  boost::asio::ssl::context::pem);
    _context.use_tmp_dh_file("../R-type/Common/ssl_files/dh512.pem");
    std::cout << "SSL context initialised" << std::endl;
    startAccept();
    std::cout << "Starting Acceptor" << std::endl;
}

Server::~Server() {
    _end.store(true);
    _threadDeath.notify_all();
    if (_clientCheck.joinable())
        _clientCheck.join();
}

void Server::startAccept() {
    Session::sessionPointer awaitingConnection =
            Session::create(_acceptor.get_io_service(), _context, _threadDeath,
                            _dataAvailable, _usernameHandler);
    _acceptor.async_accept(awaitingConnection->getSocket(),
                           boost::bind(&Server::handleAccept, this,
                                       awaitingConnection,
                                       boost::asio::placeholders::error));
}

void Server::handleAccept(Session::sessionPointer &newClient,
                          const boost::system::error_code &error) {
    if (!error) {
        newClient->start();
        _clients.push_back(newClient);
    }
    startAccept();
}

bool Server::checkSSLFiles() {
    return (std::experimental::filesystem::exists("../R-type/Common/ssl_files/server.crt") &&
            std::experimental::filesystem::exists("../R-type/Common/ssl_files/server.key") &&
            std::experimental::filesystem::exists("../R-type/Common/ssl_files/dh512.pem"));
}
