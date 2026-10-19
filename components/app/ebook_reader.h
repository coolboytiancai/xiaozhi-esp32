#ifndef EBOOK_READER_H
#define EBOOK_READER_H

#include <stdbool.h>

void ebook_reader_init(void);
bool ebook_reader_open(const char *path);
void ebook_reader_render_page(void);
void ebook_reader_next_page(void);
void ebook_reader_prev_page(void);
void ebook_reader_close(void);
bool ebook_reader_is_active(void);

#endif
