//
// Created by jacquat on 12/01/18.
//

#include "GraphicComponent.hpp"
#include "PositionComponent.hpp"
#include "SizeComponent.hpp"
#include "../../client/include/GraphicSystem.hpp"

std::shared_ptr<sf::RenderWindow> SolidEngine::GraphicSystem::_window;

SolidEngine::GraphicSystem::GraphicSystem(std::shared_ptr<Mediator> &mediator)
 : ASystem(mediator)
{
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "R-type", sf::Style::Fullscreen);
    _window->setFramerateLimit(60);
    _requiredComp.emplace_back(std::type_index(typeid(GraphicComponent)));
    _requiredComp.emplace_back(std::type_index(typeid(PositionComponent)));
    _requiredComp.emplace_back(std::type_index(typeid(SizeComponent)));
}

void    SolidEngine::GraphicSystem::displaySprite(std::shared_ptr<AEntity> &entity)
{
    auto &graphicComponent = entity->getComp<GraphicComponent>();
    auto &positionComponent = entity->getComp<PositionComponent>();
    auto &sizeComponent = entity->getComp<SizeComponent>();

    if (_sprites.count(entity->getId()) == 0) {
        _textures.push_back(std::make_shared<sf::Texture>());
        _textures.back()->loadFromFile(graphicComponent._picturePath);
        _sprites[entity->getId()] = std::make_shared<sf::Sprite>();
        _sprites[entity->getId()]->setTexture(*_textures.back());
        if (sizeComponent.width != 0 && sizeComponent.height != 0) {
            _sprites[entity->getId()]->setScale(sizeComponent.width / _textures.back()->getSize().x,
                                                sizeComponent.height / _textures.back()->getSize().y);
        } else {
            sizeComponent.height = _textures.back()->getSize().y;
            sizeComponent.width = _textures.back()->getSize().x;
        }
    }
    _sprites[entity->getId()]->setPosition(positionComponent.x, positionComponent.y);
    _window->draw(*_sprites[entity->getId()]);
}


void    SolidEngine::GraphicSystem::displayText(std::shared_ptr<AEntity> &entity)
{
    auto &graphicComponent = entity->getComp<GraphicComponent>();
    auto &positionComponent = entity->getComp<PositionComponent>();
    auto &sizeComponent = entity->getComp<SizeComponent>();

    if (_texts.count(entity->getId()) == 0) {
        sf::Font font;
        font.loadFromFile("../Assets/font.ttf");
        _fonts.push_back(std::make_shared<sf::Font>(font));
        sf::Text text;
        text.setFont(*_fonts.back());
        text.setCharacterSize(20);
        text.setString(graphicComponent._text);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top + textRect.height / 2.0f);
        text.setPosition(sf::Vector2f(positionComponent.x + sizeComponent.width / 2.0f,
                                      positionComponent.y + sizeComponent.height / 2.0f));
        _texts[entity->getId()] = std::make_shared<sf::Text>(text);
    }
    else {
        _texts[entity->getId()]->setString(graphicComponent._text);
        sf::FloatRect textRect = _texts[entity->getId()]->getLocalBounds();
        _texts[entity->getId()]->setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top + textRect.height / 2.0f);
        _texts[entity->getId()]->setPosition(sf::Vector2f(positionComponent.x + sizeComponent.width / 2.0f,
                                      positionComponent.y + sizeComponent.height / 2.0f));
    }
    _window->draw(*_texts[entity->getId()]);

}

void     SolidEngine::GraphicSystem::execute()
{
    _window->clear();
    for(int i = 0; i < _entityVec.size(); i++) {
        try {
            auto &entity = getEntityByID(i);
            auto &graphicComponent = entity->getComp<GraphicComponent>();
            if (!graphicComponent._picturePath.empty())
                displaySprite(entity);
            if (!graphicComponent._text.empty())
                displayText(entity);
        }
        catch (std::exception& ex)
        { }
    }
    _window->display();
}


std::shared_ptr<SolidEngine::AEntity> &SolidEngine::GraphicSystem::getEntityByID(int id)
{
    auto it = std::find_if(_entityVec.begin(), _entityVec.end(), [id](Sptr<AEntity> entity)
    { return entity->getComp<GraphicComponent>()._id == id; });
    if (it == _entityVec.end())
        throw std::invalid_argument("Invalid argument while getting component: invalid Id.");
    return *it;
}
