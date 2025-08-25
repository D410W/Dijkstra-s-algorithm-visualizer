#include <cmath>
#include <iostream>
#include <fstream>
#include <ctime>

#include <json/json.h>
#include <SFML/Graphics.hpp>

#include "includes/simulation.hpp"
#include "includes/cityStructures.hpp"
#include "includes/cityWidget.hpp"
#include "includes/connectionWidget.hpp"

Json::Value loadJson(std::string file_location){
  std::ifstream settingsFile(file_location, std::ifstream::binary);
  if (!settingsFile.is_open()) {
    std::cerr << "Error opening JSON file!" << std::endl;
    return 1;
  }
  
  Json::Value root;
  Json::CharReaderBuilder readerBuilder;
  std::string errors;

  bool parsingSuccessful = Json::parseFromStream(readerBuilder, settingsFile, &root, &errors);
  if (!parsingSuccessful) {
    std::cerr << "Error parsing JSON: " << errors << std::endl;
    return 1;
  }
  
  return root;
}

void updateCityWidgets(Map &my_map, std::vector<CityWidget> &cityWidgets) {
  for(int i = 0; i < (int)my_map.cities.size(); ++i) {
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
  sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Dijkstra's", sf::Style::Titlebar);
  window.setVerticalSyncEnabled(true);
  window.setPosition(sf::Vector2i(50, 50));
  
  sf::Font font("assets/arial.ttf");
  
  // initialization of simulation objects:
  
  Json::Value simulation_config_json = loadJson("dijkstras_config.json");
  Json::Value map_config = loadJson("map_config.json");
  Map my_map = initSimulation(map_config);
  
  int unstable_frames = simulation_config_json["unstable_frames"].asInt();
  for (int i = 0; i < unstable_frames; ++i) mainSimulation(my_map, simulation_config_json, true);
  
  // std::cout << simulation_config_json["stableTime"].asInt() << '\n';
  
  // initialization of drawable objects (widgets):
  
  std::vector<CityWidget> cityWidgets;
  std::vector<ConnectionWidget> connectionWidgets;
  
  for(City &c : my_map.cities) {
    cityWidgets.push_back(CityWidget(font, c.name));
  }

  for(Connection &con : my_map.connections) {
    connectionWidgets.push_back(
      ConnectionWidget( my_map.getCity(con.first), my_map.getCity(con.second), font, con.cost)
    );
  }

  while (window.isOpen()){
    
    while (const auto event = window.pollEvent()){
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    
    mainSimulation(my_map, simulation_config_json); // simulation step function
    centerCities(my_map, sf::Vector2f(windowWidth/2.f, windowHeight/2.f));
    updateCityWidgets(my_map, cityWidgets); // update widgets
    
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
