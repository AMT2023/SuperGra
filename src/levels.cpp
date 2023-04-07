#ifndef _LEVELS_
#define _LEVELS_

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "player.cpp"
#include "utility.cpp"

struct Checkpoint
{
    int i;
    sf::Vector2f a;
    sf::Vector2f b;
};

class Level
{
    private:
    sf::Texture bgTex;
    sf::Sprite bgSprite;

    sf::Texture fgTex;
    sf::Sprite fgSprite;

    public:
    std::vector<Checkpoint> checkpoints;

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

        sf::Vector2f checkpointA;
        sf::Vector2f checkpointB;
        int i = 0;
        while (levelInfoFile >> checkpointA.x >> checkpointA.y >> checkpointB.x >> checkpointB.y)
        {
            Checkpoint checkpoint;
            checkpoint.i = i;
            checkpoint.a = {checkpointA.x, checkpointA.y};
            checkpoint.b = {checkpointB.x, checkpointB.y};
            checkpoints.push_back(checkpoint);

            i++;
        }

        levelInfoFile.close();
    }

    void update(sf::RenderWindow& window, Player& player)
    {
        for (auto& checkpoint : checkpoints)
        {
            for (float i = checkpoint.a.x; i <= checkpoint.b.x; i += std::min(player.sprite.getTexture()->getSize().x, player.sprite.getTexture()->getSize().y) / 2) {
            for (float j = checkpoint.a.y; j <= checkpoint.b.y; j += std::min(player.sprite.getTexture()->getSize().x, player.sprite.getTexture()->getSize().y) / 2) {

                sf::Vector2f pixel(checkpoint.a.x, j);
                // std::cout << pixel.x << ", " << pixel.y << ", " << std::min(player.sprite.getTexture()->getSize().x, player.sprite.getTexture()->getSize().y) <<"\n";
                if (Collision::singlePixelTest(player.sprite, pixel))
                {
                    printf("touching checkpoint\n");
                }

            }
            }
        }

        if (Collision::pixelPerfectTest(player.sprite, fgSprite))
        {
            player.reset(playerSpawnpoint, playerAngle);
        }

        window.draw(bgSprite);
        window.draw(fgSprite);
    }
};

#endif