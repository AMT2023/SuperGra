#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "player.cpp"
#include "icon.cpp"

class Menu
{
    private:
    

    public:
    std::vector<Icon> icons;
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