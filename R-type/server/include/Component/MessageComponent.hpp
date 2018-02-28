//
// Created by bibzer on 27/01/18.
//

#ifndef CPP_RTYPE_MESSAGECOMPONENT_HPP
#define CPP_RTYPE_MESSAGECOMPONENT_HPP

#include <cstdint>
#include <queue>
#include <iostream>
#include "AComponent.hpp"
#include "Binary.hpp"
#include "Protocol.hpp"

class MessageComponent : public SolidEngine::AComponent {
private:
    std::queue<std::vector<char>> _messageQueue;
public:
    MessageComponent() : AComponent(std::type_index(typeid(MessageComponent))) {}
    MessageComponent(struct SolidRType::UDPData::AddElementInfo data) : AComponent(std::type_index(typeid(MessageComponent))) {
        pushInfoToSend<SolidRType::UDPData::AddElementInfo>(data.elementId, SolidRType::UDPData::ADD_ELEMENT, data);
    }
    ~MessageComponent() override = default;

    template <typename T>
    void pushInfoToSend(int64_t id, uint8_t id_pkg, T data) {
        std::vector<char> tmp(1024);

        SolidRType::UdpPkg<T> to_serialize;
        std::memset(&to_serialize, 0, sizeof(SolidRType::UdpPkg<T>));
        to_serialize.id = id;
        to_serialize.pkg_id = id_pkg;
        to_serialize.data = data;
        std::cout << "id : "<<  id << "id_pkg" << (int)id_pkg << std::endl;
        std::cout << sizeof(to_serialize) << std::endl;
        tmp << to_serialize;

        _messageQueue.push(tmp);
    }

    std::vector<char> tryPop() {
        if (_messageQueue.empty()) {
            std::vector<char> noul;
            return noul;
        }
        auto ret = std::move(_messageQueue.front());
        _messageQueue.pop();
        return ret;
    }
};

#endif //CPP_RTYPE_MESSAGECOMPONENT_HPP
