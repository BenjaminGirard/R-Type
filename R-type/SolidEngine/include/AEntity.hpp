#ifndef AENTITY_HPP_
# define AENTITY_HPP_

# include <algorithm>
# include <exception>
# include <unordered_map>
# include <vector>
# include "Alias.hpp"
# include "AComponent.hpp"
# include "Id.hpp"

namespace SolidEngine {

    class Mediator;

    class AEntity {
    protected:
        std::unordered_map<std::type_index, std::shared_ptr<AComponent>> _compMap;
        std::vector<std::type_index> _compTypes;
        uint64_t _id;
        std::shared_ptr<Mediator> _mediator;

    public:
        explicit AEntity(std::shared_ptr<Mediator> &mediator) :
                _id(IntIDFactory::getNextId()), _mediator(mediator) {}

        virtual ~AEntity() { IntIDFactory::addUnusedId(_id); }

        AEntity(AEntity const &other) = delete;
        AEntity &operator=(AEntity const &other) = delete;

        template <typename T>
         T &getComp() {
            std::type_index t(typeid(T));
            if (_compMap.count(t) == 0)
                throw std::invalid_argument("Invalid argument while getting component: invalid Id.");
           return static_cast<T &>(*_compMap[t]);
        }

        template <typename T>
        bool hasComp() {
            std::type_index t(typeid(T));
            return (_compMap.count(t) != 0);
        }

        bool hasComp(std::type_index t) {
          return (_compMap.count(t) != 0);
        }

        /*
        template <typename T>
        T &addComp() {
            return addComp(std::make_unique<T>());
        } */

        template <typename T, typename ...Args>
        T &addComp(Args && ...args) {
            return addComp(std::make_unique<T>(FWD(args)...));
        }

        template <typename T>
        void delComp() {
            std::type_index t(typeid(T));
            if (_compMap.count(t) == 0)
                throw std::invalid_argument("Invalid argument while deleting component: invalid Id.");
            _compMap.erase(t);
            auto it = std::find_if(_compTypes.begin(), _compTypes.end(), [t](std::type_index index)
            { return index == t; });
            _compTypes.erase(it);
            removeComponent();
        }

        const auto &getCompMap() const { return _compMap; }
        const auto &getCompTypes() const { return _compTypes; }
        const auto &getSortedCompTypes() { std::stable_sort(_compTypes.begin(), _compTypes.end()); return _compTypes; }
        const auto &getId() const { return _id; }

    private:

        inline void    addComponent();
        inline void    removeComponent();

        template <typename T>
        T &addComp(std::unique_ptr<T> &&component) {
            auto &ret = *component;

            if (_compMap.find(component->getTypeIndex()) != _compMap.end())
                throw std::invalid_argument("Invalid argument while adding component: Id already used.");
            _compTypes.push_back(component->getTypeIndex());
            _compMap[component->getTypeIndex()] = std::move(component);
            addComponent();
            return ret;
        }

    };
}

#include "Mediator.hpp"

#endif /* AENTITY_HPP_ */