#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <string.h>
#include <cmath>

#include "util.hpp"

char *load_file(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        fprintf(stderr, "fopen %s failed: %d %s\n", path, errno, strerror(errno));
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    size_t length = (size_t) ftell(file);
    rewind(file);
    char *data = (char *) calloc(length + 1, sizeof(char));
    fread(data, 1, length, file);
    fclose(file);
    return data;
}
