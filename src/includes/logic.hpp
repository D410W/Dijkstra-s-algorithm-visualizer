#include <SFML/Graphics.hpp>
#include <json/json.h>

#include "widget.hpp"
#include "structures.hpp"

Map initLogic();

void mainLogic(Map &p_map, Json::Value);
