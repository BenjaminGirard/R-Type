#ifndef ACOMPONENT_HPP_
# define ACOMPONENT_HPP_

# include <typeindex>

namespace SolidEngine {
    class AComponent {
    protected:
        const std::type_index _typeIndex;

    public:
        explicit AComponent(const std::type_index &t) : _typeIndex(t) {}

        virtual ~AComponent() = default;

        const std::type_index &getTypeIndex() const { return _typeIndex; }
    };
};
#endif /* ACOMPONENT_HPP_ */