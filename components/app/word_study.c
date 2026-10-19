#include "word_study.h"
#include "display/display.h"
#include <stdio.h>

typedef struct {
    const char *eng;
    const char *chn;
} WordItem;

static const WordItem word_list[] = {
    {"apple", "苹果"},
    {"banana", "香蕉"},
    {"computer", "电脑"},
    {"book", "书籍"},
    {"study", "学习"},
    {"water", "水"},
    {"sun", "太阳"},
    {"moon", "月亮"},
};
static const int word_count = sizeof(word_list)/sizeof(WordItem);

static int word_idx = 0;
static bool word_active = false;

void word_study_init(void)
{
    word_idx = 0;
    word_active = false;
}

void word_study_start(void)
{
    word_active = true;
    word_idx = 0;
    word_study_refresh_screen();
}

void word_study_stop(void)
{
    word_active = false;
}

void word_study_next(void)
{
    if(!word_active) return;
    word_idx ++;
    if(word_idx >= word_count)
    {
        word_idx = 0;
    }
    word_study_refresh_screen();
}

bool word_study_is_active(void)
{
    return word_active;
}

void word_study_refresh_screen(void)
{
    if(!word_active) return;
    display_clear();
    const WordItem *w = &word_list[word_idx];
    display_draw_string(20, 30, w->eng);
    display_draw_string(20, 70, w->chn);
    char buf[32];
    snprintf(buf, sizeof(buf, "单词 %d/%d", word_idx+1, word_count));
    display_draw_string(20,110,buf);
    display_refresh();
}
