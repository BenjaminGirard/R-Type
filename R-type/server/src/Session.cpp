#include "Binary.hpp"
#include "Protocol.hpp"
#include "Id.hpp"
#include "Session.hpp"
#include "boost/bind.hpp"

Session::Session(boost::asio::io_service &ioService, uint64_t id,
                 boost::asio::ssl::context &context,
                 std::condition_variable &threadDeath,
                 std::condition_variable &dataAvailable,
                 UsernameHandler &usernameHandler)
        : _socket(ioService, context), _id(id), _buffer(Session::BUFFER_SIZE),
          _tmpPackage(Session::BUFFER_SIZE), _isDead(false), _writeReady(false),
          _threadDeath(threadDeath), _dataAvailable(dataAvailable), _usernameHandler(usernameHandler) {
    std::cout << "New Player [" << std::to_string(id) << "]" << std::endl;
}

Session::sessionPointer Session::create(boost::asio::io_service &ioService,
                                        boost::asio::ssl::context &context,
                                        std::condition_variable &threadDeath,
                                        std::condition_variable &dataAvailable,
                                        UsernameHandler &usernameHandler) {
    return sessionPointer(new Session(ioService, SolidEngine::IntIDFactory::getNextId(),
                                      context,
                                      threadDeath,
                                      dataAvailable,
                                      usernameHandler));
}

Session::ssl_socket::lowest_layer_type &Session::getSocket() {
    return (_socket.lowest_layer());
}

void Session::start() {
    _socket.async_handshake(boost::asio::ssl::stream_base::server,
                            boost::bind(&Session::handleHandshake, this,
                                        boost::asio::placeholders::error));
}

void Session::doRead() {
    boost::asio::async_read(_socket, boost::asio::buffer(_buffer, _buffer.size()),
                            boost::asio::transfer_at_least(1),
                            boost::bind(&Session::handleRead, shared_from_this(),
                                        boost::asio::placeholders::error));
}

void Session::doWrite(const std::vector<char> &data) {
    boost::asio::async_write(_socket, boost::asio::buffer(data),
                             boost::asio::transfer_at_least(1),
                             boost::bind(&Session::handleWrite, shared_from_this(),
                                         boost::asio::placeholders::error));
}

void Session::handleRead(const boost::system::error_code &error){
    if (!error) {
        _receivedData.push(_buffer);
        _dataAvailable.notify_all();
        doRead();
    }
    else
        notifyDeath();
}

void Session::handleWrite(const boost::system::error_code &error) {
    if (!error) {
        if (!_dataToSend.empty()) {
            _dataToSend.pop_front();
        }
    }
    else
        notifyDeath();
}

void Session::handleHandshake(const boost::system::error_code &error) {
    if (!error) {
        _writeReady = true;
        doRead();
        SolidRType::TcpPkg<uint64_t> tmp{SolidRType::TCPData::COMMAND_TYPE::USER_ID,
                                         getId()};
        std::vector<char> toSend(BUFFER_SIZE);
        toSend << tmp;
        sendData(toSend);
    }
    else if (!_isDead)
        notifyDeath();
}

bool Session::sendData(std::vector<char> const &data) {
    if (!_writeReady) {
        std::cout << "Couldnt write" << std::endl;
        return false;
    }
    std::cout << "Sending " << std::to_string(data[0])
              << " to player [" << _id  << "]" << std::endl;
    _dataToSend.push_back(data);
    doWrite(_dataToSend.back());
    return true;
}

std::queue<std::vector<char>> Session::receiveData() {
    std::queue<std::vector<char>> tmp = _receivedData;
    while (!_receivedData.empty())
        _receivedData.pop();
    return (tmp);
}

bool Session::dataAvailable() { return !_receivedData.empty(); }

bool Session::isDead() const { return _isDead; }

uint64_t Session::getId() const { return _id; }

std::string const &Session::getUsername() const { return _username; }

bool Session::isAuthentified() const { return !_username.empty(); }

bool Session::setUsername(std::string const &username) {
    if (!_usernameHandler.addUsername(username))
        return false;
    _username = username;
    return true;
}

void Session::notifyDeath() {
    if (!_username.empty())
        _usernameHandler.removeUsername(_username);
    _writeReady = false;
    _isDead = true;
    _threadDeath.notify_all();
}

