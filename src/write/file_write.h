#ifndef FILE_WRITE_H
#define FILE_WRITE_H

#include <stdint.h>
#include <stdio.h>

/** 将in写入到文件*/ 
extern int file_w(FILE *f, uint8_t *in, uint32_t in_len);

#endif // FILE_WRITE_H