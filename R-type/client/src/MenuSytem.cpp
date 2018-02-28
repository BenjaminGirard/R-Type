//
// Created by jacquat on 18/01/18.
//

#include <string>
#include "InputComponent.hpp"
#include "ClickableComponent.hpp"
#include "SizeComponent.hpp"
#include "PositionComponent.hpp"
#include "GraphicComponent.hpp"
#include "MenuSystem.hpp"
#include <iostream>
#include "Rtype.hpp"

SolidEngine::MenuSystem::MenuSystem(Sptr<Mediator> &mediator)
        : ASystem(mediator),
          _menuMode({
                            { CREATE_CONNECTION_MENU, (&MenuSystem::createConnectionMenu) },
                            { WAITING_ROOM_MENU, (&MenuSystem::displayWaitingRoomMenu) },
                            { PROFILE_MENU, (&MenuSystem::displayProfile) },
                            { MENU, (&MenuSystem::displayMenu) },
                            { OPTION, (&MenuSystem::displayOption) },
                            { CREATE_MENU, (&MenuSystem::displayCreateGame) },
                            { JOIN_MENU, (&MenuSystem::displayJoinGame) },
                            { JOIN_MENU_PASSWORD, (&MenuSystem::displayJoinRoomPassword) },
                            { START_GAME, (&MenuSystem::StartGame) }
                    })
{
    _requiredComp.emplace_back(std::type_index(typeid(ActionComponent)));
    createConnectionMenu();
}

void    SolidEngine::MenuSystem::displayWaitingRoomMenu() {
    while (!_menuEntities.empty()) {
        _mediator->pingDeleteEntity(_menuEntities.back());
        _menuEntities.pop_back();
    }

    auto &background = _mediator->pingCreateEntity();
    background.addComp<SolidEngine::GraphicComponent>("../Assets/test.png", "Waiting for players");
    background.addComp<PositionComponent>(0, 0);
    background.addComp<SizeComponent>(1920, 1080);
    _menuEntities.push_back(&background);

    auto &buttonBack = _mediator->pingCreateEntity();
    buttonBack.addComp<GraphicComponent>("../Assets/button.png", "Quit room");
    buttonBack.addComp<PositionComponent>(895, 580);
    buttonBack.addComp<SizeComponent>(127, 60);
    buttonBack.addComp<SolidEngine::ClickableComponent>(Action::LEAVE_ROOM, _idRoom);
    _menuEntities.push_back(&buttonBack);
    std::cout << "waiting to connect" << std::endl;
}

void    SolidEngine::MenuSystem::displayProfile() {
    while (!_menuEntities.empty()) {
        _mediator->pingDeleteEntity(_menuEntities.back());
        _menuEntities.pop_back();
    }
    auto &background = _mediator->pingCreateEntity();
    background.addComp<SolidEngine::GraphicComponent>("../Assets/test.png", "v0.1 Alpha");
    background.addComp<PositionComponent>(0, 0);
    background.addComp<SizeComponent>(1920, 1080);
    _menuEntities.push_back(&background);

    auto &name = _mediator->pingCreateEntity();
    name.addComp<SolidEngine::GraphicComponent>("../Assets/backname.png");
    name.addComp<PositionComponent>(791, 340);
    name.addComp<SizeComponent>();
    _menuEntities.push_back(&name);

    auto &textPlayer = _mediator->pingCreateEntity();
    textPlayer.addComp<SolidEngine::GraphicComponent>("", "Player name");
    textPlayer.addComp<PositionComponent>(960, 400);
    textPlayer.addComp<SizeComponent>();
    _menuEntities.push_back(&textPlayer);

    auto &inputName = _mediator->pingCreateEntity();
    inputName.addComp<SolidEngine::GraphicComponent>("../Assets/input.png");
    inputName.addComp<PositionComponent>(820, 430);
    inputName.addComp<SizeComponent>();
    inputName.addComp<SolidEngine::ClickableComponent>(Action::SELECTED,
                                                       SolidEngine::INPUT_ID::PLAYER_NAME);
    inputName.addComp<SolidEngine::InputComponent>(15);
    _menuEntities.push_back(&inputName);

    auto &buttonOK = _mediator->pingCreateEntity();
    buttonOK.addComp<GraphicComponent>("../Assets/button.png", "Accept");
    buttonOK.addComp<PositionComponent>(895, 580);
    buttonOK.addComp<SizeComponent>(127, 60);
    buttonOK.addComp<SolidEngine::ClickableComponent>(Action::NAME_AUTHORIZATION);
    _menuEntities.push_back(&buttonOK);
}

