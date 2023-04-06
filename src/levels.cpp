#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "player.cpp"

class Level
{
    sf::Texture background_tex;
    sf::Sprite background;

    std::vector<sf::RectangleShape> objects;

    public:

    void loadLevel(int nLevel, Player& player)
    {
        std::fstream levelFile("data/levels/level" + std::to_string(nLevel));

        sf::Vector2f playerPos;
        levelFile >> playerPos.x >> playerPos.y;

        player.sprite.setPosition(playerPos);

        std::string keyword;
        int values[5];

        sf::RectangleShape object;

        while (levelFile >> keyword >> values[0] >> values[1] >> values[2] >> values[3] >> values[4])
        {
            if (keyword == "wall") // [0] - posX, [1] - posY, [2] - width, [3] - height, [4] - rotation
            {
                sf::RectangleShape object({(float)(values[2]), (float)(values[3])});
                object.setOrigin(values[2] / 2, values[3] / 2);
                object.setPosition(values[0], values[1]);
                object.setRotation(180 / M_PI * values[4]);
                objects.push_back(object);
            }
        }
        
        levelFile.close();
    }

    void update(sf::RenderWindow &window)
    {
        for (auto &object : objects)
        {
            window.draw(object);
        }
    }
};