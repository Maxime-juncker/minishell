#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char cwd[1024];

    // Get current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current Directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return EXIT_FAILURE;
    }

    // Change to parent directory
    if (chdir("..") != 0) {
        perror("chdir() error");
        return EXIT_FAILURE;
    }

    // Get new working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("New Directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}