void    SolidEngine::MenuSystem::displayJoinRoomPassword() {
    while (!_menuEntities.empty()) {
        _mediator->pingDeleteEntity(_menuEntities.back());
        _menuEntities.pop_back();
    }

    auto &background = _mediator->pingCreateEntity();
    background.addComp<SolidEngine::GraphicComponent>("../Assets/test.png", "v0.1 Alpha");
    background.addComp<PositionComponent>(0, 0);
    background.addComp<SizeComponent>(1920, 1080);
    _menuEntities.push_back(&background);

    auto &textPlayer = _mediator->pingCreateEntity();
    textPlayer.addComp<SolidEngine::GraphicComponent>("", "Password");
    textPlayer.addComp<PositionComponent>(960, 400);
    textPlayer.addComp<SizeComponent>();
    _menuEntities.push_back(&textPlayer);

    auto &inputName = _mediator->pingCreateEntity();
    inputName.addComp<SolidEngine::GraphicComponent>("../Assets/input.png");
    inputName.addComp<PositionComponent>(820, 430);
    inputName.addComp<SizeComponent>();
    inputName.addComp<SolidEngine::ClickableComponent>(Action::SELECTED,
                                                       SolidEngine::INPUT_ID::JOIN_ROOM_PWD);
    inputName.addComp<SolidEngine::InputComponent>(15);
    _menuEntities.push_back(&inputName);

    auto &buttonOK = _mediator->pingCreateEntity();
    buttonOK.addComp<GraphicComponent>("../Assets/button.png", "Join");
    buttonOK.addComp<PositionComponent>(895, 580);
    buttonOK.addComp<SizeComponent>(127, 60);
    buttonOK.addComp<SolidEngine::ClickableComponent>(Action::JOIN_ROOM);
    _menuEntities.push_back(&buttonOK);

    auto &buttonBack = _mediator->pingCreateEntity();
    buttonBack.addComp<GraphicComponent>("../Assets/button.png", "Back");
    buttonBack.addComp<PositionComponent>(895, 680);
    buttonBack.addComp<SizeComponent>(127, 60);
    buttonBack.addComp<SolidEngine::ClickableComponent>(Action::ASK_ROOM_LIST);
    _menuEntities.push_back(&buttonBack);
}

