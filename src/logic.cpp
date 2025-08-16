#include <SFML/Graphics.hpp>

#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>

#include "includes/widget.hpp"
#include "includes/structures.hpp"

float getMagnitude(const sf::Vector2f& vector) {
  return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

Map initLogic() {
  srand(time(0));
  
  Map new_map;
  
  new_map.insertCity( City("A") );
  new_map.insertCity( City("B") );
  new_map.insertCity( City("C") );
  new_map.insertCity( City("D") );
  new_map.insertCity( City("E") );
  // new_map.insertCity( City("F") );
  // new_map.insertCity( City("G") );
  // new_map.insertCity( City("H") );
  
  new_map.insertConnection( new_map.getCity("A"), new_map.getCity("B") );
  new_map.insertConnection( new_map.getCity("B"), new_map.getCity("C") );
  new_map.insertConnection( new_map.getCity("C"), new_map.getCity("D") );
  
  return new_map;
}

void mainLogic(Map &p_map) {
  for(City &c : p_map.cities) {
  
    for(City &other_c : p_map.cities) {
      if(c.name == other_c.name) continue;
      
      sf::Vector2f difference = (other_c.position - c.position);
      
      difference *= getMagnitude(difference) - 80.0f;
      
      c.velocity += difference * 0.01f;
    }
    
    c.velocity = c.velocity * 0.6f;
  
    c.position += c.velocity;
    
    c.velocity.x = std::clamp(c.velocity.x, -10.0f, 10.0f);
    c.velocity.y = std::clamp(c.velocity.y, -10.0f, 10.0f);
  }
}
