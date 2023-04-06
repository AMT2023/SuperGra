#ifndef _PARTICLES_
#define _PARTICLES_

#include <SFML/Graphics.hpp>

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

        Particle(int type, int effect, sf::Vector2f position, float size, sf::Vector2f velocity, float rotation, sf::Color color, float time)
        {
            this->type = type;
            this->effect = effect;
            this->velocity = velocity;
            this->rotation = rotation;
            this->color = color;
            this->time = time;

            switch (type)
            {
                case Types::squareParticle:

                    rect.setSize({size, size});
                    rect.setOrigin({size / 2, size / 2});
                    rect.setPosition(position);
                    rect.setRotation(rotation);
                    rect.setFillColor(color);
                    break;

                case Types::circleParticle:

                    circle.setRadius(size);
                    circle.setOrigin({size, size});
                    circle.setPosition(position);
                    circle.setFillColor(color);
                    break;
            }
        }

        void setDestroy()
        {
            if (scaleFactor <= 0)
            {
                destroy = true;
            }
            if (fadeOpacity <= 0)
            {
                destroy = true;
            }
        }

        bool getDestroy()
        {
            return destroy;
        }

        void updateEffects()
        {
            if ((1 & (effect >> 0)))
            {
                scaleFactor = 1 - clock.getElapsedTime().asSeconds() / time;
                setDestroy();
            }

            if ((1 & (effect >> 1)))
            {
                fadeOpacity = color.a * (1 - clock.getElapsedTime().asSeconds() / time);
                if (fadeOpacity < 0) { fadeOpacity = 0; }
                setDestroy();
            }
        }

        void updateParticle(sf::RenderWindow& window)
        {
            switch (type)
            {
                case Types::squareParticle:
                
                    rect.move(velocity.x, velocity.y);

                    rect.setScale(scaleFactor, scaleFactor);
                    rect.setFillColor(sf::Color(color.r, color.g, color.b, fadeOpacity));
                    setDestroy();

                    window.draw(rect);
                    break;

                case Types::circleParticle:

                    circle.move(velocity.x, velocity.y);

                    circle.setScale(scaleFactor, scaleFactor);
                    circle.setFillColor(sf::Color(color.r, color.g, color.b, fadeOpacity));
                    setDestroy();

                    window.draw(circle);
                    break;
            }
        }

        void update(sf::RenderWindow& window)
        {
            updateEffects();
            updateParticle(window);
        }
    };

    std::vector<Particle> particles;

    void update(sf::RenderWindow& window)
    {
        int i = 0;
        for (int i = 0; i < particles.size(); i++)
        {
            particles[i].update(window);
            if (particles[i].getDestroy())
            {
                particles.erase(particles.begin() + i);
            }
        }
    }
}

#endif