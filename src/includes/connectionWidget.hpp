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
  sf::Text cost;
  
public:
  ConnectionWidget(City *p_first, City *p_second, sf::Font &p_font, int cost, int font_size = 16)
    : first(p_first), second(p_second), line(sf::Vector2f(0.f, 3.f)), cost(p_font) {
    
    this->cost.setString(std::to_string(cost));
    this->cost.setCharacterSize(font_size);

    this->cost.setFillColor(sf::Color::White);
    this->cost.setOutlineColor(sf::Color::Black);
    this->cost.setOutlineThickness(2.f);
  }
  
  void setFillColor(sf::Color new_color) {
    this->line.setFillColor(new_color);
  }
  
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
    
    cost.setPosition( (point1 + point2)/2.0f );
  }
  
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    states.transform *= this->getTransform();

    target.draw(this->line, states);
    target.draw(this->cost, states);
  }
  
  void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {}
  
};
