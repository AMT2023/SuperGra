#ifndef _LEVELS_
#define _LEVELS_

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include "player.cpp"
#include "utility.cpp"

struct Checkpoint
{
    bool t = false;
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

        std::string bgTexPath;
        levelInfoFile >> bgTexPath;
        bgTexPath = ("data/levels/level" + std::to_string(curLevel) + "/" + bgTexPath);
        bgTex.loadFromFile(bgTexPath);
        bgSprite.setTexture(bgTex);

        std::string fgTexPath;
        levelInfoFile >> fgTexPath;
        fgTexPath = ("data/levels/level" + std::to_string(curLevel) + "/" + fgTexPath);
        fgTex.loadFromFile(fgTexPath);
        fgSprite.setTexture(fgTex);

        checkpoints.clear();
        checkpointsTouched = 0;
        sf::Vector2f checkpointA;
        sf::Vector2f checkpointB;
        while (levelInfoFile >> checkpointA.x >> checkpointA.y >> checkpointB.x >> checkpointB.y)
        {
            Checkpoint checkpoint;
            checkpoint.a = {checkpointA.x, checkpointA.y};
            checkpoint.b = {checkpointB.x, checkpointB.y};
            checkpoints.push_back(checkpoint);
        }

        levelInfoFile.close();
    }

    void reset(Player& player)
    {
        loadLevel(curLevel, player);
    }

    void updateCheckpoints(Player& player, int& gameState)
    {
        // Update checkpointsTouched
        for (auto& checkpoint : checkpoints)
        { 
            for (float i = checkpoint.a.x; i <= checkpoint.b.x; i += std::min(player.sprite.getTexture()->getSize().x, player.sprite.getTexture()->getSize().y) / 2) {
            for (float j = checkpoint.a.y; j <= checkpoint.b.y; j += std::min(player.sprite.getTexture()->getSize().x, player.sprite.getTexture()->getSize().y) / 2) {

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
        for (float i = checkpoints[0].a.x; i <= checkpoints[0].b.x; i += std::min(player.sprite.getTexture()->getSize().x, player.sprite.getTexture()->getSize().y) / 2) {
        for (float j = checkpoints[0].a.y; j <= checkpoints[0].b.y; j += std::min(player.sprite.getTexture()->getSize().x, player.sprite.getTexture()->getSize().y) / 2) {

            sf::Vector2f pixel(i, j);
            if (collision::singlePixelTest(player.sprite, pixel))
            {
                gameState = 0;
            }

        }
        }
        }
    }

    void update(sf::RenderWindow& window, Player& player, int& gameState)
    {
        updateCheckpoints(player, gameState);

        if (collision::pixelPerfectTest(player.sprite, fgSprite))
        {
            reset(player);
        }

        window.draw(bgSprite);
        window.draw(fgSprite);
    }
};

#endif