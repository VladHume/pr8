#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd[2];
    char buffer[] = "Test write to pipe with limited read side";
    ssize_t nbytes = sizeof(buffer);
    ssize_t count;

    pipe(fd);
    if (fork() == 0) {
        close(fd[1]);
        sleep(2);
        char read_buf[10];
        read(fd[0], read_buf, sizeof(read_buf));
        return 0;
    } else {
        close(fd[0]);
        count = write(fd[1], buffer, nbytes);
        printf("Requested to write %zd bytes, %zd bytes written\n", nbytes, count);
        return 0;
    }
}
