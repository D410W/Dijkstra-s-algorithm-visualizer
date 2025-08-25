// #include <ctime>

#include <SFML/Graphics.hpp>
#include <json/json.h>

#include "widget.hpp"
#include "cityStructures.hpp"

Map initLogic(Json::Value city_config);

void mainLogic(Map &p_map, Json::Value sim_config, bool unstable = false);
