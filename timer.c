//
// Created by flasque on 24/06/2022.
//

#include <stdio.h>
#include "timer.h"

void startTimer()
{
    _timer._start = clock();
}

void stopTimer()
{
    _timer._end = clock();
}

void displayTime()
{
    _timer._msecs = (1000.0 * (double) (_timer._end - _timer._start)) / CLOCKS_PER_SEC;
    int msecs = (int) (_timer._msecs) % 1000;
    int secs = (int) (_timer._msecs) / 1000;

    printf("%d s %d ms\n", secs, msecs);
}