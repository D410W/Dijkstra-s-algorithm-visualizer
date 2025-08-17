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
  new_map.insertCity( City("F") );
  new_map.insertCity( City("G") );

  new_map.insertConnection( new_map.getCity("A"), new_map.getCity("C"), 3 );
  new_map.insertConnection( new_map.getCity("A"), new_map.getCity("F"), 2 );
  new_map.insertConnection( new_map.getCity("C"), new_map.getCity("F"), 2 );
  new_map.insertConnection( new_map.getCity("C"), new_map.getCity("E"), 1 );
  new_map.insertConnection( new_map.getCity("C"), new_map.getCity("D"), 4 );
  new_map.insertConnection( new_map.getCity("F"), new_map.getCity("E"), 3 );
  new_map.insertConnection( new_map.getCity("F"), new_map.getCity("B"), 6 );
  new_map.insertConnection( new_map.getCity("F"), new_map.getCity("G"), 5 );
  new_map.insertConnection( new_map.getCity("E"), new_map.getCity("B"), 2 );
  new_map.insertConnection( new_map.getCity("D"), new_map.getCity("B"), 1 );
  new_map.insertConnection( new_map.getCity("G"), new_map.getCity("B"), 2 );

  return new_map;
}

void mainLogic(Map &p_map) {

  float distance = 100.0f;

  for(City &c : p_map.cities) {
  
    for(City &other_c : p_map.cities) {
      if(c.name == other_c.name) continue;
      
      sf::Vector2f difference = (other_c.position - c.position);
      
      if(getMagnitude(difference) > distance)
	if(std::find(c.my_connections.begin(),
		     c.my_connections.end(),
		     other_c.name) == c.my_connections.end()) continue;


      difference *= getMagnitude(difference) - distance;
      
      c.velocity += difference * 0.01f;
    }
    
    c.velocity = c.velocity * 0.6f;
    
    c.position += c.velocity;
    
    c.velocity.x = std::clamp(c.velocity.x, -10.0f, 10.0f);
    c.velocity.y = std::clamp(c.velocity.y, -10.0f, 10.0f);
  }
}
