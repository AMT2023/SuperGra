#include "particles.cpp"
#include "player.cpp"
#include "utility.cpp"

void driving(Player& player, Level& level)
{
    float prevAngle = player.angle;
    sf::Vector2f prevPos = player.sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player.angle -= 1.1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player.angle += 1.1;
    }
    player.sprite.setRotation(player.angle);

    if (collision::pixelPerfectTest(level.fgSprite, player.sprite))
    {
        player.sprite.setRotation(prevAngle);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        player.speed += player.przyspieszenie;

        ps::particles.push_back(ps::Particle(
            
            ps::Types::squareParticle,
            ps::Effects::fade,
            player.sprite.getPosition(),
            10,
            {0.5f * (float)(-sin(radians(((rand() % 81) + player.angle - 40)))),
             0.5f * (float)(cos(radians(((rand() % 81) + player.angle - 40))))},
            (rand() % 360),
            sf::Color(92, 34, 1),
            0.4
        ));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        player.speed -= player.przyspieszenie / 2;
    }
    player.move();

    if (collision::pixelPerfectTest(level.fgSprite, player.sprite))
    {
        player.speed = 0;
        player.sprite.setPosition(prevPos);
    }
}