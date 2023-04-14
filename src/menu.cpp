#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "levels.cpp"
#include "player.cpp"
#include "icon.cpp"

class Menu
{
    public:
    std::vector<std::vector<Icon>> iconSets;

    int menuState = 0; // 0 - main menu, 1 - shop, 2 - level beaten

    Menu()
    {
        iconSets.resize(3);
        iconSets[0].push_back( Icon("data/menu/bg/menu.png", {960, 540}) );
        iconSets[0].push_back( Icon("data/menu/icons/logo.png", {960, 240}, {0.5, 0.5}) );
        iconSets[0].push_back( Icon("data/menu/icons/start.png", {960, 540}) );
        fixTextures(iconSets[0]);

        iconSets[1].push_back( Icon("data/menu/bg/menu.png", {960, 540}) );
        iconSets[1].push_back( Icon("data/menu/icons/logo.png", {960, 240}, {0.5, 0.5}) );
        iconSets[1].push_back( Icon("data/menu/icons/start.png", {960, 540}) );
        fixTextures(iconSets[1]);
    }

    void update(sf::RenderWindow& window, int& gameState, Player& player, Level& level, sf::Clock elapsedTime)
    {
        switch (menuState)
        {
            case 0:
                iconSets[0][1].offset.y = sin(elapsedTime.getElapsedTime().asSeconds() * 3) * 40;

                if (iconSets[0][2].isClicked(window))
                {
                    gameState = 1;
                    level.loadLevel(0, player);
                }
            break;

            case 1:
                iconSets[0][1].offset.y = sin(elapsedTime.getElapsedTime().asSeconds() * 3) * 40;

                if (iconSets[0][2].isClicked(window))
                {
                    gameState = 1;
                    level.loadLevel(0, player);
                }
            break;
        }
        

        for (auto &icon : iconSets[menuState])
        {
            icon.update(window);
        }
    }
};