#include "philosophers.h"
#include <unistd.h>

void main(void)
{
    philosophers_create();

    while (!philosophers_finished())
        usleep(CYCLE_TIME_US*10);

    philosophers_destroy();
}