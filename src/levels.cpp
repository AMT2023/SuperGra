#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include "player.cpp"
#include "utility.cpp"

struct Object
{
    sf::Texture tex;
    sf::Sprite sprite;
};

class Level
{
    private:
    sf::Texture background_tex;
    sf::Sprite background;

    public:
    std::vector<Object> objects;

    void loadLevel(int nLevel, Player& player)
    {
        std::fstream levelFile("data/levels/level" + std::to_string(nLevel));

        sf::Vector2f playerPos;
        levelFile >> playerPos.x >> playerPos.y;

        player.sprite.setPosition(playerPos);

        std::string keyword;
        int values[5];
        std::string texturePath;

        while (levelFile >> keyword >> values[0] >> values[1] >> values[2] >> values[3] >> values[4] >> texturePath)
        {
            if (keyword == "wall") // [0] - posX, [1] - posY, [2] - width, [3] - height, [4] - rotation, [5] - texturePath
            {
                Object object;
                object.tex.loadFromFile(texturePath);
                object.tex.setRepeated(true);
                object.sprite.setTexture(object.tex);
                // object.sprite.setSize({(float)(values[2]), (float)(values[3])});
                object.sprite.setOrigin(values[2] / 2, values[3] / 2);
                object.sprite.setPosition(values[0], values[1]);
                object.sprite.setRotation(radians(values[4]));
                objects.push_back(object);
            }
        }
        
        levelFile.close();
    }

    void update(sf::RenderWindow& window)
    {
        for (auto &object : objects)
        {
            object.sprite.setTexture(object.tex);
            window.draw(object.sprite);
        }
    }
};