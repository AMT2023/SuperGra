#ifndef _PLAYER_
#define _PLAYER_

#include <SFML/Graphics.hpp>
#include <cmath>

class Player
{
    public:
    sf::Sprite sprite;
    sf::Texture tex;
    float angle = 0;
    float speed;

    float przyspieszenie = 0.15;
    float opor = 0.98;

    Player(sf::Vector2f position)
    {
        sprite.setPosition(position);
        float texScale = 0.3;
        tex.loadFromFile("data/assets/passaratti.png");
        sprite.setTexture(tex);
        sprite.setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);
        sprite.setScale(texScale, texScale);
    }

    void move()
    {
        speed *= opor;
        sprite.move({
            speed * (float)(sin(M_PI / 180 * angle)),
            speed * (float)(-cos(M_PI / 180 * angle))
        });
    }

    void update(sf::RenderWindow &window)
    {
        move();
        // auto view = sf::View(sprite.getPosition(), { 1920u, 1080u });
        // window.setView(view);
        window.draw(sprite);
    }
};

#endif