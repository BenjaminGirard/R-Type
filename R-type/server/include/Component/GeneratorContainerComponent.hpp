//
// Created by tetard on 22/01/18.
//

#ifndef CPP_RTYPE_PROJECTILESCONTAINERCOMPONENT_HPP
#define CPP_RTYPE_PROJECTILESCONTAINERCOMPONENT_HPP

#include <AComponent.hpp>
#include <AEntity.hpp>
#include "AGeneratorComponent.hpp"

// le player contient une liste de AEntity (guns) qui sont update en meme temps que le player


class GeneratorContainerComponent : public SolidEngine::AComponent {
private:
    std::vector<std::shared_ptr<AGeneratorComponent>> _genContainer;

public:
    GeneratorContainerComponent() : SolidEngine::AComponent(std::type_index(typeid(GeneratorContainerComponent))) {}

    ~GeneratorContainerComponent() override = default;

    void addGenerator(const std::shared_ptr<AGeneratorComponent> &gen) {
      _genContainer.push_back(gen);
    }

    void shoot(std::shared_ptr<SolidEngine::Mediator> &med,
               const PositionComponent &pos,
               const DirectionComponent &dir,
               const TeamComponent &team) {
      for (auto &it : _genContainer)
        it->generate(med, pos, dir, team);
    }
};

#endif //CPP_RTYPE_PROJECTILESCONTAINERCOMPONENT_HPP
