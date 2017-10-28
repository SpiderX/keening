#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdbool.h>
#include "config.h"

const char* name;

void err(char* msg, int e);
char* cat(const char* a, const char* b);

int main(int argc, char* argv[]) {
    name = argv[0] == NULL ? "" : argv[0];
    char* dest = argv[1] != NULL ? argv[1] : getenv("SSH_ORIGINAL_COMMAND");
    bool is_tmp = dest == NULL ? 1 : 0;

    char* file = NULL;
    const char* prefix = NULL;

    char buf[BUFSIZ];

    int fd = -1;

    if (is_tmp) {
        if((fd = mkstemp(PATH_TMP)) == -1 ) {
            err("mkstemp", errno);
            return 1;
        }

        if (chmod(PATH_TMP, 0644) == -1)
            err("Could not set mode 0644 for temporary file", errno);

        file = PATH_TMP;
        prefix = URL_TMP;

    } else {
        char* fdest = cat(PATH_PRS, dest);

        if ((fd = open(fdest, O_CREAT|O_WRONLY|O_TRUNC, 0644)) == -1) {
            err("Could not open target file", errno);
            return 1;
        }

        file = dest;
        prefix = URL_PRS;

        free(fdest);
    }
        
    ssize_t b;
    int ret = 0;

    /* read from stdin, write to destination */
    while ((b = read(0, buf, BUFSIZ)) > 0) {
        if(write(fd, buf, b) == -1) {
            err("write", errno);
            ret = 1;
            break;
        }
    }

    if (b == -1) {
        err("read", errno);
        ret = 1;
    }

    if (ret && is_tmp && unlink(PATH_TMP) == -1) {
            err("Could not delete target file", errno);
    } else {
        char* url = cat(prefix, basename(file));
        printf("%s\n", url);
        free(url);
    }

    close(fd);
    return ret;
}

void err(char* msg, int e) {
    fprintf(stderr, "%s: %s: %s\n", name, msg, strerror(e));
}

char* cat(const char* a, const char* b) {
    char* c = malloc(strlen(a) + strlen(b) + 2);
    *c = '\0';

    strcat(c, a);
    strcat(c, b);

    return c;
}
