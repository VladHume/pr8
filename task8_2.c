#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("testfile.bin", O_RDONLY);
    if (fd == -1) {
        perror("Open failed");
        return 1;
    }

    unsigned char buffer[4];
    lseek(fd, 3, SEEK_SET);
    read(fd, buffer, 4);

    printf("Buffer: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    close(fd);
    return 0;
}
