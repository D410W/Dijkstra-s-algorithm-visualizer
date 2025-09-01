#include <vector>
#include <sstream>

#include "cityStructures.hpp"

std::string calculate_dijkstras_steps(Map *p_map, std::string begin_city, std::string end_city) {
  std::stringstream oss;
  
  City *checking_city = p_map->getCity(begin_city);
  checking_city->cost = 0;
  
  oss << "updcost " << "0 " << checking_city->name << '\n' << checking_city->name << '\n';
  
  while (true) {
  
    checking_city->checked = true;
    
    // checking_city->color = sf::Color(0,255,0);
    if (checking_city->name == end_city) {
      oss << "checked " << checking_city->name << '\n';
      oss << "done " << checking_city->name << "\n";
      break;
    }
    
    oss << "checking " << checking_city->name << '\n';
    
    for (auto &c : checking_city->connections) {
      // std::cout << c.first << ' ' << c.second << '\n';
      
      City *city_update_cost = p_map->getCity(c.first);
      
      if (city_update_cost->checked) continue;
      
      if (city_update_cost->cost > checking_city->cost + c.second) {
        city_update_cost->cost = checking_city->cost + c.second;
        // city_update_cost->back_path = checking_city->name;
        
        oss << "updcost " << city_update_cost->cost << ' '
            << checking_city->name << '\n' << city_update_cost->name << '\n';
      }
    }
    
    City *least_cost = nullptr;
    
    for (City &c : p_map->cities) {
      if (c.checked) continue;
      if (least_cost == nullptr) least_cost = &c;
      else if (c.cost < least_cost->cost) least_cost = &c;
    }
    
    oss << "checked " << checking_city->name << '\n';
    
    checking_city = least_cost;
  }
  
  return oss.str();
}
