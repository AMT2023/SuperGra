#ifndef _ICON_
#define _ICON_

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Icon
{
    public:
    sf::Texture tex;
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f offset;
    std::string texturePath;
    

    Icon(std::string texturePath, sf::Vector2f position)
    {
        this->texturePath = texturePath;
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
        sprite.setPosition({position.x + offset.x, position.y + offset.y});
        window.draw(sprite);
    }
};

void fixTextures(std::vector<Icon>& icons)
{
    for (auto& icon : icons)
    {
        icon.tex.loadFromFile(icon.texturePath);
        icon.sprite.setTexture(icon.tex);
    }
}

#endif