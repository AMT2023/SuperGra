#ifndef _PLAYER_
#define _PLAYER_

#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
    public:
    sf::RectangleShape rect;
    sf::Texture tex;
    float angle = 0;
    float speed;

    float przyspieszenie = 0.15;
    float opor = 0.98;

    Player(sf::Vector2f position)
    {
        rect.setPosition(position);
        float texScale = 0.3;
        tex.loadFromFile("assets/passaratti.png");
        rect.setSize({texScale * (float)(tex.getSize().x), texScale * (float)(tex.getSize().y)});
        rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
        rect.setTexture(&tex);
    }

    void move()
    {
        speed *= opor;
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

#endif