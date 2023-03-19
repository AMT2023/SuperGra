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
        shrink,
        fade
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
        float fadeOpacity = 1;
        bool destroy = false;

        public:

        Particle(Types type, Effects effect, sf::Vector2f position, float size, sf::Vector2f velocity, float rotation, sf::Color color, float time)
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

        void update(sf::RenderWindow &window)
        {
            switch (effect)
            {
                case Effects::shrink:

                    scaleFactor = 1 - clock.getElapsedTime().asSeconds() / time;
                    setDestroy();

                    break;

                case Effects::fade:

                    fadeOpacity = 255 * (1 - clock.getElapsedTime().asSeconds() / time);
                    if (fadeOpacity < 0) { fadeOpacity = 0; }
                    setDestroy();

                    break;
            }

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