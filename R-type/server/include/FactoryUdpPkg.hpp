//
// Created by pereira on 26/01/2018.
//

#ifndef CPP_RTYPE_FACTORYUDPPKG_HPP
#define CPP_RTYPE_FACTORYUDPPKG_HPP


#include <cstdint>
#include <functional>
#include <map>
#include <Binary.hpp>
#include <Protocol.hpp>

namespace SolidRType {
    class FactoryUdpPkg {
    public:
        FactoryUdpPkg()
        : _list_pkg({
            {UDPData::UPDATE_ELEMENT, &FactoryUdpPkg::RetUpdateElementInfo},
            {UDPData::DELETE_ELEMENT ,&FactoryUdpPkg::RetDeleteElementInfo},
            {UDPData::USER_INPUT ,&FactoryUdpPkg::RetUserInput},
            {UDPData::ADD_ELEMENT ,&FactoryUdpPkg::RetaddElement},
            {UDPData::CHANGE_GAME_STATUS ,&FactoryUdpPkg::RetChangeGameStatus}
        }){}

        std::shared_ptr<SolidRType::UdpPkg> factory(int32_t id_pkg)
        {
            if (_list_pkg.find(id_pkg) != _list_pkg.end())
                return _list_pkg[id_pkg]();
            return NULL;
        }

    private:
        std::map<int32_t, std::function<std::shared_ptr<SolidRType::UdpPkg>()>> _list_pkg;

        std::shared_ptr<SolidRType::UdpPkg<UDPData::UpdateElementInfo>> RetUpdateElementInfo(){
            struct UdpPkg<UDPData::UpdateElementInfo> tmp;
            return (std::make_shared<SolidRType::UdpPkg<UDPData::UpdateElementInfo>>(tmp));
        }

        std::shared_ptr<SolidRType::UdpPkg> RetDeleteElementInfo(){
            return (new SolidRType::UdpPkg<struct DeleteElementInfo>);
        }

        std::shared_ptr<SolidRType::UdpPkg> RetUserInput(){
            return (new SolidRType::UdpPkg<struct UserInput>);
        }

        std::shared_ptr<SolidRType::UdpPkg> RetaddElement(){
            return (new SolidRType::UdpPkg<struct addElement>);
        }

        std::shared_ptr<SolidRType::UdpPkg> RetChangeGameStatus() {
            return (new SolidRType::UdpPkg<struct ChangeGameStatus>);
        }
    };
}

#endif //CPP_RTYPE_FACTORYUDPPKG_HPP
