#include <vector>
#include <sstream>

#include "cityStructures.hpp"

std::string calculate_dijkstras_steps(Map *p_map, std::string begin_city, std::string end_city) {
  std::stringstream oss;
  
  City *checking_city = p_map->getCity(begin_city);
  checking_city->cost = 0;
  
  while (true) {
    
    for (auto &c : checking_city->connections) {
      std::cout << c.first << ' ' << c.second << '\n';
    }
    
    City *least_cost = &p_map->cities[0];
    
    break;
    
    for (City &c : p_map->cities) {
      if (c.cost < least_cost->cost) least_cost = &c;
    }
  }
  
  return oss.str();
}
