#ifndef FILE_READ_H
#define FILE_READ_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/** 从文件读取内容到out */ 
extern int file_r(FILE *f, uint8_t *out, uint32_t out_max, size_t* out_len);

#endif // FILE_READ_H