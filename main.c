#include "edfirst.h"
#include "ratemono.h"

int main(){
    uint16_t tasks[3] = {0x0305, 0x0508, 0x0A0A};
    EDF * edf_task = edf_init(tasks, 3);
    return 0;
}
