//
// Created by nicolas on 22/01/2018.
//

#ifndef CPP_RTYPE_NETWORKTCPSYSTEM_HPP
#define CPP_RTYPE_NETWORKTCPSYSTEM_HPP

#include <iostream>
#include <thread>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <typeindex>
#include <ASystem.hpp>
#include <unordered_map>
#include <Protocol.hpp>
#include "Binary.hpp"
#include "TCPDataProtocol.hpp"
#include <ANetwork.hpp>

static const int    BUFFER_SIZE = 1024;

namespace SolidEngine {
    class NetworkTCPSystem : public ASystem, public ANetwork {
        typedef int(NetworkTCPSystem::*fnct)(std::vector<char>&);
        typedef std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socketSsl;
    private:
        boost::asio::io_service _io_service;
        std::unordered_map<SolidRType::TCPData::COMMAND_TYPE, fnct>    _receiveMode;


        SolidRType::TCPData::TCPDataProtocol _dataProtocol;

/*        std::string _port;
        std::string _host;*/
        socketSsl _client;
        bool        _isConnected;
        bool        _update;
    public:
        explicit NetworkTCPSystem(Sptr<Mediator> &mediator,
                                  boost::asio::io_service& io_service,
                                  boost::asio::ssl::context &context);
        ~NetworkTCPSystem() = default;

        void execute() override;

        void handle_handshake(const boost::system::error_code &error);
        void handle_connect(const boost::system::error_code &error);

        int send(const std::vector<char> &msg);
        int receive();
        int tryConnection();
        void resetConnection();
        bool disconnect();
        void run();

        void sendAuthentificationRequest(const SolidRType::TCPData::PlayerInfo &_player);
        void sendCreateRoom(const SolidRType::TCPData::CreateRoom &room);
        void sendJoinRoom(const SolidRType::TCPData::AskJoinRoom &room);
        void sendAskForRoom();
        void sendLeaveRoom(uint64_t roomId);
        void sendUserReady(SolidRType::TCPData::CONFIRM cnf);

        int receiveAuthentificationRequest(std::vector<char>& buf);
        int receiveUserID(std::vector<char>& buf);
        int receiveLaunchGame(std::vector<char>& buf);
        int receiveCreateRoom(std::vector<char>& buf);
        int receiveJoinRoom(std::vector<char>& buf);
        int receiveAskForRoom(std::vector<char>& buf);
        int receiveRoomInfo(std::vector<char>& buf);
    };
}
#endif //CPP_RTYPE_NETWORKTCPSYSTEM_HPP
