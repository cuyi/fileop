#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"
#include "read/file_read.h"
#include "write/file_write.h"

int main(int argc, char *args[])
{
    printf("fileop begin\r\n");

    for (int i = 0; i < argc; i++) {
        printf("arg%d:%s\r\n", i, args[i]);
    }

    char src_path[FILE_PATH_MAX_LEN] = {0};
    char dst_path[FILE_PATH_MAX_LEN] = {0};
    strcpy(src_path, args[1]);
    strcpy(dst_path, args[2]);

    FILE *fsrc = file_open_file_read(src_path);
    if (fsrc == NULL) {
        return -1;
    }
    FILE *fdst = file_open_file_write(dst_path);
    if (fdst == NULL) {
        fclose(fsrc);
        return -1;
    }

    long file_len = file_get_file_len(fsrc);
    if (file_len < 0) {
        fclose(fsrc);
        fclose(fdst);
        return -1;
    }
    uint8_t *out = (uint8_t *)malloc(FILE_RD_MAX_LEN_ONCE);
    if (out == NULL) {
        fclose(fsrc);
        fclose(fdst);
        printf("ERR %s:%d\r\n", __FILE__, __LINE__);
        return -1;
    }

    long cur_offset = 0;
    while (cur_offset < file_len) {
        size_t read_len = 0;
        int ret = file_r(fsrc, out, FILE_RD_MAX_LEN_ONCE, &read_len);
        if (ret < 0) {
            printf("ERR %s:%d\r\n", __FILE__, __LINE__);
            free(out);
            fclose(fsrc);
            fclose(fdst);
            return -1;
        }
        cur_offset += read_len;

        ret = file_w(fdst, out, read_len);
        if (ret < 0) {
            printf("ERR %s:%d\r\n", __FILE__, __LINE__);
            free(out);
            fclose(fsrc);
            fclose(fdst);
            return -1;
        }
    }
    
    if (cur_offset != file_len) {
        printf("ERR %s:%d\r\n", __FILE__, __LINE__);
        free(out);
        fclose(fsrc);
        fclose(fdst);
        return -1;
    }
    if (file_get_file_len(fdst) != file_len) {
        printf("ERR %s:%d\r\n", __FILE__, __LINE__);
        free(out);
        fclose(fsrc);
        fclose(fdst);
        return -1;
    }

    free(out);
    fclose(fsrc);
    fclose(fdst);
    printf("fileop end\r\n");
    return 0;
}