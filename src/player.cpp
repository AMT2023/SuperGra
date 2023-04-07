#ifndef _PLAYER_
#define _PLAYER_

#include <SFML/Graphics.hpp>
#include "utility.cpp"

class Player
{
    public:
    sf::Sprite sprite;
    sf::Texture tex;
    sf::Vector2f spawnpoint;
    float angle = 0;
    float speed;

    float przyspieszenie = 0.15;
    float opor = 0.98;

    Player(sf::Vector2f position)
    {
        spawnpoint = position;
        float texScale = 0.3;
        tex.loadFromFile("data/assets/passaratti.png");
        sprite.setTexture(tex);
        sprite.setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);
        sprite.setPosition(spawnpoint);
        sprite.setScale(texScale, texScale);
    }

    void reset()
    {
        sprite.setPosition(spawnpoint);
        angle = 0;
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
        move();
        // auto view = sf::View(sprite.getPosition(), { 1920u, 1080u });
        // window.setView(view);
        window.draw(sprite);
    }
};

#endif