#ifndef WORD_STUDY_H
#define WORD_STUDY_H
#include <stdbool.h>

void word_study_init(void);
void word_study_start(void);
void word_study_next(void);
void word_study_end(void);
bool word_study_is_active(void);

#endif
