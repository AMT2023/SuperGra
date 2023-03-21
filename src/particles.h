#include <SFML/Graphics.hpp>

#pragma once

#ifndef _PARTICLES_H
#define _PARTICLES_H

namespace ps
{
    enum Types
    {
        squareParticle,
        circleParticle
    };

    enum Effects
    {
        shrink = 1 << 0,
        fade = 1 << 1
    };

    class Particle
    {
        private:

        int type;
        int effect;
        sf::RectangleShape rect;
        sf::CircleShape circle;
        sf::Vector2f velocity;
        float rotation;
        sf::Color color;
        float time;
        
        sf::Clock clock;
        float scaleFactor = 1;
        float fadeOpacity = 255;
        bool destroy = false;

        public:

        Particle(int type, int effect, sf::Vector2f position, float size, sf::Vector2f velocity, float rotation, sf::Color color, float time);
        void setDestroy();
        bool getDestroy();
        void updateEffects();
        void updateParticle(sf::RenderWindow &window);
        void update(sf::RenderWindow &window);
    };

    std::vector<Particle> particles;

    void update(sf::RenderWindow &window);
}

#endif