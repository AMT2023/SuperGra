#ifndef _PLAYER_
#define _PLAYER_

#include <SFML/Graphics.hpp>
#include "levels.cpp"
#include "utility.cpp"

class Player
{
    public:
    sf::Sprite sprite;
    sf::Texture tex;
    sf::Vector2f spawnpoint;
    int currentCheckpoint = 0;
    float angle = 0;
    float speed;

    float przyspieszenie = 0.1;
    float opor = 0.98;

    Player()
    {
        float texScale = 0.3;
        tex.loadFromFile("data/assets/passaratti.png");
        sprite.setTexture(tex);
        sprite.setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);
        sprite.setScale(texScale, texScale);
    }

    void reset(sf::Vector2f playerSpawnpoint, float playerAngle)
    {
        sprite.setPosition(playerSpawnpoint);
        angle = playerAngle;
        sprite.setRotation(angle);
        speed = 0;
    }

    void move()
    {
        speed *= opor;
        sprite.move({
            speed * (float)(sin(radians(angle))),
            speed * (float)(-cos(radians(angle)))
        });
    }

    void update(sf::RenderWindow& window)
    {
        auto view = sf::View(sprite.getPosition(), { 1920u, 1080u });
        window.setView(view);
        window.draw(sprite);
    }
};

#endif