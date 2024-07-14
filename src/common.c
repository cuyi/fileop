#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>

bool g_dbg = true;

void file_dbg_msg(const char *format, ...)
{
    if (!g_dbg) {
        return;
    }

    va_list args;
    va_start(args, format);
 
    // 获取当前日志的大小
    size_t size = 1024; // 假设初始大小为1024字节
    char *log_entry = (char *)malloc(size * sizeof(char));
    if (log_entry == NULL) {
        printf("ERR %s:%d\r\n", __FILE__, __LINE__);
        return;
    }
 
    // 使用可变参数列表进行格式化字符串
    int n = vsnprintf(log_entry, size, format, args);
    if (n > -1 && n < (int)size) { // 成功
        // 输出日志内容
        printf("DBG: %s", log_entry);
    } else {
        // 处理字符串超出预分配大小的情况
        size *= 2; // 增加两倍大小
        char *tmp = (char *)realloc(log_entry, size * sizeof(char));
        if (tmp != NULL) {
            log_entry = tmp;
            n = vsnprintf(log_entry, size, format, args);
            // 输出日志内容
            printf("DBG: %s", log_entry);
        } else {
            // 内存再次分配失败的处理逻辑
        }
    }
 
    // 释放内存
    free(log_entry);
    va_end(args);
}

long file_get_file_len(FILE *stream)
{
    /* 保存原始偏移 */
    long cur_saved = ftell(stream);
    if (cur_saved < 0) {
        printf("ERR %s:%d\r\n", __FILE__, __LINE__);
        return -1;
    }

    /* 获取长度 */
    if (fseek(stream, 0, SEEK_END) < 0) {
        printf("ERR %s:%d\r\n", __FILE__, __LINE__);
        return -1;
    }
    long len = ftell(stream);
    if (len < 0) {
        printf("ERR %s:%d\r\n", __FILE__, __LINE__);
        return -1;
    }

    /* 恢复原始偏移 */
    if (fseek(stream, cur_saved, SEEK_SET) < 0) {
        printf("ERR %s:%d cur_saved:%ld\r\n", __FILE__, __LINE__, cur_saved);
        return -1;
    }
    return len;
}

FILE* file_open_file_read(const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        printf("ERR %s:%d\r\n", __FILE__, __LINE__);
        return NULL;
    }
    return f;
}

FILE* file_open_file_write(const char *path)
{
    FILE *f = fopen(path, "w");
    if (f == NULL) {
        printf("ERR %s:%d\r\n", __FILE__, __LINE__);
        return NULL;
    }
    return f;
}