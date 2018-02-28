#ifndef DEATH_SYSTEM_HPP_
# define DEATH_SYSTEM_HPP_

#include "ASystem.hpp"

class DeathSystem : public SolidEngine::ASystem {
private:

public:
    DeathSystem(const std::shared_ptr<SolidEngine::Mediator> &mediator);
    ~DeathSystem() override = default;
    void execute(void) override;
};

#endif /* DEATH_SYSTEM_HPP_ */