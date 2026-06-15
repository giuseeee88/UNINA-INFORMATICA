#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/myfifo"

int main() {
    int fd;
    pid_t pid;
    char message[] = "Hello, child process!";
    char buf[1024];

    // Create the named pipe
    mkfifo(FIFO_NAME, 0666);

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Parent process
        // Open the named pipe for writing
        fd = open(FIFO_NAME, O_WRONLY);
        if (fd == -1) {
            fprintf(stderr, "Failed to open FIFO for writing\n");
            exit(EXIT_FAILURE);
        }

        // Write to the named pipe
        write(fd, message, strlen(message) + 1);
        close(fd);
        printf("Parent sent message to child: %s\n", message);
    } else { // Child process
        // Open the named pipe for reading
        fd = open(FIFO_NAME, O_RDONLY);
        if (fd == -1) {
            fprintf(stderr, "Failed to open FIFO for reading\n");
            exit(EXIT_FAILURE);
        }

        // Read from the named pipe
        read(fd, buf, sizeof(buf));
        printf("Child received message from parent: %s\n", buf);
        close(fd);
    }

    return 0;
}