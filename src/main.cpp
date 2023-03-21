#include <SFML/Graphics.hpp>
// #include "particles.h"
#include "driving.cpp"
#include "save_init.cpp"

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Passaratti Raceing", sf::Style::Fullscreen };
    window.setFramerateLimit(144);

    Player player({window.getSize().x / 2.f, window.getSize().y / 2.f});

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

        // ps::update(window);

        driving(player.angle, player.speed, player.rect);
        player.update(window);

        window.display();
    }
}
