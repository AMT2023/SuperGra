#ifndef _ICON_
#define _ICON_

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Icon
{
    private:
    sf::Texture tex;
    

    public:
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f offset;

    Icon(std::string texturePath, sf::Vector2f position)
    {
        this->position = position;
        sprite.setPosition(position);
        tex.loadFromFile(texturePath);
        sprite.setTexture(tex);
        sprite.setOrigin(sprite.getGlobalBounds().getSize().x / 2, sprite.getGlobalBounds().getSize().y / 2);
    }

    bool isClicked(sf::RenderWindow& window)
    {
        bool leftMB = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        bool touchingIcon = sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

        if (leftMB && touchingIcon)
        {
            return true;
        }
        return false;
    }

    void update(sf::RenderWindow& window)
    {
        sprite.setTexture(tex);
        sprite.setPosition({position.x + offset.x, position.y + offset.y});
        window.draw(sprite);
    }
};

#endif