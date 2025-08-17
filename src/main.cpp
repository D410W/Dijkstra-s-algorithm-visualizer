#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "includes/logic.hpp"
#include "includes/structures.hpp"
#include "includes/cityWidget.hpp"
#include "includes/connectionWidget.hpp"

void updateCityWidgets(Map &my_map, std::vector<CityWidget> &cityWidgets) {
  for(int i = 0; i < my_map.cities.size(); ++i) {
    cityWidgets[i].changePosition(my_map.cities[i].position); 
    // std::cout << my_map.cities[i].velocity.x << ' ' << my_map.cities[i].velocity.y << '\n';
  }
}

void centerCities(Map &my_map, sf::Vector2f center) {
  sf::Vector2f centerOfMass(0.f, 0.f);

  for(City &c : my_map.cities) {
    centerOfMass += c.position;
  }

  centerOfMass /= float( my_map.cities.size() );

  sf::Vector2f difference = center - centerOfMass;

  for(City &c : my_map.cities) {
    c.position += difference;
  }
}

int main(){

  unsigned int windowWidth = 800, windowHeight = 600;
  sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Dijkstra's", sf::Style::Default);
  window.setVerticalSyncEnabled(true);

  window.setPosition(sf::Vector2i(50, 50));

  sf::Font font("../src/arial.ttf");

  Map my_map = initLogic();
  
  std::vector<CityWidget> cityWidgets;
  std::vector<ConnectionWidget> connectionWidgets;
  
  for(City &c : my_map.cities) {
    cityWidgets.push_back(CityWidget(font, c.name));
  }

  for(Connection &con : my_map.connections) {
    connectionWidgets.push_back(ConnectionWidget( my_map.getCity(con.first), my_map.getCity(con.second) ));
  }

  while (window.isOpen()){
    
    while (const auto event = window.pollEvent()){
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    
    mainLogic(my_map);
    centerCities(my_map, sf::Vector2f(windowWidth/2.f, windowHeight/2.f));
    updateCityWidgets(my_map, cityWidgets);
    
    //---------------

    window.clear(sf::Color(18,18,18));
    
    for(ConnectionWidget &conw : connectionWidgets) {
      conw.updatePosition();
      window.draw(conw);
    }
    for(CityWidget &cw : cityWidgets) window.draw(cw);
    
    window.display();
  }
  
  return 0;
}
