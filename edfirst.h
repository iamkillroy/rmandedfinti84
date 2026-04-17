#ifndef ED_FIRST_H  /* Include guard */
#define ED_FIRST_H
#include <stdlib.h>
#include <stdint.h>

typedef struct EDF{
    int time;
    uint16_t tasks[]; //dynamically allocated tasks. first part of the uint16_t is
    //for the task, while the second part is for the period. range for tasks is 1-256 and same with the period
} EDF;
EDF * edf_init(uint16_t[], int);
int getTaskAtTime(int x);  /* An example function declaration */

#endif // FOO_H_
