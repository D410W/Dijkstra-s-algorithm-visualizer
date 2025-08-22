#include <ctime>

#include <SFML/Graphics.hpp>
#include <json/json.h>

#include "widget.hpp"
#include "cityStructures.hpp"

Map initLogic(Json::Value city_config);

void mainLogic(time_t startTime, Map &p_map, Json::Value sim_config);
