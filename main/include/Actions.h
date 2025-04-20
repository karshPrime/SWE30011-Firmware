
#pragma once

#include <string>

//- Configs ----------------------------------------------------------------------------------------

using std::string;
typedef unsigned int uint;
typedef enum { STOP, START, UNCHANGED, BEEP, BEEP_FAST, BEEP_SLOW } AStatus;
typedef enum { REGULAR = 3, FAST, SLOW } APace;

typedef struct {
    uint    Pin;
    string  Key;
    AStatus Status;
    bool    State;
} Actuator;

//- Public Methods ---------------------------------------------------------------------------------

void ActionUpdate( string );
void ActionBeep( APace );
