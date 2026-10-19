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
};
static int word_idx = 0;
static bool word_active = false;

void word_study_init(void)
{
    word_idx = 0;
    word_active = false;
}

void word_study_start(void)
{
    word_idx = 0;
    word_active = true;
    display_clear();
    display_draw_string(20, 80, word_list[word_idx].eng);
    display_draw_string(20, 140, word_list[word_idx].chn);
    display_refresh();
}

void word_study_next(void)
{
    word_idx++;
    if(word_idx >= (sizeof(word_list)/sizeof(WordItem))) {
        word_idx = 0;
    }
    display_clear();
    display_draw_string(20, 80, word_list[word_idx].eng);
    display_draw_string(20, 140, word_list[word_idx].chn);
    display_refresh();
}

void word_study_end(void)
{
    word_active = false;
    display_clear();
    display_refresh();
}

bool word_study_is_active(void)
{
    return word_active;
}
