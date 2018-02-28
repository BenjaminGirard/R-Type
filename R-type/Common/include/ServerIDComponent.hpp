//
// Created by jacquat on 28/01/18.
//

#ifndef SERVERIDCOMPONENT_HPP_
# define SERVERIDCOMPONENT_HPP_

#include <cstdint>
#include "AComponent.hpp"

namespace SolidEngine {

    class ServerIDComponent : public AComponent {
    public:
        explicit ServerIDComponent(uint64_t id)
                : AComponent(std::type_index(typeid(ServerIDComponent))), _id(id)
        { }
        uint64_t _id;
    };
}
#endif /* SERVERIDCOMPONENT_HPP_ */
