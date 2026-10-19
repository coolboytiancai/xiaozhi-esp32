#ifndef POMODORO_H
#define POMODORO_H
#include <stdbool.h>

void pomodoro_init(void);
void pomodoro_start(int work_min);
void pomodoro_stop(void);
bool pomodoro_is_running(void);

#endif
