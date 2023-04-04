#include <SFML/Graphics.hpp>
#include "levels.cpp"
#include "driving.cpp"
#include "save_init.cpp"
#include "menu.cpp"


int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Passaratti Racing", sf::Style::Default};
    window.setFramerateLimit(144);

    Player player({window.getSize().x / 2.f, window.getSize().y / 2.f});
    Level level;
    level.loadLevel(0, player);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if ((event.type == sf::Event::Closed) or (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
        }

        window.clear();

        ps::update(window);

        driving(player);
        player.update(window);

        level.update(window);

        window.display();
    }
}
