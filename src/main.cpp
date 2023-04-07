#include <SFML/Graphics.hpp>
#include "levels.cpp"
#include "driving.cpp"
#include "save_init.cpp"
#include "menu.cpp"
#include "utility.cpp"


int main()
{
    sf::VideoMode windowVideoMode(1920u, 1080u);
    sf::String windowTitle("Passaratti Racing");
    sf::Uint32 windowStyle(sf::Style::Titlebar | sf::Style::Close);
    sf::Uint32 windowStyleFullscreen(sf::Style::Fullscreen);
    sf::Uint32 windowFramerateLimit(144);
    bool windowIsFullscreen = 0;
    sf::RenderWindow window{ windowVideoMode, windowTitle, windowStyle };
    window.setFramerateLimit(windowFramerateLimit);

    sf::Clock elapsedTime;

    Player player;

    Level level;
    level.loadLevel(0, player);

    Menu menu;

    int gameState = 0; // 0 - menu, 1 - playing

    while (window.isOpen())
    {
        // if (!window.hasFocus()) { continue; }
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                gameState = 0;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
            {
                if (windowIsFullscreen)
                { window.create( windowVideoMode, windowTitle, windowStyle ); }
                else
                { window.create( windowVideoMode, windowTitle, windowStyleFullscreen ); }
                window.setFramerateLimit(windowFramerateLimit);
                windowIsFullscreen = !windowIsFullscreen;
            }
        }

        window.clear();

        ps::update(window);

        if (gameState == 0)
        {
            menu.update(window, gameState, player, level, elapsedTime);
        }

        if (gameState == 1)
        {
            level.update(window, player);

            driving(player);
            player.update(window);
        }

        window.display();
    }
}