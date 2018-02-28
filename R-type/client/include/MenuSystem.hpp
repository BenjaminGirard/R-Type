//
// Created by jacquat on 18/01/18.
//

#ifndef INPUTSYSTEM_HPP_
#define INPUTSYSTEM_HPP_

#include "InputComponent.hpp"
#include "ActionComponent.hpp"
#include "ASystem.hpp"
#include "TCPDataProtocol.hpp"

namespace SolidEngine {

    class MenuSystem : public ASystem {
        typedef void (MenuSystem::*fnct)(void);

    public:
        explicit MenuSystem(Sptr<Mediator> &mediator);

        void execute() override;

    private:
        /* Display Functions */

        void createConnectionMenu();
        void displayWaitingRoomMenu();
        void displayProfile();
        void displayMenu();
        void displayOption();
        void displayJoinGame();
        void displayJoinRoomPassword();
        void displayCreateGame();
        void StartGame();

        void updateText(int64_t c);
        void updateSelect(int64_t id);
    private:
        bool _update;
        uint64_t _idRoom;
        SolidRType::TCPData::TCPDataProtocol _dataProtocol;
        std::unordered_map<Action, fnct>    _menuMode;
        std::vector<AEntity *> _menuEntities;
    };
}

#endif /* INPUTSYSTEM_HPP_ */
