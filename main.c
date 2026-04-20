#include "edfirst.h"
#include "ratemono.h"
#include <stdint.h>

int main(){
    Task tasks[3] = {{3, 8, 3, false}, {5, 14, 5, false}, {8, 30, 8, false}};
    int taskLen = 3;
    EDF * edf_task = edf_init(tasks, taskLen);
    edf_display_fancy(edf_task, 30, 50);
    return 0;
}
