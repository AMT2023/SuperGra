#include <SFML/Graphics.hpp>
#include "driving.cpp"

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Passaratti Raceing" };
    window.setFramerateLimit(144);

    Player player({100, 110});

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

        driving(player.angle, player.speed, player.rect);
        player.update(window);

        window.display();
    }
}
