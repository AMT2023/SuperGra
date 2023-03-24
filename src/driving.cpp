#include <cmath>
#include <iostream>
#include "particles.cpp"
#include "player.cpp"

void driving(Player &player)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player.angle -= 1.1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player.angle += 1.1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        player.speed += player.przyspieszenie;

        ps::particles.push_back(
            ps::Particle(
                ps::Types::squareParticle,
                ps::Effects::fade,
                player.rect.getPosition(),
                10,
                {0.5f * (float)(-sin(M_PI / 180 * ((rand() % 81) + player.angle - 40))),
                 0.5f * (float)(cos(M_PI / 180 * ((rand() % 81) + player.angle - 40)))},
                (rand() % 360),
                sf::Color(92, 34, 1),
                0.4
            ));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        player.speed -= player.przyspieszenie / 2;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        if (player.czasTurbo >= 0 && player.czasTurbo <= player.maxCzasTurbo)
        {
            player.speed = 20 * player.przyspieszenie * player.przyspieszenieTurbo;
            player.czasTurbo -= 0.01;

            ps::particles.push_back(
                ps::Particle(
                    ps::Types::squareParticle,
                    ps::Effects::fade,
                    player.rect.getPosition(),
                    40,
                    {0, 0},
                    player.angle,
                    sf::Color(255, 255, 255, 30),
                    1
                ));
        }
        else
        {
            if (player.czasTurbo != player.maxCzasTurbo * 3)
            {
                player.czasTurbo = player.maxCzasTurbo * 3;
            }
            else
            {
                player.czasTurbo -= 0.01;
            }
        }
    }

    std::cout << player.czasTurbo << ", " << "\n";

    player.rect.setRotation(player.angle);
}

