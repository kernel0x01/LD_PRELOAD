#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int open(const char *pathname, int flags, mode_t mode) {
    // Define the real open function.
    int (*real_open)(const char *, int, mode_t) = dlsym(RTLD_NEXT, "open");

    // Call the real open function to open the file.
    int fd = real_open(pathname, flags, mode);

    // Check if the file is "king.txt".
    if (strstr(pathname, "king.txt") != NULL) {
        // If the file is "king.txt", print a message to indicate that it has been opened.
        printf("Opened file %s\n", pathname);
    }

    // Return the file descriptor returned by the real open function.
    return fd;
}

ssize_t write(int fd, const void *buf, size_t count) {
    // Define the real write function.
    ssize_t (*real_write)(int, const void *, size_t) = dlsym(RTLD_NEXT, "write");

    // Check if the file descriptor is for "king.txt".
    if (fd == open("shit.txt", O_RDWR, S_IRUSR | S_IWUSR)) {
        // If the file descriptor is for "king.txt", replace all occurrences of "bhaisd" with "goodboy".
        char *new_buf = strdup(buf);
        char *token = strtok(new_buf, " ");
        while (token != NULL) {
            if (strcmp(token, "badboy") == 0) {
                printf("Replacing %s with goodboy\n", token);
                strncpy(token, "goodboy", strlen("goodboy"));
            }
            token = strtok(NULL, " ");
        }

        // Call the real write function with the modified buffer.
        ssize_t ret = real_write(fd, new_buf, strlen(new_buf));

        // Free the memory allocated for the modified buffer.
        free(new_buf);

        // Return the value returned by the real write function.
        return ret;
    } else {
        // If the file descriptor is not for "king.txt", call the real write function with the original buffer.
        ssize_t ret = real_write(fd, buf, count);
        return ret;
    }
}
