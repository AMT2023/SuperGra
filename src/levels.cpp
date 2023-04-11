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
    bool t;
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
    int curLevel = 0;

    std::vector<Checkpoint> checkpoints;
    int checkpointsTouched;

    sf::Vector2f playerSpawnpoint;
    float playerAngle;

    void loadLevel(int nLevel, Player& player)
    {
        curLevel = nLevel;

        std::fstream levelInfoFile("data/levels/level" + std::to_string(curLevel) + "/levelInfo");

        levelInfoFile >> playerSpawnpoint.x >> playerSpawnpoint.y >> playerAngle;
        player.reset(playerSpawnpoint, playerAngle);

        std::cout << curLevel;

        std::string bgTexPath;
        levelInfoFile >> bgTexPath;
        bgTexPath = ("data/levels/level" + std::to_string(curLevel) + "/" + bgTexPath);
        bgTex.loadFromFile(bgTexPath);
        bgSprite.setTexture(bgTex, true);

        std::string fgTexPath;
        levelInfoFile >> fgTexPath;
        fgTexPath = ("data/levels/level" + std::to_string(curLevel) + "/" + fgTexPath);
        fgTex.loadFromFile(fgTexPath);
        fgSprite.setTexture(fgTex, true);

        checkpoints.clear();
        checkpointsTouched = 0;
        sf::Vector2f pointA;
        sf::Vector2f pointB;
        while (levelInfoFile >> pointA.x >> pointA.y >> pointB.x >> pointB.y)
        {
            Checkpoint checkpoint;
            checkpoint.t = false;
            checkpoint.a = {pointA.x, pointA.y};
            checkpoint.b = {pointB.x, pointB.y};
            checkpoints.push_back(checkpoint);
        }

        levelInfoFile.close();
    }

    void reset(Player& player)
    {
        player.reset(playerSpawnpoint, playerAngle);

        checkpointsTouched = 0;
        for (auto& checkpoint : checkpoints)
        {
            checkpoint.t = false;
        }
    }

    void updateCheckpoints(Player& player, int& gameState)
    {
        // Update checkpointsTouched
        for (auto& checkpoint : checkpoints)
        {
            // std::min(player.sprite.getTexture()->getSize().x, player.sprite.getTexture()->getSize().y) / 2
            for (float i = checkpoint.a.x; i <= checkpoint.b.x; i += 1) {
            for (float j = checkpoint.a.y; j <= checkpoint.b.y; j += 1) {

                sf::Vector2f pixel(i, j);
                if (collision::singlePixelTest(player.sprite, pixel) && !checkpoint.t) {

                    checkpoint.t = true;
                    checkpointsTouched++;

                }

            }
            }
        }

        // Got all checkpoints
        if (checkpointsTouched == checkpoints.size()) {
        for (float i = checkpoints[0].a.x; i <= checkpoints[0].b.x; i += 1) {
        for (float j = checkpoints[0].a.y; j <= checkpoints[0].b.y; j += 1) {

            sf::Vector2f pixel(i, j);
            if (collision::singlePixelTest(player.sprite, pixel))
            {
                loadLevel(curLevel + 1, player);
            }

        }
        }
        }
    }

    void update(sf::RenderWindow& window, Player& player, int& gameState)
    {
        if (collision::pixelPerfectTest(player.sprite, fgSprite))
        {
            reset(player);
        }

        updateCheckpoints(player, gameState);

        window.draw(bgSprite);
        window.draw(fgSprite);
    }
};

#endif