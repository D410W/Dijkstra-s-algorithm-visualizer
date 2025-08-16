#pragma once

#include <SFML/System/Vector2.hpp>

#include <algorithm>

#include "widget.hpp"

class Character : public Widget {
private:
  sf::RectangleShape background;
  
  sf::FloatRect getGlobalBounds() const {
    const sf::Transform& parentTransform = this->getTransform();
    return parentTransform.transformRect( background.getGlobalBounds() );
  }
  
public:
  Character() {
    
  }
  
  // methods:
  
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    // Apply the widget's transform (position, rotation, scale)
    states.transform *= this->getTransform();

    // Draw the components of the button
    target.draw(background, states);
  }
  
  void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {
    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
      if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
      
        sf::Vector2f mousePos = window.mapPixelToCoords({mouseButtonPressed->position.x, mouseButtonPressed->position.y});

        if (this->getGlobalBounds().contains(mousePos)) {
          *(this->activeID) = this->myID;
        }
        
      }
    }
  }
  
};

