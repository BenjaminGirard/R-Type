#ifndef ASYSTEM_HPP_
# define ASYSTEM_HPP_

# include <vector>
# include "AEntity.hpp"

namespace SolidEngine {

    class Mediator;

    class ASystem {

    protected:
        std::vector<Sptr<AEntity>> _entityVec;
        std::vector<std::type_index> _requiredComp;
        const uint64_t _id;
        Sptr<Mediator> _mediator;

    public:
        explicit ASystem(Sptr<Mediator> mediator) :
                _id(IntIDFactory::getNextId()), _mediator(mediator) {}
        virtual ~ASystem() { IntIDFactory::addUnusedId(_id); }
        ASystem(const ASystem &cp) = delete;
        ASystem &operator=(const ASystem &cp) = delete;

    public:
        virtual void execute() = 0;

        void addEntity(const Sptr<AEntity> &entity) noexcept {
            if (!hasEntity(entity))
                _entityVec.push_back(entity);
        }

        virtual void delEntity(const Sptr<AEntity> &entity) {
            auto i = std::find_if(_entityVec.begin(), _entityVec.end(),
                                  [entity](Sptr<AEntity> const& i)
                                  { return i.get()->getId() == entity.get()->getId(); });
            _entityVec.erase(i);
        }

        bool hasEntity(const Sptr<AEntity> &entity) {
            auto i = std::find_if(_entityVec.begin(), _entityVec.end(),
                                  [entity](Sptr<AEntity> const& i)
                                  { return i.get()->getId() == entity.get()->getId(); });
            return (i != _entityVec.end());
        }


    public:
      const std::vector<Sptr<AEntity>> &getEntityVec() const { return _entityVec; }
      const std::vector<std::type_index> &getRequiredComp() const { return _requiredComp; }
      const std::vector<std::type_index> &getSortedRequiredComp() {std::stable_sort(_requiredComp.begin(), _requiredComp.end()); return _requiredComp;}
      const uint64_t &getId() const { return _id; }
    };
};



#endif /* ASYSTEM_HPP_ */
