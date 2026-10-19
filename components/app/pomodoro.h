#ifndef __POMODORO_H__
#define __POMODORO_H__

#include <stdbool.h>

// 番茄钟状态
typedef enum {
    POMO_STOP = 0,
    POMO_WORK,
    POMO_REST
} PomodoroState;

void pomodoro_init(void);
void pomodoro_start(int work_sec, int rest_sec);
void pomodoro_stop(void);
void pomodoro_tick(void); // 1s调用一次
bool pomodoro_is_running(void);
// 刷新墨水屏显示
void pomodoro_refresh_screen(void);

#endif
