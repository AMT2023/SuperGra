#include <SFML/Graphics.hpp>
#include <cmath>
#include "particles.cpp"

class Player
{
    public:
    sf::RectangleShape rect;
    sf::Texture tex;
    float angle = 0;
    float speed;

    float PRZYSPIESZENIE = 0.15;

    Player(sf::Vector2f position)
    {
        rect.setPosition(position);
        rect.setSize({40, 60}); // rect.setSize({63, 128});
        rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);

        // tex.loadFromFile("passaratti-no-bg.png");
        // rect.setTexture(&tex);
    }

    void move()
    {
        speed *= 0.98;
        rect.move({
            speed * (float)(sin(M_PI / 180 * angle)),
            speed * (float)(-cos(M_PI / 180 * angle))
        });
    }

    void update(sf::RenderWindow &window)
    {
        move();
        // auto view = sf::View(rect.getPosition(), { 1920u, 1080u });
        // view.setRotation(angle);
        // window.setView(view);
        window.draw(rect);
    }
};

void driving(Player &player)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.angle -= 1.1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.angle += 1.1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player.speed += player.PRZYSPIESZENIE;

        // ps::particles.push_back(
        //     ps::Particle(
        //         ps::Types::squareParticle,
        //         ps::Effects::fade,
        //         rect.getPosition(),
        //         10,
        //         {0.5f * (float)(-sin(M_PI / 180 * ((rand() % 81) + angle - 40))),
        //          0.5f * (float)(cos(M_PI / 180 * ((rand() % 81) + angle - 40)))},
        //         (rand() % 360),
        //         sf::Color(92, 34, 1),
        //         0.4
        //     ));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        player.speed -= player.PRZYSPIESZENIE / 2;
    }

    player.rect.setRotation(player.angle);
}

