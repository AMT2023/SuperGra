#include <SFML/Graphics.hpp>
#include "levels.cpp"
#include "driving.cpp"
#include "save_init.cpp"
#include "menu.cpp"


int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Passaratti Racing", sf::Style::Titlebar | sf::Style::Close };
    window.setFramerateLimit(144);

    sf::Clock elapsedTime;

    Player player({window.getSize().x / 2.f, window.getSize().y / 2.f});

    Level level;
    level.loadLevel(0, player);

    Menu menu;

    int gameState = 0; // 0 - menu, 1 - playing

    while (window.isOpen())
    {
        // if (!window.hasFocus()) { continue; }
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if ((event.type == sf::Event::Closed) or (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
        }

        window.clear();

        ps::update(window);

        if (gameState == 0)
        {
            menu.update(window, gameState, player, elapsedTime);
        }

        if (gameState == 1)
        {
            driving(player);
            player.update(window);

            level.update(window);
        }

        window.display();
    }
}
