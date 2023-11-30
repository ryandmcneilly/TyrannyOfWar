#include "keep_menu.h"

void addProduction (Menu* menu, enum UnitType unitType) {
    menu->production[menu->unitNo] = unitType;
}

