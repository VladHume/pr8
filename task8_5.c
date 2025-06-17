#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("testfile_small.bin", O_RDONLY);
    if (fd == -1) {
        perror("Open failed");
        return 1;
    }

    char buffer[100];
    ssize_t count = read(fd, buffer, sizeof(buffer));

    printf("Requested: %ld bytes, Read: %zd bytes\n", sizeof(buffer), count);

    close(fd);
    return 0;
}
