#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

int menu(){
    sf::RectangleShape icon;
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(icon.getGlobalBounds().contains(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y))
        {

            
        }
    }


}