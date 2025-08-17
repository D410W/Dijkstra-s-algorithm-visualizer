#pragma once

#include <SFML/System/Vector2.hpp>

#include "widget.hpp"

class CityWidget : public Widget {
private:
  sf::CircleShape circleBackground;
  sf::Text name;
  
public:
  CityWidget(sf::Font &p_font, std::string p_name, int size = 20) : circleBackground(20.0f), name(p_font) {
    name.setString(p_name);
    name.setCharacterSize(size);

    name.setFillColor(sf::Color::White);
    name.setOutlineColor(sf::Color::Black);
    name.setOutlineThickness(2.f);
  }
  
  void changePosition(sf::Vector2f p_position) {
    this->setPosition(p_position - sf::Vector2f(circleBackground.getRadius(), circleBackground.getRadius()));
  }
  
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    states.transform *= this->getTransform();

    target.draw(circleBackground, states);
    target.draw(name, states);
  }
  
  void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {}
  
};
