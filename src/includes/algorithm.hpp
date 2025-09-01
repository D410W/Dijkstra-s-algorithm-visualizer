#pragma once

#include <chrono>
#include <random>
#include <sstream>

#include <json/json.h>

#include "cityStructures.hpp"
#include "dijkstras_steps.hpp"

void trim(std::string& s) {

    // auto rbegin = s.rbegin();
    // if (std::isspace(*rbegin)) s.erase(s.length(), 1);
    auto begin = s.begin();
    if (std::isspace(*begin)) s.erase(0, 1);
    
}

long get_time_ms() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

struct TimeStamp {
  long value;
  long latest_time;
  
  int ms_step;
  
  TimeStamp(int p_ms_step) : value( get_time_ms() ), latest_time(this->value), ms_step(p_ms_step) {}
  
  bool update() {
    long current_time_ms = get_time_ms();
    
    value += current_time_ms - latest_time;
    latest_time = current_time_ms;
    
    if (value > ms_step) {
      value -= ms_step;
      return true;
    }
    
    return false;
  }
};

class Algo {
private:
  Map *my_map;
  std::string begin_city;
  std::string end_city;
  
  // std::string dijkstras_steps = "";
  std::stringstream dijkstras_steps;

  TimeStamp time_stamp;
  
public:
  Algo(Json::Value config_json, Map &p_map) : my_map(&p_map), time_stamp(config_json["time_step_milliseconds"].asInt()) {
    this->begin_city = this->my_map->getCity(config_json["begin_city"].asString())->name;
    this->end_city = this->my_map->getCity(config_json["end_city"].asString())->name;
      
    this->time_stamp.value = this->time_stamp.value % this->time_stamp.ms_step;
    
    this->dijkstras_steps = std::stringstream( calculate_dijkstras_steps(this->my_map, this->begin_city, this->end_city) );
    
    std::cout << this->dijkstras_steps.str();
  }
  
  void update() {
    if (time_stamp.update()) {
      
      std::string command = "";
      std::string command_city = "";
      dijkstras_steps >> command;
      
      if (command == "checking") {
        std::getline(dijkstras_steps, command_city);
        trim(command_city);
        
        my_map->getCity(command_city)->color = sf::Color(255,255,0);
      } else if (command == "checked") {
        std::getline(dijkstras_steps, command_city);
        trim(command_city);

        my_map->getCity(command_city)->color = sf::Color(0,255,0);
      } else if (command == "updcost") {
        int new_cost{};
        dijkstras_steps >> new_cost;
        
        std::string command_back_path = "";
        std::getline(dijkstras_steps, command_back_path);
        trim(command_back_path);
        
        std::getline(dijkstras_steps, command_city);
        trim(command_city);
        
        my_map->getCity(command_city)->cost_view = new_cost;
        my_map->getCity(command_city)->back_path = command_back_path;
      } else if (command == "done") {
        std::getline(dijkstras_steps, command_city);
        trim(command_city);
        
        std::string next = my_map->getCity(command_city)->back_path;
        
        while (command_city != next) {
          Connection *con = my_map->getConnection(command_city, next);
          
          con->color = sf::Color(0, 200, 0);
          
          command_city = next;
          next = my_map->getCity(command_city)->back_path;
        }
      }
      
      // my_map->cities[rand() % my_map->cities.size()].color = sf::Color(rand()%256, rand()%256, rand()%256);
    }
  }
};
