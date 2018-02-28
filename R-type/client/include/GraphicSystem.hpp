//
// Created by jacquat on 12/01/18.
//

#ifndef GRAPHICSYSTEM_HPP_
# define GRAPHICSYSTEM_HPP_

# include <SFML/Graphics.hpp>
# include <set>
# include "GraphicComponent.hpp"
# include "ASystem.hpp"

namespace SolidEngine {

    class GraphicSystem : public ASystem {
    public:
        explicit GraphicSystem(Sptr<Mediator> &mediator);
        void execute() override;
        void delEntity(const Sptr<AEntity> &entity) override {
            if (_sprites.count(entity->getId()) != 0)
                _sprites.erase(entity->getId());
            if (_texts.count(entity->getId()) != 0)
                _texts.erase(entity->getId());
            ASystem::delEntity(entity);
        }
        std::shared_ptr<AEntity> &getEntityByID(int i);

    public:
        static std::shared_ptr<sf::RenderWindow> _window;
    private:
        void displaySprite(std::shared_ptr<AEntity> &i);
        void displayText(std::shared_ptr<AEntity> &i);
        std::unordered_map<uint64_t, std::shared_ptr<sf::Sprite>> _sprites;
        std::unordered_map<uint64_t, std::shared_ptr<sf::Text>> _texts;
        std::vector<std::shared_ptr<sf::Texture>> _textures;
        std::vector<std::shared_ptr<sf::Font>> _fonts;
    };
}


#endif /* GRAPHICSYSTEM_HPP_ */
