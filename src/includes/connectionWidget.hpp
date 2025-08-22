#pragma once

#include <cmath>

#include <SFML/System/Vector2.hpp>

#include "widget.hpp"
#include "cityWidget.hpp"
#include "cityStructures.hpp"

class ConnectionWidget : public Widget {
private:
  City *first;
  City *second;

  sf::RectangleShape line;
  
public:
  ConnectionWidget(City *p_first, City *p_second)
    : first(p_first), second(p_second), line(sf::Vector2f(0.f, 3.f)) {}
  
  void updatePosition() {
    sf::Vector2f point1 = this->first->position;
    sf::Vector2f point2 = this->second->position;

    sf::Vector2f direction = point2 - point1;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    float angle = std::atan2(direction.y, direction.x) * 180 / M_PI; // Convert to degrees
    
    line.setSize( sf::Vector2f(length, line.getSize().y) );

    line.setOrigin( sf::Vector2f(0.f, line.getSize().y / 2) ); // Set the origin to the center of the left edge
    line.setPosition( point1 );         // Position the rectangle
    line.setRotation( sf::degrees(angle) );         // Rotate the rectangle
    // line.setFillColor(color);        // Set the color
  }
  
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    states.transform *= this->getTransform();

    target.draw(this->line, states);
  }
  
  void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {}
  
};
