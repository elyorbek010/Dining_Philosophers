#include "logs.h"

#include <stdio.h>

#define EATING_SYMBOL 'E'
#define THINKING_SYMBOL '_'
#define TRYING_TO_GET_LEFT_SILVERWARE_SYMBOL 'L'
#define TRYING_TO_GET_RIGHT_SILVERWARE_SYMBOL 'R'

static char my_log[MAX_LOG_ROWS][MAX_LOG_COLUMNS];

void log_thinking(size_t id, size_t cycle)
{
    my_log[id][cycle] = THINKING_SYMBOL;
}

void log_getting_silverware(size_t id, size_t cycle, size_t silverware)
{
   char fork_symbol = id == silverware ? TRYING_TO_GET_RIGHT_SILVERWARE_SYMBOL : TRYING_TO_GET_LEFT_SILVERWARE_SYMBOL;
   my_log[id][cycle] = fork_symbol;
}

void log_eating(size_t id, size_t cycle)
{
    my_log[id][cycle] = EATING_SYMBOL;
}

void save_logs(void)
{
    FILE *fp = fopen(LOG_FILE_NAME, "w");

    for (size_t i = 0; i < MAX_LOG_ROWS && my_log[i][0] != '\0'; i++)
    {
        fprintf(fp, "Philosopher %zu: %s\n", i, my_log[i]);
    }

    fclose(fp);
}