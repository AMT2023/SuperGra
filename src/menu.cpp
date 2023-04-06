#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "player.cpp"

class Icon
{
    private:
    sf::Texture tex;
    sf::Sprite sprite;

    public:
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

    void update(sf::RenderWindow &window)
    {
        sprite.setTexture(tex);
        sprite.setPosition({position.x + offset.x, position.y + offset.y});
        window.draw(sprite);
    }
};

class Menu
{
    private:
    std::vector<Icon> icons;

    public:
    Menu()
    {
        icons.push_back( Icon("data/menu/bg/menu.png", {960, 540}) );
        icons.push_back( Icon("data/menu/icons/logo.png", {960, 240}) );
        icons.push_back( Icon("data/menu/icons/start.png", {960, 540}) );
    }

    void update(sf::RenderWindow& window, int& gameState, Player& player, sf::Clock elapsedTime)
    {
        icons[1].offset.y = sin(elapsedTime.getElapsedTime().asSeconds() * 3) * 40;

        if (icons[2].isClicked(window))
        {
            player.reset();
            gameState = 1;
        }

        for (auto &icon : icons)
        {
            icon.update(window);
        }
    }
};