#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "includes/logic.hpp"
#include "includes/structures.hpp"
#include "includes/cityWidget.hpp"

void updateCityWidgets(Map &my_map, std::vector<CityWidget> &cityWidgets) {
  for(int i = 0; i < my_map.cities.size(); ++i) {
    cityWidgets[i].setPosition(my_map.cities[i].position); 
    // std::cout << my_map.cities[i].velocity.x << ' ' << my_map.cities[i].velocity.y << '\n';
  }
}

int main(){

  unsigned int windowWidth = 800, windowHeight = 600;
  sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Dijkstra's", sf::Style::Default);
  window.setVerticalSyncEnabled(true);
  
  Map my_map = initLogic();
  
  std::vector<CityWidget> cityWidgets;
  
  for(City &c : my_map.cities) {
    cityWidgets.push_back(CityWidget(c.position));
  }

  while (window.isOpen()){
    
    while (const auto event = window.pollEvent()){
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    
    mainLogic(my_map);
    updateCityWidgets(my_map, cityWidgets);
    
    //---------------

    window.clear(sf::Color(18,18,18));
    
    for(CityWidget &cw : cityWidgets) window.draw(cw);
    // for(const auto &ns : scrollers) window.draw(*ns);
    
    window.display();
  }
  
  return 0;
}
