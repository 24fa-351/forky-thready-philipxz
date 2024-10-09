#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "patterns.h"

int main(int argc, char *argv[]) {
    int total_processes = atoi(argv[1]);
    int pattern_number = atoi(argv[2]);

    if (total_processes < 1 || total_processes > 256 ||
        (pattern_number < 1 || pattern_number > 3)) {
        fprintf(stderr,
                "Invalid arguments. Number of processes must be between 1 and "
                "256, and pattern number must be 1, 2, or 3.\n");
        return 1;
    }

    srand(time(NULL));

    switch (pattern_number) {
        case 1:
            pattern1(total_processes);
            break;
        case 2:
            pattern2(total_processes);
            break;
    }

    return 0;
}