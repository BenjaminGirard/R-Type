//
// Created by jacquat on 17/01/18.
//

#ifndef INPUTCOMPONENT_HPP_
#define INPUTCOMPONENT_HPP_

#include "AComponent.hpp"

namespace SolidEngine {

    class InputComponent : public AComponent {
    public:
        explicit InputComponent(int lengthMax = 4096)
                : AComponent(std::type_index(typeid(InputComponent))),
                  _lengthMax(lengthMax) { }
        int _lengthMax;
    };
}
#endif /* INPUTCOMPONENT_HPP_ */
