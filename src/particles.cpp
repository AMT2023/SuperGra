#include <SFML/Graphics.hpp>
#include <iostream>

namespace ps
{
    enum Types
    {
        squareParticle,
        circleParticle
    };

    class Particle
    {
        private:

        int type;
        sf::RectangleShape rect;
        sf::CircleShape circle;
        sf::Vector2f velocity;
        sf::Clock clock;
        float time;
        
        float scaleFactor = 1;
        bool destroy = false;

        public:

        Particle(Types type, sf::Vector2f position, float size, sf::Vector2f velocity, sf::Color color, float time)
        {
            this->type = type;
            this->time = time;
            this->velocity = velocity;

            switch (type)
            {
                case Types::squareParticle:

                    rect.setSize({size, size});
                    rect.setOrigin({size / 2, size / 2});
                    rect.setPosition(position);
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
        }

        bool getDestroy()
        {
            return destroy;
        }

        void update(sf::RenderWindow &window)
        {
            switch (type)
            {
                case Types::squareParticle:
                
                    rect.move(velocity.x, velocity.y);

                    scaleFactor = 1 - clock.getElapsedTime().asSeconds() / time;
                    rect.setScale(scaleFactor, scaleFactor);
                    setDestroy();

                    window.draw(rect);
                    break;

                case Types::circleParticle:

                    circle.move(velocity.x, velocity.y);

                    scaleFactor = 1 - clock.getElapsedTime().asSeconds() / time;
                    circle.setScale(scaleFactor, scaleFactor);
                    setDestroy();

                    window.draw(circle);
                    break;
            }
        }
    };

    std::vector<Particle> particles;

    void update(sf::RenderWindow &window)
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