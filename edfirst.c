#include "edfirst.h"
#include <stdint.h>
#include <string.h>

EDF*  edf_init(uint16_t tasks[], int taskLen){
    EDF* edf_instance = malloc(sizeof(EDF) + sizeof(uint16_t)*taskLen);
    edf_instance->time = 0;
    memcpy(edf_instance->tasks, tasks, sizeof(uint16_t) * taskLen);

    return edf_instance;
}
uint8_t edf_step(EDF * edf){
    
}
