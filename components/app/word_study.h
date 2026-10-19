#ifndef __WORD_STUDY_H__
#define __WORD_STUDY_H__

#include <stdbool.h>

void word_study_init(void);
void word_study_start(void);
void word_study_stop(void);
void word_study_next(void);
bool word_study_is_active(void);
void word_study_refresh_screen(void);

#endif
