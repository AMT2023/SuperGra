#include <cmath>
#include "particles.cpp"
#include"player.cpp"

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

