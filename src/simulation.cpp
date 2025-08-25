#include <random>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <ctime>

#include <json/json.h>
#include <SFML/Graphics.hpp>

#include "includes/widget.hpp"
#include "includes/cityStructures.hpp"

sf::Vector2f normalize(const sf::Vector2f& source)
{
    float length = std::sqrt(source.x * source.x + source.y * source.y);
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source; // Or handle the zero vector case appropriately
}

float getMagnitude(const sf::Vector2f& vector) {
  return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f vecpow(const sf::Vector2f& p_vector, float power) {
  return normalize(p_vector) * std::pow(getMagnitude(p_vector), power);
}

Map initSimulation(Json::Value map_config) {
  srand(time(0));
  
  Map new_map;
  
  for (Json::Value city_name : map_config["cities"])
    new_map.insertCity( City(city_name.asString()) );
  
  for (Json::Value connec : map_config["connections"])
    new_map.insertConnection( new_map.getCity(connec[0].asString()),
                              new_map.getCity(connec[1].asString()),
                              connec[2].asInt() );

  // new_map.insertConnection( new_map.getCity("A"), new_map.getCity("Natal"), 3 );
  // new_map.insertConnection( new_map.getCity("C"), new_map.getCity("Natal"), 3 );

  return new_map;
}

int frame = 0;

void mainSimulation(Map &p_map, Json::Value config, bool unstable = false) {

  float idealDistance = config["connection"]["idealDistance"].asFloat();
  float differenceMultiplier = config["connection"]["differenceMultiplier"].asFloat();
  float differencePower = config["connection"]["differencePower"].asFloat();
  
  float n_idealDistance = config["noConnection"]["idealDistance"].asFloat();
  float n_differenceMultiplier = config["noConnection"]["differenceMultiplier"].asFloat();
  float n_differencePower = config["noConnection"]["differencePower"].asFloat();
  
  float frictionMultiplier = 0.f;
  if (unstable) {
    frictionMultiplier = config["frictionMultiplier"].asFloat();
  } else { 
    frictionMultiplier = config["frictionMultiplierStable"].asFloat();
  }
  
  // std::cout << config["stableTime"].asInt() << '\n';

  for(City &c : p_map.cities) {
  
    for(City &other_c : p_map.cities) {
      if(c.name == other_c.name) continue;
      
      if(std::find(c.my_connections.begin(),
                   c.my_connections.end(),
                   other_c.name) != c.my_connections.end()) {
      
        sf::Vector2f difference = (other_c.position - c.position);

        difference = normalize(difference) * ( getMagnitude(difference) - idealDistance );
        
        c.velocity += vecpow(difference, differencePower) * differenceMultiplier;
      
      } else {
        sf::Vector2f difference = (other_c.position - c.position);
        
        if(getMagnitude(difference) > n_idealDistance) continue;

        difference = normalize(difference) * ( getMagnitude(difference) - n_idealDistance );

        c.velocity += vecpow(difference, n_differencePower) * n_differenceMultiplier;
      }
    }
    
    c.velocity = c.velocity * frictionMultiplier;
    
    c.position += c.velocity;
    
    c.velocity.x = std::clamp(c.velocity.x, -10.0f, 10.0f);
    c.velocity.y = std::clamp(c.velocity.y, -10.0f, 10.0f);
  }
}
