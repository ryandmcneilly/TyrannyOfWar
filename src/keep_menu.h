#ifndef KEEP_MENU_H
#define KEEP_MENU_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "unit.h"

typedef struct {
    bool hasMenu;
    float health;
    enum UnitType production[5];
    int unitNo;
} Menu;

#endif