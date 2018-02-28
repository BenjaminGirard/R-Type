#ifndef SESSION_HPP_
# define SESSION_HPP_

# include "IPlayer.hpp"
# include "Alias.hpp"
# include "boost/asio.hpp"
# include "boost/asio/ssl.hpp"
# include "UsernameHandler.hpp"
# include <condition_variable>
# include <iostream>
# include <list>
# include <memory>
# include <mutex>

class Session : public std::enable_shared_from_this<Session>, public IPlayer {
    typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;
    static const uint32_t BUFFER_SIZE = 8192;

    ssl_socket _socket;
    std::string _username;
    uint64_t _id;
    std::vector<char> _buffer;
    std::vector<char> _tmpPackage;
    bool _isDead;
    bool _writeReady;
    std::condition_variable &_threadDeath;
    std::condition_variable &_dataAvailable;
    UsernameHandler &_usernameHandler;
    std::queue<std::vector<char>> _receivedData;
    std::list<std::vector<char>> _dataToSend;

public:
    ~Session() = default;

    Session(const Session &cp) = delete;

    Session &operator=(const Session &cp) = delete;

    typedef SolidEngine::Sptr<Session> sessionPointer;

    static sessionPointer create(boost::asio::io_service &ioService,
                                 boost::asio::ssl::context &context,
                                 std::condition_variable &threadDeath,
                                 std::condition_variable &dataAvailable,
                                 UsernameHandler &usernameHandler);

    ssl_socket::lowest_layer_type &getSocket();

    void start();

    bool isDead() const override ;

    void notifyDeath();

    bool sendData(std::vector<char> const &data) override;

    std::queue<std::vector<char>> receiveData() override;

    uint64_t getId() const override;

    bool dataAvailable() override;

    bool isAuthentified() const override;

    bool setUsername(std::string const &) override;

    std::string const &getUsername() const override;

private:
    Session(boost::asio::io_service &ioService, uint64_t id,
            boost::asio::ssl::context &context,
            std::condition_variable &threadDeath,
            std::condition_variable &dataAvailable,
            UsernameHandler &usernameHandler);

    void doRead();

    void doWrite(const std::vector<char> &data);

    void handleRead(const boost::system::error_code &error);

    void handleWrite(const boost::system::error_code &error);

    void handleHandshake(const boost::system::error_code &error);
};

#endif // SESSION_HPP_
