#ifndef LOGS_H
#define LOGS_H

#include <stddef.h>

#define LOG_FILE_NAME "logs.txt"

#define MAX_LOG_ROWS 100
#define MAX_LOG_COLUMNS 1024

void log_init(void);

void log_thinking(size_t id, size_t cycle);

void log_getting_silverware(size_t id, size_t cycle, size_t silverware);

void log_eating(size_t id, size_t cycle);

void log_end(size_t id, size_t cycle);

void save_logs(void);

#endif // LOGS_H