void    SolidEngine::MenuSystem::displayJoinGame(){
    while (!_menuEntities.empty()) {
        _mediator->pingDeleteEntity(_menuEntities.back());
        _menuEntities.pop_back();
    }

    auto &background = _mediator->pingCreateEntity();
    background.addComp<SolidEngine::GraphicComponent>("../Assets/test.png");
    background.addComp<PositionComponent>(0, 0);
    background.addComp<SizeComponent>(1920, 1080);
    _menuEntities.push_back(&background);

    int z = 1;
    int y = 0;
    for (int i = _dataProtocol._rooms.size() - 1; i >= 0; i--) {
        y += 1;
        if (i > 0 && i % 4 == 0) {
            y = 1;
            z += 1;
        }
        auto &table = _mediator->pingCreateEntity();
        table.addComp<SolidEngine::GraphicComponent>("../Assets/scifi_room_button2.png",
                                                     std::string(std::to_string(_dataProtocol._rooms[i].nbPlayersInRoom) + " / " + std::to_string(_dataProtocol._rooms[i].nbPlayersMax)));
        table.addComp<PositionComponent>(z * 300, (y * 100));
        table.addComp<SizeComponent>(227, 60);
        table.addComp<SolidEngine::ClickableComponent>(Action::JOIN_ROOM_ID, _dataProtocol._rooms[i].roomId + 10);
        _menuEntities.push_back(&table);
    }


    auto &buttonOK = _mediator->pingCreateEntity();
    buttonOK.addComp<GraphicComponent>("../Assets/button.png", "Refresh");
    buttonOK.addComp<PositionComponent>(895, 580);
    buttonOK.addComp<SizeComponent>(127, 60);
    buttonOK.addComp<SolidEngine::ClickableComponent>(Action::ASK_ROOM_LIST);
    _menuEntities.push_back(&buttonOK);

    auto &buttonMenu = _mediator->pingCreateEntity();
    buttonMenu.addComp<GraphicComponent>("../Assets/button.png", "Back");
    buttonMenu.addComp<PositionComponent>(895, 680);
    buttonMenu.addComp<SizeComponent>(127, 60);
    buttonMenu.addComp<SolidEngine::ClickableComponent>(Action::MENU);
    _menuEntities.push_back(&buttonMenu);
}
void    SolidEngine::MenuSystem::displayCreateGame(){
    while (!_menuEntities.empty()) {
        _mediator->pingDeleteEntity(_menuEntities.back());
        _menuEntities.pop_back();
    }

    auto &background = _mediator->pingCreateEntity();
    background.addComp<SolidEngine::GraphicComponent>("../Assets/test.png", "v0.1 Alpha");
    background.addComp<PositionComponent>(0, 0);
    background.addComp<SizeComponent>(1920, 1080);
    _menuEntities.push_back(&background);

    auto &name = _mediator->pingCreateEntity();
    name.addComp<SolidEngine::GraphicComponent>("../Assets/backname.png");
    name.addComp<PositionComponent>(710, 300);
    name.addComp<SizeComponent>(500, 500);
    _menuEntities.push_back(&name);

    auto &textPlayer = _mediator->pingCreateEntity();
    textPlayer.addComp<SolidEngine::GraphicComponent>("", "Number of Players");
    textPlayer.addComp<PositionComponent>(960, 400);
    textPlayer.addComp<SizeComponent>();
    _menuEntities.push_back(&textPlayer);

    auto &inputName = _mediator->pingCreateEntity();
    inputName.addComp<SolidEngine::GraphicComponent>("../Assets/input.png");
    inputName.addComp<PositionComponent>(820, 430);
    inputName.addComp<SizeComponent>();
    inputName.addComp<SolidEngine::ClickableComponent>(Action::SELECTED, SolidEngine::INPUT_ID::CREATE_ROOM_PWD);
    inputName.addComp<SolidEngine::InputComponent>(15);
    _menuEntities.push_back(&inputName);

    auto &textpass = _mediator->pingCreateEntity();
    textpass.addComp<SolidEngine::GraphicComponent>("", "Password");
    textpass.addComp<PositionComponent>(960, 495);
    textpass.addComp<SizeComponent>();
    _menuEntities.push_back(&textpass);

    auto &inputpass = _mediator->pingCreateEntity();
    inputpass.addComp<SolidEngine::GraphicComponent>("../Assets/input.png");
    inputpass.addComp<PositionComponent>(820, 525);
    inputpass.addComp<SizeComponent>();
    inputpass.addComp<SolidEngine::ClickableComponent>(Action::SELECTED,
                                                       SolidEngine::INPUT_ID::CREATE_ROOM_PWD);
    _menuEntities.push_back(&inputpass);

    auto &buttonStart = _mediator->pingCreateEntity();
    buttonStart.addComp<GraphicComponent>("../Assets/button.png", "Start");
    buttonStart.addComp<PositionComponent>(895, 580);
    buttonStart.addComp<SizeComponent>(127, 60);
    buttonStart.addComp<SolidEngine::ClickableComponent>(Action::CREATE_ROOM);
    _menuEntities.push_back(&buttonStart);

    auto &buttonMenu = _mediator->pingCreateEntity();
    buttonMenu.addComp<GraphicComponent>("../Assets/button.png", "Back");
    buttonMenu.addComp<PositionComponent>(895, 680);
    buttonMenu.addComp<SizeComponent>(127, 60);
    buttonMenu.addComp<SolidEngine::ClickableComponent>(Action::MENU);
    _menuEntities.push_back(&buttonMenu);

}
void    SolidEngine::MenuSystem::displayOption(){
    while (!_menuEntities.empty()) {
        _mediator->pingDeleteEntity(_menuEntities.back());
        _menuEntities.pop_back();
    }

    auto &background = _mediator->pingCreateEntity();
    background.addComp<SolidEngine::GraphicComponent>("../Assets/test.png", "v0.1 Alpha");
    background.addComp<PositionComponent>(0, 0);
    background.addComp<SizeComponent>(1920, 1080);
    _menuEntities.push_back(&background);

    auto &name = _mediator->pingCreateEntity();
    name.addComp<SolidEngine::GraphicComponent>("../Assets/backname.png");
    name.addComp<PositionComponent>(791, 340);
    name.addComp<SizeComponent>();
    _menuEntities.push_back(&name);

    auto &buttonStart = _mediator->pingCreateEntity();
    buttonStart.addComp<GraphicComponent>("../Assets/button.png", "Back");
    buttonStart.addComp<PositionComponent>(895, 580);
    buttonStart.addComp<SizeComponent>(127, 60);
    buttonStart.addComp<SolidEngine::ClickableComponent>(Action::MENU);
    _menuEntities.push_back(&buttonStart);
}

