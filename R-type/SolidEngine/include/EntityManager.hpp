#ifndef ENTITYMANAGER_HPP_
# define ENTITYMANAGER_HPP_

# include <algorithm>
# include <map>
# include "AEntity.hpp"

namespace SolidEngine {

    class EntityManager {

    private:
        std::map<uint64_t, Sptr<AEntity>> _entities;

    public:
        EntityManager() = default;

        ~EntityManager() = default;

        EntityManager(const EntityManager &cp) = delete;

        EntityManager &operator=(const EntityManager &cp) = delete;

    public:
        const std::map<uint64_t, Sptr<AEntity>> &getEntities() const { return _entities; }

        void addEntity(const Sptr<AEntity> &entity) {
          if (_entities.count(entity->getId()) != 0)
            throw std::invalid_argument("Invalid argument while adding Entity to EntityManager: Id already used.");
          _entities[entity->getId()] = entity;
        }

        void removeEntity(const uint64_t id) {
          if (_entities.count(id) == 0)
            throw std::invalid_argument("Invalid argument while deleting Entity from EntityManager: invalid Id.");
          _entities.erase(id);
        }

        /**
         * @param required The collection of components needed.
         * @return returns the collection of Entities with the required components.
         */
        auto getEligibleEntities(const std::vector<std::type_index> &sortedRequirements) {
            std::unordered_map<uint64_t, Sptr<AEntity>> EligibleEntities;
            for(auto const &entity : _entities) {
                auto sortedEntityCompTypes = entity.second->getSortedCompTypes();
                if (std::includes(sortedEntityCompTypes.begin(), sortedEntityCompTypes.end(), sortedRequirements.begin(), sortedRequirements.end()))
                    EligibleEntities[entity.first] = entity.second;
            }
            return EligibleEntities;
        }

        auto getEntitiesByComponent(std::type_index t) {
          std::vector<Sptr<AEntity>> EligibleEntities;
          for(auto const &entity : _entities) {
            if (entity.second->hasComp(t))
              EligibleEntities.push_back(entity.second);
          }
          return EligibleEntities;
        }
    };
};

#endif /* ENTITYMANAGER_HPP_ */