//
// Created by tetard on 29/01/18.
//

#ifndef CPP_RTYPE_IDPLAYERCOMPONENT_HPP
#define CPP_RTYPE_IDPLAYERCOMPONENT_HPP

#include <AComponent.hpp>
#include <cstdint>

class IdPlayerComponent : public SolidEngine::AComponent {
public:
    uint64_t _playerId;
    IdPlayerComponent(uint64_t playerid) : AComponent(std::type_index(typeid(IdPlayerComponent))), _playerId(playerid) {}
};

#endif //CPP_RTYPE_IDPLAYERCOMPONENT_HPP
