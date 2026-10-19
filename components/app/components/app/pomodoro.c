#include "pomodoro.h"
#include "display/display.h"
#include "esp_timer.h"
#include <stdio.h>

static bool pomo_running = false;
static int pomo_total_sec = 0;
static esp_timer_handle_t pomo_timer;

static void pomo_timer_cb(void *arg)
{
    if(pomo_total_sec <=0)
    {
        pomo_running = false;
        display_clear();
        display_draw_string(40,100,"番茄时间结束！");
        display_refresh();
        return;
    }
    int min = pomo_total_sec /60;
    int sec = pomo_total_sec %60;
    char buf[64];
    sprintf(buf,"%02d:%02d",min,sec);
    display_clear();
    display_draw_string(60,100,"🍅 番茄钟");
    display_draw_string(60,160,buf);
    display_refresh();
    pomo_total_sec--;
}

void pomodoro_init(void)
{
    pomo_running = false;
    pomo_total_sec =0;
    esp_timer_create_args_t cfg = {
        .callback = pomo_timer_cb,
        .name = "pomodoro"
    };
    esp_timer_create(&cfg, &pomo_timer);
}

void pomodoro_start(int work_min)
{
    if(pomo_running) esp_timer_stop(pomo_timer);
    pomo_total_sec = work_min *60;
    pomo_running = true;
    esp_timer_start_periodic(pomo_timer, 1000000);
}

void pomodoro_stop(void)
{
    if(pomo_running){
        esp_timer_stop(pomo_timer);
        pomo_running = false;
        display_clear();
        display_refresh();
    }
}

bool pomodoro_is_running(void)
{
    return pomo_running;
}
