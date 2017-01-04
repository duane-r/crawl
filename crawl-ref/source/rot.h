/**
 * @file
 * @brief Functions for blood & chunk rot.
 **/

#ifndef ROT_H
#define ROT_H

// aut / rot_time_factor = units on corpse "special" property
#define ROT_TIME_FACTOR 20

// aut until fresh chunks rot away
#define FRESHEST_CHUNK  2200
// # of special units until fresh corpses rot away
#define FRESHEST_CORPSE (FRESHEST_CHUNK / ROT_TIME_FACTOR)
// aut until fresh blood potions rot away
#define FRESHEST_BLOOD 22500

void rot_floor_items(int elapsedTime);


#endif
