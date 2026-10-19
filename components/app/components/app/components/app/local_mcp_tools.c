#include "local_mcp_tools.h"
#include "ebook_reader.h"
#include "word_study.h"
#include "pomodoro.h"
#include <string.h>
#include <stdio.h>

// MCP工具：打开电子书
bool mcp_open_ebook(const char *params, char *reply, int reply_len)
{
    word_study_end();
    pomodoro_stop();
    ebook_reader_open("/spiffs/book.txt");
    ebook_reader_render_page();
    snprintf(reply, reply_len, "已经打开电子书");
    return true;
}

// MCP工具：电子书下一页
bool mcp_ebook_next_page(const char *params, char *reply, int reply_len)
{
    if(ebook_reader_is_active()){
        ebook_reader_next_page();
        snprintf(reply, reply_len, "");
    }else{
        snprintf(reply, reply_len, "请先打开电子书");
    }
    return true;
}

// MCP工具：电子书上一页
bool mcp_ebook_prev_page(const char *params, char *reply, int reply_len)
{
    if(ebook_reader_is_active()){
        ebook_reader_prev_page();
        snprintf(reply, reply_len, "");
    }else{
        snprintf(reply, reply_len, "请先打开电子书");
    }
    return true;
}

// MCP工具：关闭电子书
bool mcp_close_ebook(const char *params, char *reply, int reply_len)
{
    ebook_reader_close();
    snprintf(reply, reply_len, "电子书已关闭");
    return true;
}

// MCP工具：开始背单词
bool mcp_start_wordstudy(const char *params, char *reply, int reply_len)
{
    ebook_reader_close();
    pomodoro_stop();
    word_study_start();
    snprintf(reply, reply_len, "开始背单词");
    return true;
}

// MCP工具：下一个单词
bool mcp_next_word(const char *params, char *reply, int reply_len)
{
    if(word_study_is_active()){
        word_study_next();
        snprintf(reply, reply_len, "");
    }else{
        snprintf(reply, reply_len, "请先开启背单词模式");
    }
    return true;
}

// MCP工具：结束背单词
bool mcp_stop_wordstudy(const char *params, char *reply, int reply_len)
{
    word_study_end();
    snprintf(reply, reply_len, "背单词结束");
    return true;
}

// MCP工具：启动番茄钟25分钟
bool mcp_start_pomodoro(const char *params, char *reply, int reply_len)
{
    ebook_reader_close();
    word_study_end();
    pomodoro_start(25);
    snprintf(reply, reply_len, "25分钟番茄钟开始");
    return true;
}

// MCP工具：停止番茄钟
bool mcp_stop_pomodoro(const char *params, char *reply, int reply_len)
{
    pomodoro_stop();
    snprintf(reply, reply_len, "番茄钟已停止");
    return true;
}
