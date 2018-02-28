//
// Created by tetard on 22/01/18.
//

#ifndef CPP_RTYPE_INPUTCOMPONENT_HPP
#define CPP_RTYPE_INPUTCOMPONENT_HPP

#include <queue>
#include <unordered_map>
#include "AComponent.hpp"
#include "Protocol.hpp"
#include "CoolDown.hpp"

class InputComponent : public SolidEngine::AComponent {
private:
    std::queue<SolidRType::UDPData::INPUT> _InputQueue;
    //std::unordered_map<SolidRType::UDPData::INPUT, CoolDown> _cdMap;

public:
    InputComponent() : AComponent(std::type_index(typeid(InputComponent))) {}

    ~InputComponent() override = default;

    void push(SolidRType::UDPData::INPUT in) { _InputQueue.push(in); }

    SolidRType::UDPData::INPUT tryPop() {
      if (_InputQueue.empty())
        return SolidRType::UDPData::INPUT::NONE;
      auto ret = _InputQueue.front();
      _InputQueue.pop();
      return ret;
    }

};

#endif //CPP_RTYPE_INPUTCOMPONENT_HPP
