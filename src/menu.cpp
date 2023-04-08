#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "levels.cpp"
#include "player.cpp"
#include "icon.cpp"

class Menu
{
    private:
    

    public:
    std::vector<Icon> icons0;
    std::vector<Icon> icons1;
    std::vector<Icon> icons2;

    int menuState = 0; // 0 - main menu, 1 - shop, 2 - level won

    Menu()
    {
        icons0.push_back( Icon("data/menu/bg/menu.png", {960, 540}) );
        icons0.push_back( Icon("data/menu/icons/logo.png", {960, 240}, {0.5, 0.5}) );
        icons0.push_back( Icon("data/menu/icons/start.png", {960, 540}) );
        fixTextures(icons0);
    }

    void update(sf::RenderWindow& window, int& gameState, Player& player, Level& level, sf::Clock elapsedTime)
    {
        icons0[1].offset.y = sin(elapsedTime.getElapsedTime().asSeconds() * 3) * 40;

        if (icons0[2].isClicked(window))
        {
            gameState = 1;
            level.loadLevel(0, player);
        }

        for (auto &icon : icons0)
        {
            icon.update(window);
        }
    }
};