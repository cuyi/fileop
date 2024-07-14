#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "common.h"

int file_r(FILE *f, uint8_t *out, uint32_t out_max, size_t* out_len)
{
    file_dbg_msg("file r begin\r\n");
    size_t ret = fread(out, 1, out_max, f);
    if (ret == out_max) {
        *out_len = ret;
        file_dbg_msg("file r read eq max, len:%u\r\n", *out_len);
        return 0;
    }

    if (ret < out_max && feof(f)) {
        *out_len = ret;
        file_dbg_msg("file r read less than max, len:%u\r\n", *out_len);
        clearerr(f);
        return 0;
    }

    if (ferror(f)) {
        file_dbg_msg("file r read error");
        clearerr(f);
        return -1;
    }

    file_dbg_msg("file r read what???");
    return 0;
}
