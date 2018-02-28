//
// Created by jacquat on 17/01/18.
//
#include <iostream>

#include "ClickableComponent.hpp"
#include "ActionComponent.hpp"
#include "SizeComponent.hpp"
#include "PositionComponent.hpp"
#include "GraphicComponent.hpp"
#include "EventSystem.hpp"
#include <any>
#include "TCPDataProtocol.hpp"
#include "Rtype.hpp"

SolidEngine::EventSystem::EventSystem(Sptr<Mediator> &mediator)
        : ASystem(mediator) {
    _requiredComp.emplace_back(std::type_index(typeid(GraphicComponent)));
    _requiredComp.emplace_back(std::type_index(typeid(PositionComponent)));
    _requiredComp.emplace_back(std::type_index(typeid(SizeComponent)));
    _requiredComp.emplace_back(std::type_index(typeid(ClickableComponent)));
}

std::any    SolidEngine::EventSystem::findTCPInfo(Action action, uint64_t id) {
    std::vector<std::string> input;
    for (auto const& infoEntity: _entityVec) {
        switch (action) {
            case CONNECTIONTCP: {
                if (infoEntity->hasComp<ClickableComponent>() && infoEntity->hasComp<GraphicComponent>()) {
                    auto &clickComp = infoEntity->getComp<ClickableComponent>();
                    auto &graphComp = infoEntity->getComp<GraphicComponent>();
                    if (clickComp._id == SolidEngine::INPUT_ID::PORT) {
                        input.push_back(graphComp._text);
                        continue;
                    }
                    if (clickComp._id == SolidEngine::INPUT_ID::IP) {
                        input.push_back(graphComp._text);
                        continue;
                    }
                }
                return input;
            }
            case NAME_AUTHORIZATION: {
                if (infoEntity->hasComp<ClickableComponent>() && infoEntity->hasComp<GraphicComponent>()) {
                    auto &clickComp = infoEntity->getComp<ClickableComponent>();
                    auto &graphComp = infoEntity->getComp<GraphicComponent>();
                    if (clickComp._id == SolidEngine::INPUT_ID::PLAYER_NAME) {
                        input.push_back(graphComp._text);
                    }
                }
                return input;
            }
            case CREATE_ROOM: {
                if (infoEntity->hasComp<ClickableComponent>() && infoEntity->hasComp<GraphicComponent>()) {
                    auto &clickComp = infoEntity->getComp<ClickableComponent>();
                    auto &graphComp = infoEntity->getComp<GraphicComponent>();
                    if (clickComp._id == SolidEngine::INPUT_ID::CREATE_ROOM_NB_PLAYER) {
                        input.push_back(graphComp._text);
                        continue;
                    }
                    if (clickComp._id == SolidEngine::INPUT_ID::CREATE_ROOM_PWD) {
                        input.push_back(graphComp._text);
                        continue;
                    }
                }
                return input;
            }
            case SELECTED: {
                return std::make_shared<char>(id);
            }
            case JOIN_ROOM_ID: {
                if (infoEntity->hasComp<ClickableComponent>()) {
                    auto &clickComp = infoEntity->getComp<ClickableComponent>();
                    if (infoEntity->getId() == id) {
                        return std::make_shared<char>(clickComp._id - 10);
                    }
                }
                break;
            }
            case JOIN_ROOM: {
                if (infoEntity->hasComp<ClickableComponent>() && infoEntity->hasComp<GraphicComponent>()) {
                    auto &graphComp = infoEntity->getComp<GraphicComponent>();
                    auto &clickComp = infoEntity->getComp<ClickableComponent>();
                    if (clickComp._id == SolidEngine::INPUT_ID::JOIN_ROOM_PWD) {
                        input.push_back(graphComp._text);
                    }
                }
                return input;
            }
            case LEAVE_ROOM: {
                if (infoEntity->hasComp<ClickableComponent>()) {
                    auto &clickComp = infoEntity->getComp<ClickableComponent>();
                    return (std::make_shared<char>(clickComp._id));
                }
                break;
            }
            default:
                break;
        }
    }
    return nullptr;
}

void     SolidEngine::EventSystem::execute() {
    sf::Event event;
    auto window = SolidEngine::GraphicSystem::_window;

    while (window->pollEvent(event))
        switch (event.type)
        {
            case sf::Event::Closed : {
                auto &entity = _mediator->pingCreateEntity();
                entity.addComp<ActionComponent>(Action::QUIT);
                break;
            }
            case sf::Event::TextEntered : {
                auto &entity = _mediator->pingCreateEntity();
                entity.addComp<ActionComponent>(Action::TEXT_ENTERED, std::make_shared<char>(event.text.unicode));
            }
            case sf::Event::KeyPressed : {
                std::cout << "Action !!!" << std::endl;
                auto event_id = static_cast<Event>(event.key.code);
                if (_events.count(event_id) == 0)
                    break ;
                auto &entity = _mediator->pingCreateEntity();
                entity.addComp<ActionComponent>(_events[event_id]);
                break;
            }
            case sf::Event::MouseButtonReleased : {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                for(auto const& entity: _entityVec) {
                    auto &posComp = entity->getComp<PositionComponent>();
                    auto &sizeComp = entity->getComp<SizeComponent>();
                    if (mousePos.x >= posComp.x && mousePos.x <= posComp.x + sizeComp.width &&
                            mousePos.y >= posComp.y && mousePos.y <= posComp.y + sizeComp.height) {

                        auto &newEntity = _mediator->pingCreateEntity();
                        newEntity.addComp<ActionComponent>(entity->getComp<ClickableComponent>()._action,
                                                         findTCPInfo(entity->getComp<ClickableComponent>()._action, entity->getId()));
                    }
                }
            }
            default:
                break;
        }
}