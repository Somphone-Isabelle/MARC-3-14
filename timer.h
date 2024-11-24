//
// Created by flasque on 24/06/2022.
//

#ifndef UNTITLED1_TIMER_H
#define UNTITLED1_TIMER_H

#include <time.h>

typedef struct s_timer
{
    clock_t _start;
    clock_t _end;
    double _msecs;
} t_timer;

static t_timer _timer;

void startTimer();

void stopTimer();

void displayTime();

#endif //UNTITLED1_TIMER_H
