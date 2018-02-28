//
// Created by tetard on 23/01/18.
//

#ifndef CPP_RTYPE_INPUTSYSTEM_HPP
#define CPP_RTYPE_INPUTSYSTEM_HPP

//#include <GunContainerComponent.hpp>
#include <functional>
#include <utility>
#include "SpeedComponent.hpp"
#include "Protocol.hpp"
#include "ASystem.hpp"
#include "DirectionComponent.hpp"

class InputSystem : public SolidEngine::ASystem {
private:
    std::unordered_map<SolidRType::UDPData::INPUT,
            std::function<void(InputSystem &, std::shared_ptr<SolidEngine::AEntity>&)> > _actions;

public:
    explicit InputSystem(const std::shared_ptr<SolidEngine::Mediator> &med);
    ~InputSystem() override = default;
    void execute() override;
private:
    void pushUpdate(std::shared_ptr<SolidEngine::AEntity> &entity,
                    int32_t x, int32_t y, SolidRType::UDPData::COMMAND_TYPE type);
    void moveDown(std::shared_ptr<SolidEngine::AEntity> &entity);
    void moveUp(std::shared_ptr<SolidEngine::AEntity> &entity);
    void moveLeft(std::shared_ptr<SolidEngine::AEntity> &entity);
    void moveRight(std::shared_ptr<SolidEngine::AEntity> &entity);
    void Pause(std::shared_ptr<SolidEngine::AEntity> &entity);
    void Quit(std::shared_ptr<SolidEngine::AEntity> &entity);
    void shoot(std::shared_ptr<SolidEngine::AEntity> &entity);
};

#endif //CPP_RTYPE_INPUTSYSTEM_HPP
