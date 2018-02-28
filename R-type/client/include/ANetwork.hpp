//
// Created by nicolas on 30/01/2018.
//

#ifndef CPP_RTYPE_ANETWORK_HPP
#define CPP_RTYPE_ANETWORK_HPP

//#include "ASystem.hpp"
#include <string>

namespace SolidEngine {
    enum NetworkType {
        TCP = 0,
        UDP
    };

    class ANetwork {
    private:
        inline static NetworkType _net;
        inline static std::string _port;
        inline static std::string _host;
        inline static uint64_t _id;

    public:
        ANetwork() {};

        virtual ~ANetwork() = default;

        ANetwork(const ANetwork &cp) = delete;

        NetworkType getNetworkType() const { return (_net); }

        const std::string &getPort() const { return (_port); }

        const std::string &getHost() const { return (_host); }

        uint64_t getServerId() const { return _id; }

        void setNetworkType(NetworkType net) { _net = net; }

        void setPort(const std::string &port) { _port = port; }

        void setId(uint64_t id) { _id = id; }

        void setHost(const std::string &host) { _host = host; }
    };
}
#endif //CPP_RTYPE_ANETWORK_HPP
