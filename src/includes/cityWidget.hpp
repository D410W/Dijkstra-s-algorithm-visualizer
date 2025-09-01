#pragma once

#include <SFML/System/Vector2.hpp>

#include "widget.hpp"

class CityWidget : public Widget {
private:
  sf::CircleShape circle_background;
  sf::Text name;
  sf::Text cost;
  // TODO: add a back path indicator
  
public:
  CityWidget(sf::Font &p_font, std::string p_name, int size = 20) :
            circle_background(20.0f), name(p_font), cost(p_font) {
    name.setString(p_name);
    name.setCharacterSize(size);

    name.setFillColor(sf::Color::White);
    name.setOutlineColor(sf::Color::Black);
    name.setOutlineThickness(2.f);
    
    cost.setCharacterSize((int)(size*0.75f));

    cost.setFillColor(sf::Color::White);
    cost.setOutlineColor(sf::Color::Black);
    cost.setOutlineThickness(2.f);

  }
  
  void setFillColor(sf::Color new_color) {
    this->circle_background.setFillColor(new_color);
  }
  
  void changePosition(sf::Vector2f p_position) {
    this->setPosition(p_position - sf::Vector2f(circle_background.getRadius(), circle_background.getRadius()));
  }
  
  void updateCost(int cost) {
    if (cost == INT_MAX) this->cost.setString("INF");
    else this->cost.setString(std::to_string(cost));
  }
  
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    states.transform *= this->getTransform();

    target.draw(circle_background, states);
    target.draw(name, states);
    states.transform.translate(sf::Vector2f{5.f, 20.f});
    target.draw(cost, states);
  }
  
  void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {}
  
};
