#ifndef _PLAYER_
#define _PLAYER_

#include<SFML/Graphics.hpp>

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
        rect.setSize({40, 60}); // rect.setSize({63, 128});
        rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);

        // tex.loadFromFile("passaratti-no-bg.png");
        // rect.setTexture(&tex);
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