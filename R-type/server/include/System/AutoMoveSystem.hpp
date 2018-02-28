//
// Created by tetard on 28/01/18.
//

#ifndef CPP_RTYPE_AUTOMOVESYSTEM_HPP
#define CPP_RTYPE_AUTOMOVESYSTEM_HPP

#include <ASystem.hpp>

class AutoMoveSystem : public SolidEngine::ASystem {
public:
    AutoMoveSystem(const std::shared_ptr<SolidEngine::Mediator> &mediator);
    ~AutoMoveSystem() override = default;
    void execute(void) override;
};

#endif //CPP_RTYPE_AUTOMOVESYSTEM_HPP
