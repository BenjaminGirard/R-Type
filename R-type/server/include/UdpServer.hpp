//
// Created by pereira on 24/01/2018.
//

#ifndef CPP_RTYPE_UDPSERVER_HPP
#define CPP_RTYPE_UDPSERVER_HPP

# include <map>
# include <boost/asio.hpp>
# include <boost/bind.hpp>
# include <thread>
# include "ASystem.hpp"
# include "Binary.hpp"
# include "Protocol.hpp"

namespace SolidEngine {
    class UdpServer : public ASystem {
    public:
        UdpServer(Sptr<Mediator> &mediator, boost::asio::io_service &io_service, std::mutex &mutex, uint32_t nbPlayers);
        ~UdpServer() override;
        void execute() override;
    private:
        void start_receive();
        void handle_receive(const boost::system::error_code& error, std::size_t);


        void updateElem(int8_t IdPkg, int64_t Id);
        void delElem(int8_t IdPkg, int64_t Id);
        void UpdtInput(int8_t IdPkg, int64_t Id);
        void addElem(int8_t IdPkg, int64_t Id);
        void changeStatus(int8_t IdPkg, int64_t Id);

        void checkMessageComp();

        void send_to(std::vector<char>&, int64_t Id);
        void handle_send(const boost::system::error_code& ec, std::size_t);
        void check_sum_crc();
        void addPlayer(int64_t Id);
        void FindTypePkg(int8_t Id);

        //std::shared_ptr<SolidRType::UdpPkg> _pkg;
        boost::asio::io_service &_ioService;
        std::thread _t;
        boost::asio::ip::udp::socket _socket;
        std::map<int32_t, std::function<void(UdpServer &, int32_t, int64_t)>> _rcvFct;
        std::unordered_map<int64_t, boost::asio::ip::udp::endpoint> _players;
        boost::asio::ip::udp::endpoint _remote_endpoint;
        std::vector<char> _recv_buffer = std::vector<char>(1024);
        std::mutex &_mutex;

        uint32_t _nbPlayers;
        std::vector<SolidRType::UDPData::AddElementInfo> _newPlayersPackages;
    };
}

#endif //CPP_RTYPE_UDPSERVER_HPP
