#include "ebook_reader.h"
#include "display/display.h"
#include "esp_spiffs.h"
#include <stdio.h>
#include <string.h>

#define EBOOK_LINE_MAX 32
#define EBOOK_PAGE_LINE 12

static bool ebook_active = false;
static int ebook_page = 0;
static FILE *ebook_fp = NULL;

void ebook_reader_init(void)
{
    ebook_active = false;
    ebook_page = 0;
    ebook_fp = NULL;
}

// 打开spiffs内的txt电子书
bool ebook_reader_open(const char *filepath)
{
    ebook_fp = fopen(filepath, "r");
    if(!ebook_fp)
    {
        return false;
    }
    ebook_page = 0;
    ebook_active = true;
    ebook_reader_refresh_screen();
    return true;
}

void ebook_reader_close(void)
{
    if(ebook_fp)
    {
        fclose(ebook_fp);
        ebook_fp = NULL;
    }
    ebook_active = false;
}

void ebook_reader_next_page(void)
{
    if(!ebook_active || !ebook_fp) return;
    ebook_page ++;
    ebook_reader_refresh_screen();
}

void ebook_reader_prev_page(void)
{
    if(!ebook_active || !ebook_fp || ebook_page <= 0) return;
    ebook_page --;
    ebook_reader_refresh_screen();
}

bool ebook_reader_is_active(void)
{
    return ebook_active;
}

void ebook_reader_refresh_screen(void)
{
    if(!ebook_active || !ebook_fp) return;
    rewind(ebook_fp);
    display_clear();
    char line_buf[EBOOK_LINE_MAX];
    int skip_lines = ebook_page * EBOOK_PAGE_LINE;
    int line_cnt = 0;
    int y_pos = 20;

    // 翻到当前页起始行
    for(int i=0; i<skip_lines; i++)
    {
        if(fgets(line_buf, EBOOK_LINE_MAX, ebook_fp) == NULL) break;
    }

    // 读取本页内容
    while(fgets(line_buf, EBOOK_LINE_MAX, ebook_fp) != NULL && line_cnt < EBOOK_PAGE_LINE)
    {
        // 去除换行符
        size_t len = strlen(line_buf);
        if(len>0 && line_buf[len-1] == '\n') line_buf[len-1] = '\0';
        display_draw_string(10, y_pos, line_buf);
        y_pos += 16;
        line_cnt++;
    }
    char page_info[32];
    snprintf(page_info, sizeof(page_info), "页码:%d", ebook_page+1);
    display_draw_string(10, 220, page_info);
    display_refresh();
}
