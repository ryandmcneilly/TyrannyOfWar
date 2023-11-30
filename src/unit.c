#include "unit.h"


Unit create_unit(enum UnitType unitType) {
    Unit unit = {0};
    unit.unitType = WARRIOR;
    return unit;
}

UnitStats get_unit_stat(enum UnitType unitType) {
    switch (unitType) {
        case WARRIOR:
            UnitStats uniStates = {.health = 69};
        return uniStates;

        default:
            break;
    }
}

