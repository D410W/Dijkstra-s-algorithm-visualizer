// #include <ctime>

#include <SFML/Graphics.hpp>
#include <json/json.h>

#include "widget.hpp"
#include "cityStructures.hpp"

Map initSimulation(Json::Value city_config);

void mainSimulation(Map &p_map, Json::Value sim_config, bool unstable = false);
