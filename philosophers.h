#ifndef PHILOSOPHERS_H
#define PHLOSOPHERS_H

#include "stdbool.h"

#define CYCLE_TIME_US 1000 // time should be enough for all philosophers to finish their job

#define eat_cycles() (3 + rand() % 7)   // cycle length [3, 9]
#define think_cycles() (3 + rand() % 7) // cycle length [3, 9]

#define PHILOSOPHERS_N 5
#define TOTAL_MEAL_COURSES_N 3

void philosophers_create(void);

void philosophers_destroy(void);

bool philosophers_finished(void);

#endif // PHILOSOPHERS_H