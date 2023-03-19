#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include "particles.cpp"

void driving(float &angle, float &speed, sf::RectangleShape &rect)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        angle -= 1.4;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        angle += 1.4;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        speed += 0.15;

        ps::particles.push_back(
            ps::Particle(
                ps::Types::squareParticle,
                ps::Effects::fade,
                rect.getPosition(),
                10,
                {-0.5f * (float)(sin(M_PI / 180 * ((rand() % 81) + angle - 40))),
                 0.5f * (float)(cos(M_PI / 180 * ((rand() % 81) + angle - 40)))},
                (rand() % 360),
                sf::Color(92, 34, 1),
                0.4
            ));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        speed -= 0.08;
    }

    rect.setRotation(angle);
}

class Player
{
    public:
    sf::RectangleShape rect;
    float angle = 0;
    float speed;

    Player(sf::Vector2f position)
    {
        rect.setPosition(position);
        rect.setSize({40, 60});
        rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
    }

    void move()
    {
        speed *= 0.98;
        rect.move({
            speed * static_cast<float>(sin(M_PI / 180 * angle)),
            -speed * static_cast<float>(cos(M_PI / 180 * angle))
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