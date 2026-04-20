#include "edfirst.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

EDF*  edf_init(Task tasks[],  int taskLen){
    EDF* edf_instance = malloc(sizeof(EDF) + sizeof(Task)*taskLen);
    edf_instance->globaltime = 0;
    edf_instance->taskLen = taskLen; //get byte size of tasks and dive by byte size of one task to get len per
    memcpy(edf_instance->tasks, tasks, sizeof(Task) * taskLen);

    return edf_instance;
}
uint8_t edf_step(EDF * edf){
    //okay first we need to check every single task
    // and see if it's period is up. if that's the case
    // then we just enable its period to be on
    //first, let's set the current task
    //which is the one with the earliest deadline
    //if it's not finished. so we check the task
    //period and see if it's the least
    uint8_t lastEarliestDeadline = 255;
    uint8_t indexOfTaskWithED = 255;
    for (int i = 0; i<edf->taskLen; i++) {
        if (edf->tasks[i].period < lastEarliestDeadline){
            if (!edf->tasks[i].finished){
                lastEarliestDeadline = edf->tasks[i].period;
                indexOfTaskWithED = i;
            }
        }
    }
    //lastly and most importantly
    edf->globaltime++;//increment time
    edf->tasks[indexOfTaskWithED].timeLeft--;//deincrement time left

    for (int i = 0; i<edf->taskLen; i++){
        if (edf->globaltime != 0 && edf->globaltime % edf->tasks[i].period  == 0) {//aka if period is a multiple of time
            edf->tasks[i].finished = false; //reassigned! this now needs to be done
            edf->tasks[i].timeLeft = edf->tasks[i].time;
        }
        if (edf->tasks[i].timeLeft == 0){//if there's zero time left it's finished
            edf->tasks[i].finished = true;
        }
    }

    return indexOfTaskWithED;

}

void edf_display(EDF * edf, uint8_t runTill){
    int totalTaskUsage[runTill];
    for (int i = 0; i<runTill; i++){
        totalTaskUsage[i] = edf_step(edf);
    }
    for (int i = 0; i<runTill; i++){
        printf("Task %d\n", totalTaskUsage[i]+1);
    }
    return;
}

void buzz(int period) {
    char cmd[64];
    int freq = 17000 / period;
    snprintf(cmd, sizeof(cmd), "./beeper %d 1000 &", freq);
    system(cmd);
}
void edf_display_fancy(EDF * edf, uint8_t runTill, int delayMs) {
    uint8_t totalTaskUsage[runTill];
    for (int i = 0; i < runTill; i++) {
        totalTaskUsage[i] = edf_step(edf);
    }

    // print each task row
    for (int t = 0; t < edf->taskLen; t++) {
        printf("T%d ", t + 1);
        for (int i = 0; i < runTill; i++) {
            if (totalTaskUsage[i] == t) {
                printf("█");
            } else {
                printf(" ");
            }
            fflush(stdout);
            usleep(delayMs * 1000);  // delay between each column

            // beep based on task's period (shorter period = higher frequency)
            if (totalTaskUsage[i] == t) {
                // map period to frequency: shorter period = higher pitch
                int freq = 2000 / edf->tasks[t].period * 100;
                buzz(freq);
            }
        }
        printf("\n");
    }

    // print timeline
    printf("   ");
    for (int i = 0; i < runTill; i++) {
        printf("%d ", i % 10);  // mod 10 to keep single digit
    }
    printf("\n");
}
