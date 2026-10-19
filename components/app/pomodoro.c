#include "pomodoro.h"
#include "display/display.h"
#include <stdio.h>

static PomodoroState pomo_state = POMO_STOP;
static int work_seconds = 0;
static int rest_seconds = 0;
static int current_sec = 0;

void pomodoro_init(void)
{
    pomo_state = POMO_STOP;
    current_sec = 0;
}

void pomodoro_start(int work_sec, int rest_sec)
{
    work_seconds = work_sec;
    rest_seconds = rest_sec;
    pomo_state = POMO_WORK;
    current_sec = work_seconds;
    pomodoro_refresh_screen();
}

void pomodoro_stop(void)
{
    pomo_state = POMO_STOP;
}

void pomodoro_tick(void)
{
    if(pomo_state == POMO_STOP) return;

    current_sec --;
    if(current_sec <= 0)
    {
        if(pomo_state == POMO_WORK)
        {
            // 工作结束，切换休息
            pomo_state = POMO_REST;
            current_sec = rest_seconds;
        }
        else
        {
            // 休息结束，停止
            pomo_state = POMO_STOP;
        }
    }
    pomodoro_refresh_screen();
}

bool pomodoro_is_running(void)
{
    return pomo_state != POMO_STOP;
}

void pomodoro_refresh_screen(void)
{
    display_clear();
    char buf[64];
    if(pomo_state == POMO_WORK)
    {
        snprintf(buf, sizeof(buf), "🍅 专注时间");
    }
    else if(pomo_state == POMO_REST)
    {
        snprintf(buf, sizeof(buf), "☕ 休息时间");
    }
    else
    {
        snprintf(buf, sizeof(buf), "番茄钟已停止");
    }
    display_draw_string(10,20,buf);

    int min = current_sec / 60;
    int sec = current_sec % 60;
    snprintf(buf, sizeof(buf), "%02d:%02d", min, sec);
    display_draw_string(10,60,buf);
    display_refresh();
}
