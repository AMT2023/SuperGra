#ifndef _LEVELS_
#define _LEVELS_

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "player.cpp"
#include "utility.cpp"

struct Object
{
    std::string texturePath;
    sf::Texture tex;
    sf::Sprite sprite;
};

class Level
{
    private:
    sf::Texture bgTex;
    sf::Sprite bgSprite;

    sf::Texture fgTex;
    sf::Sprite fgSprite;

    public:
    std::vector<Object> objects;

    sf::Vector2f playerSpawnpoint;
    float playerAngle;

    void loadLevel(int nLevel, Player& player)
    {
        std::fstream levelInfoFile("data/levels/level" + std::to_string(nLevel) + "/levelInfo");

        levelInfoFile >> playerSpawnpoint.x >> playerSpawnpoint.y >> playerAngle;

        std::string bgTexPath;
        levelInfoFile >> bgTexPath;
        bgTexPath = ("data/levels/level" + std::to_string(nLevel) + "/" + bgTexPath);
        bgTex.loadFromFile(bgTexPath);
        bgSprite.setTexture(bgTex);

        std::string fgTexPath;
        levelInfoFile >> fgTexPath;
        fgTexPath = ("data/levels/level" + std::to_string(nLevel) + "/" + fgTexPath);
        fgTex.loadFromFile(fgTexPath);
        fgSprite.setTexture(fgTex);

        levelInfoFile.close();
    }

    void update(sf::RenderWindow& window, Player& player)
    {
        if (Collision::pixelPerfectTest(player.sprite, fgSprite))
        {
            player.reset(playerSpawnpoint, playerAngle);
        }

        window.draw(bgSprite);
        window.draw(fgSprite);
    }
};

#endif