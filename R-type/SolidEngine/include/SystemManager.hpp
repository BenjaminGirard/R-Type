//
// Created by tetard on 11/01/18.
//

#ifndef SYSTEMMANAGER_HPP_
# define SYSTEMMANAGER_HPP_

# include "ASystem.hpp"

namespace SolidEngine {

    class SystemManager {
    private:
        std::vector<Sptr<ASystem>> _systems;

    public:
        SystemManager() = default;
        ~SystemManager() = default;

        void addSystem(const Sptr<ASystem> &sys) {
            auto i = std::find_if(_systems.begin(), _systems.end(), [&](std::shared_ptr<ASystem> const& p) {
                return p->getId() == sys->getId();
            });
            if (i != _systems.end())
                throw std::invalid_argument("Invalid argument while adding system: Id already used.");
            _systems.push_back(sys);
        }

        void removeSystem(const Sptr<ASystem> &sys) {
            auto i = std::find_if(_systems.begin(), _systems.end(), [&](std::shared_ptr<ASystem> const& p) {
                return p->getId() == sys->getId();
            });
            if (i == _systems.end())
                throw std::invalid_argument("Invalid argument while adding system: Id already used.");
            _systems.erase(i);
        }

        const auto &getSystems() const { return _systems; }

        /**
         * Add the entity to the appropriate systems depending on the requirement of the systems
         * and the components of the entity.
         * 
         * @param entity The entity to be added to the appropriate systems
         */
        void addEntityToAppropriateSystems(const Sptr<AEntity> &entity) {
            auto sortedEntitySpecs = entity->getSortedCompTypes();

            for(auto const& system: _systems) {
                auto sortedSystemRequirements = system->getSortedRequiredComp();
                if (std::includes(sortedEntitySpecs.begin(), sortedEntitySpecs.end(),
                                  sortedSystemRequirements.begin(), sortedSystemRequirements.end())
                        || sortedSystemRequirements.empty())
                    system->addEntity(entity);
            }
        }

        void removeEntityToAppropriateSystems(const Sptr<AEntity> &entity) {
            auto sortedEntitySpecs = entity->getSortedCompTypes();

            for(auto const& system: _systems) {
                if (system->hasEntity(entity)) {
                    auto sortedSystemRequirements = system->getSortedRequiredComp();
                    if (!std::includes(sortedEntitySpecs.begin(), sortedEntitySpecs.end(),
                                      sortedSystemRequirements.begin(), sortedSystemRequirements.end())) {
                        system->delEntity(entity);
                    }
                }
            }
        }

        void removeEntityToAllSystems(const Sptr<AEntity> &entity) {
            for(auto const& system: _systems) {
                if (system->hasEntity(entity)) {
                    system->delEntity(entity);
                }
            }
        }

        SystemManager(const SystemManager &cp) = delete;
        SystemManager &operator=(const SystemManager &cp) = delete;
    };
};

#endif /* SYSTEMMANAGER_HPP_ */
