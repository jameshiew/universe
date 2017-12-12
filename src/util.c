//
// Created by James Hiew on 12/12/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "util.h"

char *load_file(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        fprintf(stderr, "fopen %s failed: %d %s\n", path, errno, strerror(errno));
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    size_t length = (size_t) ftell(file);
    rewind(file);
    char *data = calloc(length + 1, sizeof(char));
    fread(data, 1, length, file);
    fclose(file);
    return data;
}
