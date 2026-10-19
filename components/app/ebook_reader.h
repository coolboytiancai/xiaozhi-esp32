#ifndef EBOOK_READER_H
#define EBOOK_READER_H

#include <stdbool.h>

void ebook_reader_init(void);
void ebook_reader_start(void);
void ebook_reader_next_page(void);
void ebook_reader_prev_page(void);
void ebook_reader_exit(void);
bool ebook_reader_is_active(void);

#endif
