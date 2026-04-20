#ifndef ED_FIRST_H  /* Include guard */
#define ED_FIRST_H
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct Task {
    uint8_t time;
    uint8_t period;
    uint8_t timeLeft;
    bool finished;
} Task;
typedef struct EDF{
    int globaltime;
    uint8_t currentTask;
    int taskLen;
    Task tasks[]; //dynamically allocated tasks. first part of the uint16_t is
    //for the task, while the second part is for the period. range for tasks is 1-256 and same with the period
} EDF;
EDF * edf_init(Task [], int);
uint8_t edf_step(EDF *);  /* An example function declaration */
void edf_display(EDF *, uint8_t);
void edf_display_fancy(EDF * , uint8_t, int);
void buzz(int);
#endif // FOO_H_
