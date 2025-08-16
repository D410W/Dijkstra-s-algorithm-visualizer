#pragma once

#include <vector>
#include <utility>
#include <string>
#include <climits>
#include <random>

#include <SFML/System/Vector2.hpp>

struct City {
  std::string name;
  int cost = INT_MAX;
  
  std::vector<City*> my_connections;
  
  sf::Vector2f position;
  sf::Vector2f velocity;
  
  City(std::string p_name) : name(p_name), position(200.0f + float(rand()%20), 200.0f), velocity(0.0f, float(rand()%20)) {}
};

struct Connection {
  City *first;
  City *second;
  int cost;
  
  Connection(City *p_first, City *p_second) : first(p_first), second(p_second) {}
};

struct Map {
  // sf::Vector2f character_pos;
  std::vector<City> cities;
  std::vector<Connection> connections;
  
  City* getCity(std::string p_name) {
    for(int i = 0; i < this->cities.size(); i++) {
      if(this->cities[i].name == p_name) {
        return &(this->cities[i]);
      }
    }
    throw std::invalid_argument( "Did not find city named: " + p_name );
  }
  
  void insertCity(City p_city) {
    this->cities.push_back(p_city);
  }
  
  void insertConnection(City *first, City *second) {
    this->connections.push_back( Connection(first, second) );
  }
};
