#ifndef UNIT_H
#define UNIT_H

#include <stdlib.h>

enum UnitType {
    WARRIOR = 0,
    NUM_UNITS,
};

typedef struct {
    float  health;
    float  attack;
    size_t cost;
    size_t movement;
} UnitStats;


typedef struct  {
    enum UnitType unitType;
    size_t row;
    size_t col;
    UnitStats* stats;
} Unit;


Unit create_unit(enum UnitType unitType);


#endif
