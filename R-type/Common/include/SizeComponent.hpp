//
// Created by tetard on 19/01/18.
//

#ifndef CPP_RTYPE_SIZECOMPONENT_HPP
#define CPP_RTYPE_SIZECOMPONENT_HPP

#include <cstdint>
#include "AComponent.hpp"

class SizeComponent : public SolidEngine::AComponent {
public:
    float width;
    float height;
    SizeComponent(int64_t Width = 0, int64_t Height = 0)
            : AComponent(std::type_index(typeid(SizeComponent))),
              width(Width), height(Height) {}

    ~SizeComponent() override = default;
};

#endif //CPP_RTYPE_SIZECOMPONENT_HPP
