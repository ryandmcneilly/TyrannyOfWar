#include "unit.h"
#include <assert.h>

UnitStats* get_unit_stat(enum UnitType unitType) {
    UnitStats* stats = malloc(sizeof(UnitStats));
    switch (unitType) {
        case WARRIOR:
            *stats = (UnitStats){ .health = 100, .attack = 1, .cost = 5, .movement = 2};
            break;
        case NUM_UNITS:
            assert(0 && "Invalid usage.\n");
    }
    return stats;
}


Unit create_unit(enum UnitType unitType) {
    Unit unit = {0};
    unit.unitType = WARRIOR;
    unit.stats = get_unit_stat(unitType); 
    return unit;
}


void free_unit(Unit* unit) {
    free(unit->stats);
    free(unit);
}
