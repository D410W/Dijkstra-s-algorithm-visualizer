#pragma once

#include <vector>
#include <utility>
#include <string>
#include <climits>
#include <random>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

struct City {
  std::string name;
  int cost = INT_MAX;
  int cost_view = INT_MAX;
  std::string back_path = "";
  bool checked = false;
  sf::Color color = sf::Color::White;
  
  std::vector<std::pair<std::string, int>> connections;
  
  sf::Vector2f position;
  sf::Vector2f velocity;
  
  City(std::string p_name) : name(p_name), position(200.0f + float(rand()%20), 200.0f), velocity(0.0f, float(rand()%20)) {}
};

struct Connection {
  std::string first;
  std::string second;
  int cost;
  sf::Color color = sf::Color::White;
  
  Connection(City &p_first, City &p_second, int p_cost) : first(p_first.name), second(p_second.name), cost(p_cost) {}
};

struct Map {
  // sf::Vector2f character_pos;
  std::vector<City> cities;
  std::vector<Connection> connections;
  
  City* getCity(std::string p_name) {
    for (int i = 0; i < (int)this->cities.size(); i++) {
      if (this->cities[i].name == p_name) {
        return &(this->cities[i]);
      }
    }
    throw std::invalid_argument( "Did not find city named: \'" + p_name + "\'" );
  }
  
  Connection* getConnection(std::string p_name1, std::string p_name2) {
    for (int i = 0; i < (int)this->connections.size(); i++) {
      if (this->connections[i].first == p_name1 &&
         this->connections[i].second == p_name2) {
         
        return &(this->connections[i]);
      
      } else if(this->connections[i].first == p_name2 &&
             this->connections[i].second == p_name1) {
      
        return &(this->connections[i]);
      
      }
    }
    throw std::invalid_argument( "Did not find connecton: \'" + p_name1 + "\' & \'" + p_name2 + "\'" );
  }
  
  void insertCity(City p_city) {
    this->cities.push_back(p_city);
  }
  
  void insertConnection(City *first, City *second, int p_cost) {
    this->connections.push_back( Connection(*first, *second, p_cost) );
    first->connections.push_back( {second->name, p_cost} );
    second->connections.push_back( {first->name, p_cost} );
  }
};
