#pragma once

#include <chrono>
#include <random>

#include <json/json.h>

#include "cityStructures.hpp"

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
  City *begin_city;
  City *end_city;

  TimeStamp time_stamp;
  
public:
  Algo(Json::Value config_json, Map &p_map) : my_map(&p_map), time_stamp(config_json["time_step_milliseconds"].asInt()) {
    this->begin_city = this->my_map->getCity(config_json["begin_city"].asString());
    this->end_city = this->my_map->getCity(config_json["end_city"].asString());
      
    this->time_stamp.value = this->time_stamp.value % this->time_stamp.ms_step;
  }
  
  void update() {
    if (time_stamp.update()) {
      
      std::cout << "update!" << '\n';
      my_map->cities[rand() % my_map->cities.size()].color = sf::Color(rand()%256, rand()%256, rand()%256);
      
    }
  }
};
