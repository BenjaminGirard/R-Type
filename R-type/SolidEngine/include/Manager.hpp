//
// Created by tetard on 12/01/18.
//

#ifndef MANAGER_HPP_
# define MANAGER_HPP_

# include "ServerIDComponent.hpp"
# include "EntityManager.hpp"
# include "SystemManager.hpp"

namespace SolidEngine {

    class Mediator;

    class Manager final {

    private:
        EntityManager _em;
        SystemManager _sm;
        Sptr<Mediator>      _mediator;
        bool _isRunning;

    public:
        Manager(): _mediator(std::make_shared<Mediator>(this)), _isRunning(true) {}

        AEntity &addEntity() {
            Sptr<SolidEngine::AEntity> entity = std::make_shared<AEntity>(_mediator);
            _em.addEntity(entity);
            _sm.addEntityToAppropriateSystems(entity);
            return *entity;
        }

        AEntity &getEntity(uint64_t id) {
            for (auto const &entity : _em.getEntities()) {
                if (entity.second->hasComp<ServerIDComponent>()) {
                    auto &comp = entity.second->getComp<ServerIDComponent>();
                    if (comp._id == id)
                        return *entity.second;
                }
            }
            throw std::invalid_argument("Invalid argument while getting Entity: invalid Id.");
        }


        void removeEntity(uint64_t id) {
            _sm.removeEntityToAllSystems(_em.getEntities().at(id));
            _em.removeEntity(id);
        }


        template <typename T>
        T &addSystem() {
            Sptr<T> sys = std::make_shared<T>(_mediator);
            auto CorrespondingEntityList = _em.getEligibleEntities(sys->getSortedRequiredComp());
            for(auto const& entity : CorrespondingEntityList)
                sys->addEntity(entity.second);
            _sm.addSystem(sys);
            return (*sys);
        }

        template <typename T, typename ...Args>
        T &addSystem(Args && ...args) {
            Sptr<T> sys = std::make_shared<T>(_mediator, FWD(args)...);
            auto CorrespondingEntityList = _em.getEligibleEntities(sys->getSortedRequiredComp());
            for(auto const& entity : CorrespondingEntityList)
                sys->addEntity(entity.second);
            _sm.addSystem(sys);
            return (*sys);
        }


        void addComponent(uint64_t id) {
            _sm.addEntityToAppropriateSystems(_em.getEntities().at(id));
        }

        void removeComponent(uint64_t id) {
            _sm.removeEntityToAppropriateSystems(_em.getEntities().at(id));
        }

        std::vector<Sptr<AEntity>> getEntitiesByComp(std::type_index t) {
          return _em.getEntitiesByComponent(t);
        }

        void executeSystems() {
            for(auto const &system: _sm.getSystems())
                system->execute();
        }

        bool isRunning() { return _isRunning; }
        void stop() { _isRunning = false; }
        void start() { _isRunning = true; }

        Manager(const Manager &cp) = delete;
        Manager &operator=(const Manager &cp) = delete;
    };

};


#endif /* MANAGER_HPP_ */
