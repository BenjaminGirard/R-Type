//
// Created by jacquat on 25/01/18.
//

#ifndef RECEIVERSYSTEM_HPP_
#define RECEIVERSYSTEM_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/optional.hpp>
#include <thread>
#include "ASystem.hpp"
#include "ANetwork.hpp"

namespace SolidEngine {

    class UDPSystem : public ASystem, public ANetwork {
    public:
        explicit UDPSystem(Sptr<Mediator> &mediator, boost::asio::io_service &io_service, std::mutex &mutex);
        ~UDPSystem() override;
        void execute() override;

    private:
        void startReceive();
        void handleReceive(const boost::system::error_code& error, std::size_t);
        void handleSend(const boost::system::error_code& ec,
                    std::size_t bytes_transferred);

        void connect();
    private:

        std::map<SolidEngine::Action, SolidRType::UDPData::INPUT> _input;
        std::map<uint8_t, std::function<void(UDPSystem &)>> _action;

        uint64_t _id;

        void addElement();
        void updateElement();
        void deleteElement();
        void changeGameStatus();

        AEntity &findEntityServerId(uint64_t sid) const;

        boost::asio::ip::udp::socket _socket;
        boost::asio::io_service &_io_service;
        boost::asio::ip::udp::endpoint _remote_endpoint;
        std::vector<char> _data = std::vector<char>(1024);
        std::thread _t;
        std::mutex &_mutex;
    };
}
#endif /* RECEIVERSYSTEM_HPP_ */
