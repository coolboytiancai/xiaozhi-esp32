#include "ebook_reader.h"
#include "display/display.h"
#include "esp_spiffs.h"
#include <stdio.h>
#include <string.h>

#define EBOOK_LINE_MAX 32
#define EBOOK_PAGE_LINES 12

static bool ebook_active = false;
static FILE *fp = NULL;
static char line_buf[EBOOK_LINE_MAX];
static int current_page = 0;

void ebook_reader_init(void)
{
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = "spiffs",
        .max_files = 5,
        .format_if_mount_failed = true
    };
    esp_spiffs_init(&conf);
}

void ebook_reader_start(void)
{
    fp = fopen("/spiffs/book.txt", "r");
    if (!fp) {
        display_clear();
        display_draw_text(10, 20, "未找到 book.txt");
        display_refresh();
        return;
    }
    ebook_active = true;
    current_page = 0;
    ebook_reader_next_page();
}

void ebook_reader_next_page(void)
{
    if (!ebook_active || !fp) return;
    display_clear();
    int y = 10;
    for(int i=0; i<EBOOK_PAGE_LINES; i++){
        if(fgets(line_buf, EBOOK_LINE_MAX, fp) == NULL) break;
        display_draw_text(8, y, line_buf);
        y += 28;
    }
    display_refresh();
    current_page++;
}

void ebook_reader_prev_page(void)
{
    display_clear();
    display_draw_text(10,20,"简易版暂不支持上一页");
    display_refresh();
}

void ebook_reader_exit(void)
{
    ebook_active = false;
    if(fp) fclose(fp);
    fp = NULL;
}

bool ebook_reader_is_active(void)
{
    return ebook_active;
}
