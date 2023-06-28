#include "philosophers.h"
#include <unistd.h>

void main(void)
{
    philosophers_create();

    while (!philosophers_finished())
        sleep(1);

    philosophers_destroy();
}