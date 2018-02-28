#ifndef IMPACT_SYSTEM_HPP
# define IMPACT_SYSTEM_HPP

# include "ASystem.hpp"

class ImpactSystem : public SolidEngine::ASystem {
private:

public:
    ImpactSystem(const std::shared_ptr<SolidEngine::Mediator> &mediator);
    ~ImpactSystem() override = default;
    void execute(void) override;
};

#endif /* IMPACT_SYSTEM_HPP */