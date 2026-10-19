#ifndef LOCAL_MCP_TOOLS_H
#define LOCAL_MCP_TOOLS_H

#include <stdbool.h>

bool mcp_open_ebook(const char *params, char *reply, int reply_len);
bool mcp_ebook_next_page(const char *params, char *reply, int reply_len);
bool mcp_ebook_prev_page(const char *params, char *reply, int reply_len);
bool mcp_close_ebook(const char *params, char *reply, int reply_len);

bool mcp_start_wordstudy(const char *params, char *reply, int reply_len);
bool mcp_next_word(const char *params, char *reply, int reply_len);
bool mcp_stop_wordstudy(const char *params, char *reply, int reply_len);

bool mcp_start_pomodoro(const char *params, char *reply, int reply_len);
bool mcp_stop_pomodoro(const char *params, char *reply, int reply_len);

#endif
