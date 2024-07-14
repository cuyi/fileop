#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

#define FILE_PATH_MAX_LEN 128
#define FILE_RD_MAX_LEN_ONCE (1 * 1024 * 1024) // 单次最大对区1MB

extern void file_dbg_msg(const char *format, ...);

extern long file_get_file_len(const FILE *stream);
extern FILE* file_open_file_read(const char *path);
extern FILE* file_open_file_write(const char *path);

#endif // COMMON_H