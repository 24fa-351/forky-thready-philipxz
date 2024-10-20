#include "patterns.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void pattern1(int processes) {
    fprintf(stderr, "** Pattern 1: creating %d processes **\n", processes);
    for (int ix = 1; ix <= processes; ix++) {
        pid_t child_pid = fork();
        int sleep_time = rand() % 8 + 1;
        if (child_pid == 0) {  // Child Process
            fprintf(stderr, "Process %d (%d) beginning\n", ix, getpid());
            fprintf(stderr, "Process %d (pid %d): sleeping for %d seconds\n",
                    ix, getpid(), sleep_time);
            sleep(sleep_time);
            fprintf(stderr, "Process %d (pid %d): exiting.\n", ix, getpid());
            exit(0);
        } else {  // Parent Process
            fprintf(stderr, "Parent: created child %d (pid %d)\n", ix,
                    child_pid);
        }
    }
    // Wait for all child processes to complete
    while (wait(NULL) > 0);
    fprintf(stderr, "** Pattern 1: All children have exited **\n");
}

void pattern2(int processes) {
    fprintf(stderr, "** Pattern 2: creating %d processes **\n", processes);
    for (int ix = 1; ix <= processes; ix++) {
        pid_t pid = getpid();
        int sleep_time = rand() % 8 + 1;

        if (ix == 0) {
            fprintf(stderr, "Parent: created child %d (pid %d)\n", ix, pid);
        } else {
            fprintf(stderr, "Child %d (pid %d): starting\n", ix, pid);
        }

        // Create next process in this current process
        if (ix < processes) {
            pid_t child_pid = fork();
            if (child_pid == 0) {  // Child Process
                fprintf(stderr,
                        "Child %d (pid %d), sleeping %d seconds after creating "
                        "child %d (pid %d)\n",
                        ix, pid, sleep_time, ix + 1, getpid());
                sleep(sleep_time);
            } else {  // Parent Process
                fprintf(stderr,
                        "Child %d (pid %d), waiting for child %d (pid %d)\n",
                        ix, pid, ix + 1, child_pid);
                wait(NULL);
                fprintf(stderr, "Child %d (pid %d) exiting.\n", ix, pid);
                exit(0);
            }
        } else {  // Special case for the last process since it doesn't fork a
                  // child
            fprintf(
                stderr,
                "Child %d (pid %d) [no children created] sleeping %d seconds\n",
                ix, pid, sleep_time);
            sleep(sleep_time);  // Sleep for a random duration
            fprintf(stderr, "Child %d (pid %d) exiting.\n", ix, pid);
        }
    }
}