void    SolidEngine::MenuSystem::StartGame() {
    while (!_menuEntities.empty()) {
        _mediator->pingDeleteEntity(_menuEntities.back());
        _menuEntities.pop_back();
    }
    return ;
}

void    SolidEngine::MenuSystem::displayMenu() {

    while (!_menuEntities.empty()) {
        _mediator->pingDeleteEntity(_menuEntities.back());
        _menuEntities.pop_back();
    }

    auto &background = _mediator->pingCreateEntity();
    background.addComp<SolidEngine::GraphicComponent>("../Assets/test.png", "v0.1 Alpha");
    background.addComp<PositionComponent>(0, 0);
    background.addComp<SizeComponent>(1920, 1080);
    _menuEntities.push_back(&background);

    auto &name = _mediator->pingCreateEntity();
    name.addComp<SolidEngine::GraphicComponent>("../Assets/backname.png");
    name.addComp<PositionComponent>(791, 340);
    name.addComp<SizeComponent>();
    _menuEntities.push_back(&name);

    auto &buttonCreateRoom = _mediator->pingCreateEntity();
    buttonCreateRoom.addComp<GraphicComponent>("../Assets/button.png", "Create Room");
    buttonCreateRoom.addComp<PositionComponent>(860, 390);
    buttonCreateRoom.addComp<SizeComponent>(200, 60);
    buttonCreateRoom.addComp<SolidEngine::ClickableComponent>(Action::CREATE_MENU);
    _menuEntities.push_back(&buttonCreateRoom);

    auto &buttonJoinRoom = _mediator->pingCreateEntity();
    buttonJoinRoom.addComp<GraphicComponent>("../Assets/button.png", "Join Room");
    buttonJoinRoom.addComp<PositionComponent>(860, 450);
    buttonJoinRoom.addComp<SizeComponent>(200, 60);
    buttonJoinRoom.addComp<SolidEngine::ClickableComponent>(Action::ASK_ROOM_LIST);
    _menuEntities.push_back(&buttonJoinRoom);

    auto &buttonOption = _mediator->pingCreateEntity();
    buttonOption.addComp<GraphicComponent>("../Assets/button.png", "Option");
    buttonOption.addComp<PositionComponent>(860, 510);
    buttonOption.addComp<SizeComponent>(200, 60);
    buttonOption.addComp<SolidEngine::ClickableComponent>(Action::OPTION);
    _menuEntities.push_back(&buttonOption);

    auto &buttonQuit = _mediator->pingCreateEntity();
    buttonQuit.addComp<GraphicComponent>("../Assets/button.png", "Quit");
    buttonQuit.addComp<PositionComponent>(860, 570);
    buttonQuit.addComp<SizeComponent>(200, 60);
    buttonQuit.addComp<SolidEngine::ClickableComponent>(Action::QUIT);
    _menuEntities.push_back(&buttonQuit);

}

