#pragma once

#include <SFML/Graphics.hpp>

class Widget : public sf::Drawable, public sf::Transformable {
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

    virtual void handleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;
    
    virtual ~Widget() = default;
};
