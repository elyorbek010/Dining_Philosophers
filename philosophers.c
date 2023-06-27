#include "philosophers.h"
#include "logs.h"

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>

pthread_barrier_t cycle_start; // philosophers wait cycle start each cycle

static atomic_size_t cur_cycle = 0;  // counter controlled by main
static atomic_uint cnt_finished = 0; // number of philosophers finished
static atomic_bool exit_flag = 0;    // flag is up when everybody finished

pthread_mutex_t silverware[PHILOSOPHERS_N]; // either fork or knife

enum philosopher_state
{
    THINK,
    GET_SILVERWARE_1,
    GET_SILVERWARE_2,
    EAT,
    FINISHED
};

struct philosopher_ctx
{
    size_t id; // unique ID of every philosopher

    uint had_courses; // how many courses philosopher had
    uint cycles_left; // how many cycles of thinking or eating left

    size_t silverware_1; // fork or knife
    size_t silverware_2;

    enum philosopher_state state;
};

static void philosopher_state_transition(struct philosopher_ctx *philosopher, enum philosopher_state new_state);

static void my_log(struct philosopher_ctx philosopher);

static bool try_to_take_silverware(size_t silverware_idx)
{
    return pthread_mutex_trylock(&silverware[silverware_idx]) == 0;
}

static void release_silverware(size_t silverware_idx)
{
    pthread_mutex_unlock(&silverware[silverware_idx]);
}

void *philosopher_routine(void *arg)
{
    size_t id = (size_t)arg;
    struct philosopher_ctx philosopher = {
        .id = id,
        .had_courses = 0,
        .cycles_left = 0,
        .silverware_1 = (id + id % 2) % PHILOSOPHERS_N,
        .silverware_2 = (id + 1 - id % 2) % PHILOSOPHERS_N,
        .state = 0,
    };

    philosopher_state_transition(&philosopher, THINK);

    while (!philosophers_finished())
    {
        pthread_barrier_wait(&cycle_start);

        my_log(philosopher);

        switch (philosopher.state)
        {
        case THINK:
        {
            philosopher.cycles_left--;

            if (philosopher.cycles_left == 0)
                philosopher_state_transition(&philosopher, GET_SILVERWARE_1);

            break;
        }

        case GET_SILVERWARE_1:
        {
            if (try_to_take_silverware(philosopher.silverware_1))
                philosopher_state_transition(&philosopher, GET_SILVERWARE_2);
            else
                philosopher_state_transition(&philosopher, THINK);

            break;
        }

        case GET_SILVERWARE_2:
        {
            if (try_to_take_silverware(philosopher.silverware_2))
            {
                philosopher_state_transition(&philosopher, EAT);
            }
            else
            {
                release_silverware(philosopher.silverware_1);
                philosopher_state_transition(&philosopher, THINK);
            }
            break;
        }

        case EAT:
        {
            philosopher.cycles_left--;

            if (philosopher.cycles_left == 0)
            {
                philosopher_state_transition(&philosopher, THINK);

                release_silverware(philosopher.silverware_1);
                release_silverware(philosopher.silverware_2);

                philosopher.had_courses++;
                if (philosopher.had_courses == TOTAL_MEAL_COURSES_N)
                {
                    atomic_fetch_add(&cnt_finished, 1);
                    philosopher_state_transition(&philosopher, FINISHED);
                }
                else
                {
                    philosopher_state_transition(&philosopher, THINK);
                }
            }
            break;
        }

        case FINISHED:
        {
            // do nothing, keep looping to keep other philosophers company, till everybody finished
            break;
        }
        }
    }
}

void *administrator_routine(void *arg)
{
    // control pulse clock(cycles)
    while (cnt_finished < PHILOSOPHERS_N)
    {
        pthread_barrier_wait(&cycle_start);
        usleep(CYCLE_TIME_US);
        cur_cycle++;
    }

    atomic_store_explicit(&exit_flag, 1, memory_order_release);
    pthread_barrier_wait(&cycle_start); // final cycle, everyone exits
}

static void philosopher_state_transition(struct philosopher_ctx *philosopher, enum philosopher_state new_state)
{
    switch (new_state)
    {
    case THINK:
        philosopher->state = THINK;
        philosopher->cycles_left = think_cycles();
        break;
    case GET_SILVERWARE_1:
        philosopher->state = GET_SILVERWARE_1;
        break;
    case GET_SILVERWARE_2:
        philosopher->state = GET_SILVERWARE_2;
        break;
    case EAT:
        philosopher->state = EAT;
        philosopher->cycles_left = think_cycles();
        break;
    case FINISHED:
        philosopher->state = FINISHED;
        break;
    }
}

void philosophers_create(void)
{
    pthread_t thread;
    pthread_barrier_init(&cycle_start, NULL, PHILOSOPHERS_N + 1); // philosophers + administrator

    for (size_t i = 0; i < PHILOSOPHERS_N; i++)
    {
        pthread_create(&thread, NULL, philosopher_routine, (void *)i);
        pthread_detach(thread);
        pthread_mutex_init(&silverware[i], NULL);
    }

    pthread_create(&thread, NULL, administrator_routine, NULL);
    pthread_detach(thread);
}

void philosophers_destroy(void)
{
    pthread_barrier_destroy(&cycle_start);

    for (size_t i = 0; i < PHILOSOPHERS_N; i++)
    {
        pthread_mutex_destroy(&silverware[i]);
    }

    save_logs();
}

bool philosophers_finished(void)
{
    return atomic_load_explicit(&exit_flag, memory_order_acquire);
}

static void my_log(struct philosopher_ctx philosopher)
{
    switch (philosopher.state)
    {
    case THINK:
        log_thinking(philosopher.id, cur_cycle);
        break;
    case GET_SILVERWARE_1:
        log_getting_silverware(philosopher.id, cur_cycle, philosopher.silverware_1);
        break;
    case GET_SILVERWARE_2:
        log_getting_silverware(philosopher.id, cur_cycle, philosopher.silverware_2);
        break;
    case EAT:
        log_eating(philosopher.id, cur_cycle);
        break;
    case FINISHED:
        break;
    }
}