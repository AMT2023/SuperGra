#include <SFML/Graphics.hpp>
#include "driving.cpp"
#include "save.cpp"
int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Passaratti Raceing" };
    window.setFramerateLimit(144);

    auto kwadrat = sf::RectangleShape({100, 100});

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
        window.display();
    }
}
