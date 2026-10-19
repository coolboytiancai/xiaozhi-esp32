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

// 初始化电子书
void ebook_reader_init(void)
{
    ebook_active = false;
    ebook_page = 0;
    ebook_fp = NULL;
}

// 打开电子书文件
bool ebook_reader_open(const char *path)
{
    ebook_fp = fopen(path, "r");
    if (!ebook_fp)
    {
        return false;
    }
    ebook_page = 0;
    ebook_active = true;
    return true;
}

// 渲染当前页面到墨水屏
void ebook_reader_render_page(void)
{
    if (!ebook_active || !ebook_fp) return;
    display_clear();
    fseek(ebook_fp, ebook_page * EBOOK_LINE_MAX * EBOOK_PAGE_LINE, SEEK_SET);
    char line_buf[EBOOK_LINE_MAX + 1];
    for (int i = 0; i < EBOOK_PAGE_LINE; i++)
    {
        if (fgets(line_buf, EBOOK_LINE_MAX, ebook_fp) == NULL) break;
        display_draw_string(10, i * 32, line_buf);
    }
    display_refresh();
}

// 翻下一页
void ebook_reader_next_page(void)
{
    ebook_page++;
    ebook_reader_render_page();
}

// 翻上一页
void ebook_reader_prev_page(void)
{
    if (ebook_page > 0)
    {
        ebook_page--;
        ebook_reader_render_page();
    }
}

// 关闭电子书
void ebook_reader_close(void)
{
    if (ebook_fp)
    {
        fclose(ebook_fp);
        ebook_fp = NULL;
    }
    ebook_active = false;
    display_clear();
    display_refresh();
}

bool ebook_reader_is_active(void)
{
    return ebook_active;
}
