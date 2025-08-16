#pragma once

#include <SFML/System/Vector2.hpp>

#include "widget.hpp"

class CityWidget : public Widget {
private:
  sf::CircleShape circleBackground;
  
public:
  CityWidget(sf::Vector2f p_position) : circleBackground(20.0f) {
    this->setPosition(p_position);
  }
  
  void changePosition(sf::Vector2f p_position) {
    this->setPosition(p_position);
  }
  
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    states.transform *= this->getTransform();

    target.draw(circleBackground, states);
  }
  
  void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {}
  
};