void    SolidEngine::MenuSystem::createConnectionMenu()
{
    while (!_menuEntities.empty()) {
        _mediator->pingDeleteEntity(_menuEntities.back());
        _menuEntities.pop_back();
    }
    std::cout << "create connection" << std::endl;
    auto &background = _mediator->pingCreateEntity();
    background.addComp<SolidEngine::GraphicComponent>("../Assets/test.png", "v0.1 Alpha");
    background.addComp<PositionComponent>(0, 0);
    background.addComp<SizeComponent>(1920, 1080);
    _menuEntities.push_back(&background);

    auto &name = _mediator->pingCreateEntity();
    name.addComp<SolidEngine::GraphicComponent>("../Assets/backname.png");
    name.addComp<PositionComponent>(791, 340);
    name.addComp<SizeComponent>();
    _menuEntities.push_back(&name);

    auto &textPlayer = _mediator->pingCreateEntity();
    textPlayer.addComp<SolidEngine::GraphicComponent>("", "Port");
    textPlayer.addComp<PositionComponent>(960, 400);
    textPlayer.addComp<SizeComponent>();
    _menuEntities.push_back(&textPlayer);

    auto &inputName = _mediator->pingCreateEntity();
    inputName.addComp<SolidEngine::GraphicComponent>("../Assets/input.png");
    inputName.addComp<PositionComponent>(820, 430);
    inputName.addComp<SizeComponent>();
    inputName.addComp<SolidEngine::ClickableComponent>(Action::SELECTED,
                                                       SolidEngine::INPUT_ID::PORT);
    inputName.addComp<SolidEngine::InputComponent>(15);
    _menuEntities.push_back(&inputName);

    auto &textIP = _mediator->pingCreateEntity();
    textIP.addComp<SolidEngine::GraphicComponent>("", "IP Server");
    textIP.addComp<PositionComponent>(960, 495);
    textIP.addComp<SizeComponent>();
    _menuEntities.push_back(&textIP);

    auto &inputIP = _mediator->pingCreateEntity();
    inputIP.addComp<SolidEngine::GraphicComponent>("../Assets/input.png");
    inputIP.addComp<PositionComponent>(820, 525);
    inputIP.addComp<SizeComponent>();
    inputIP.addComp<SolidEngine::ClickableComponent>(Action::SELECTED,
                                                     SolidEngine::INPUT_ID::IP);
    _menuEntities.push_back(&inputIP);

    auto &buttonOK = _mediator->pingCreateEntity();
    buttonOK.addComp<GraphicComponent>("../Assets/button.png", "Connect");
    buttonOK.addComp<PositionComponent>(895, 580);
    buttonOK.addComp<SizeComponent>(127, 60);
    buttonOK.addComp<SolidEngine::ClickableComponent>(Action::CONNECTIONTCP);
    _menuEntities.push_back(&buttonOK);

}

void    SolidEngine::MenuSystem::updateText(int64_t c)
{
    for(auto const& entity: _menuEntities)
        if (c != 0 && entity->hasComp<InputComponent>() && entity->hasComp<GraphicComponent>()) {
            auto &graphicComponent = entity->getComp<GraphicComponent>();
            auto &inputComponent = entity->getComp<InputComponent>();
            if (c != '\b' && graphicComponent._text.size() < inputComponent._lengthMax)
                graphicComponent._text += static_cast<char >(c);
            else if (c == '\b' && !graphicComponent._text.empty())
                graphicComponent._text.pop_back();
        }
}

void    SolidEngine::MenuSystem::updateSelect(int64_t id)
{
    for(auto const& entity: _menuEntities) {
        if (entity->hasComp<InputComponent>()) {
            entity->delComp<InputComponent>();
            break ;
        }
    }
    for(auto const& entity: _menuEntities) {
        if (entity->getId() == id)
            entity->addComp<InputComponent>(15);
    }
}

void     SolidEngine::MenuSystem::execute()
{
    for(auto & entity: _entityVec) {
        auto &actionComponent = entity->getComp<ActionComponent>();
        if (actionComponent._action == TEXT_ENTERED && actionComponent._data.has_value())
            updateText(*std::any_cast<std::shared_ptr<char>>(actionComponent._data));
        if (actionComponent._action == SELECTED)
            updateSelect(*std::any_cast<std::shared_ptr<char>>(actionComponent._data));
        if (actionComponent._action >= CREATE_CONNECTION_MENU && actionComponent._action <= QUIT) {
            if (actionComponent._action == JOIN_MENU && actionComponent._data.has_value()) {
                _dataProtocol._rooms.clear();
                std::vector<SolidRType::TCPData::RoomInfo> tmp(std::any_cast<std::vector<SolidRType::TCPData::RoomInfo>>(actionComponent._data));
                while (!tmp.empty()) {
                    _dataProtocol._rooms.push_back(tmp.back());
                    tmp.pop_back();
                }
            }
            if (actionComponent._action == WAITING_ROOM_MENU) {
                _idRoom = *(std::any_cast<std::shared_ptr<char>>(actionComponent._data));
                std::cout << "waiting to connect 2" << std::endl;
            }
            auto it = _menuMode.find(actionComponent._action);
            fnct f;
            if (it != _menuMode.end()) {
                f = it->second;
                (this->*f)();
            }
        }
    }
}
