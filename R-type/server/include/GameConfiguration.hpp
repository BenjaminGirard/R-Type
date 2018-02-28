//
// Created by tetard on 26/01/18.
//

#ifndef CPP_RTYPE_GAMECONFIGURATION_HPP
#define CPP_RTYPE_GAMECONFIGURATION_HPP

#include <Manager.hpp>

class GameConfiguration {
public:
    GameConfiguration(SolidEngine::Manager &manager, int32_t nbPlayer);

    ~GameConfiguration() = default;

    GameConfiguration(const GameConfiguration &cp) = delete;
    GameConfiguration &operator=(const GameConfiguration &cp) = delete;
};

#endif //CPP_RTYPE_GAMECONFIGURATION_HPP
