//
// Created by tetard on 20/01/18.
//

#ifndef CPP_RTYPE_IMONSTER_HPP
#define CPP_RTYPE_IMONSTER_HPP

#include <map>
#include <memory>

#ifdef WIN32
# define PLUGIN_EXPORT __declspec(dllexport)
#else
# define PLUGIN_EXPORT // empty
#endif

//namespace SolidEngine {
//
//    class Mediator;
//}
#include "Mediator.hpp"

namespace {
    class ADynamicEntity {
    public:
        ADynamicEntity() = default;

        virtual ~ADynamicEntity() = default;

        virtual void createEntity(std::shared_ptr<SolidEngine::Mediator> &mediator,
                                  int32_t posx, int32_t posy, double dirx, double diry) const = 0;

        /**
         * Override this function to log information into a string
         * @return return a log of information about the entity to be generated
         */
        virtual std::string getEntityInfo() const = 0;
    };
}

#endif //CPP_RTYPE_IMONSTER_HPP
