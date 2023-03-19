#include <SFML/Graphics.hpp>
#include "driving.cpp"
#include "save_init.cpp"

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Passaratti Raceing" };
    window.setFramerateLimit(144);

    Player player({window.getSize().x / 2.f, window.getSize().y / 2.f});

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
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
