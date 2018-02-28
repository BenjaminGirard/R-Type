//
// Created by tetard on 27/01/18.
//

#ifndef CPP_RTYPE_MONSTERGENERATOR_HPP
#define CPP_RTYPE_MONSTERGENERATOR_HPP

#include <ASystem.hpp>
#include <list>

#include <functional>
#include <cstdint>
#include "ADynamicEntity.hpp"

class MonsterGeneratorSystem : public SolidEngine::ASystem {
private:
//    typedef ADynamicEntity *(*create_fptr)();
//    typedef void(*delete_fptr)(ADynamicEntity *);
//
//    std::list<void *> _libs;
//    std::vector<std::pair<ADynamicEntity *, delete_fptr>> _monserList;

    std::vector<std::shared_ptr<ADynamicEntity>> _monstersGenerators;

public:
    MonsterGeneratorSystem(const std::shared_ptr<SolidEngine::Mediator> &mediator);

    ~MonsterGeneratorSystem() override;

    void execute() override;
};

#endif //CPP_RTYPE_MONSTERGENERATOR_HPP
