    //
// Created by pereira on 14/01/2018.
//

#ifndef MEDIATOR_HPP_
# define MEDIATOR_HPP_

#include "AEntity.hpp"

    namespace SolidEngine {

    class Manager;

    class Mediator {

    public:

        explicit Mediator(Manager *manager) : _manager(manager){}
        ~Mediator() = default;

        inline void pingDeleteEntity(SolidEngine::AEntity *entity);
        inline SolidEngine::AEntity &pingCreateEntity();
        inline SolidEngine::AEntity &getEntity(uint64_t id);
        inline std::vector<std::shared_ptr<SolidEngine::AEntity>> pingGetEntitiesByComp(std::type_index t);
        inline void pingDeleteComponent(SolidEngine::AEntity *entity);
        inline void pingCreateComponent(SolidEngine::AEntity *entity);
        inline void stop();
        inline void start();

    private:
        Manager *_manager;
    };
}

#endif /* MEDIATOR_HPP_ */
