#include "forky.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void pattern1(int processes) {
    for (int ix = 1; ix <= processes; ix++) {
        pid_t child_pid = fork();
        if (child_pid == 0) {  // Child Process
            printf("Process %d (%d) beginning\n", ix, getpid());
            int sleep_time = rand() % 8 + 1;
            sleep(sleep_time);
            printf("Process %d (%d) exiting\n", ix, getpid());
            exit(0);
        }
    }

    // Wait for all child processes to complete
    while (wait(NULL) > 0);
}

void pattern2(int total_processes) {
    for (int ix = 1; ix <= total_processes; ix++) {
        pid_t pid = getpid();
        printf("Process %d (%d) beginning\n", ix, pid);

        int sleep_time = rand() % 8 + 1;
        sleep(sleep_time);

        // Create next process in this current process
        if (ix < total_processes) {
            pid_t child_pid = fork();
            if (child_pid == 0) {  // Child Process
                printf("Process %d (%d) creating Process %d\n", ix, pid,
                       ix + 1);
            } else {  // Parent Process
                wait(NULL);
                printf("Process %d (%d) exiting\n", ix, pid);
                exit(0);
            }
        } else {  // Special case for the last process since it doesn't fork a child
            printf("Process %d (%d) exiting\n", ix, pid);  
            exit(0); 
        }
    }
}