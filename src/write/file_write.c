#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "common.h"

int file_w(FILE *f, uint8_t *in, uint32_t in_len)
{
    file_dbg_msg("file w begin\r\n");
    size_t ret = fwrite(in, 1, in_len, f);
    if (ret == in_len) {
        file_dbg_msg("file w write eq in_len, len:%u\r\n", in_len);
        return 0;
    }

    if (feof(f)) {
        file_dbg_msg("file w eof\r\n");
        return -1;
    }

    if (ferror(f)) {
        file_dbg_msg("file w error\r\n");
        return -1;
    }

    file_dbg_msg("file w what???\r\n");
    return -1;
}
