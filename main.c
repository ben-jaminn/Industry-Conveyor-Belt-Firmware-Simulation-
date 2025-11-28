#include <stdio.h>
#define MOTOR_ON 1
#define ERROR_OVERHEAT 2
#define EMERGENCY_STOP 4

//Machine state
enum{
    STATE_IDLE,
    STATE_RUNNING,
    STATE_FAULT
};

//The Blueprint
struct Machine {
    int id;
    int motorSpeed; //0 to 100
    unsigned int statusRegister; //holds the flags
    unsigned int lastMaintenanceTime; //to track timing
};

//To change one flag without touching the other
void updateMotor(volatile struct Machine *ptr, int currentState){
    printf("Checking Motor state...\n");
    if(currentState == STATE_RUNNING) {
        ptr->statusRegister |= MOTOR_ON;
        ptr->motorSpeed = 100;
        printf("Motor is on and running at speed %d\n", ptr->motorSpeed);
    }
    
    if(currentState == STATE_FAULT){
        ptr->statusRegister |= EMERGENCY_STOP;
        printf("Error Overheat, emergency stop activated!\n");
    }
};

int currentState = STATE_IDLE; // Global variable

int main(){
    struct Machine state = {1, 100, 0, 0};
    int currentTime = 0;
    int timer = 0;
    char c;
    int loop = 0;
        //Simulating infinite loop
        while(loop < 20) {
        currentTime += 100;

        //Non-Blocking Timer
        if (currentState == STATE_RUNNING && (currentTime - timer >= 2000)) {
            printf("\nConveyor Moving...\n");
            timer = currentTime;
        }

        //Gives System info
        printf("\nSystem State: %d (0=Idle, 1=Run, 2=Fault)\n", currentState);
        //Asks for user input
        printf("Command (S=Start, H=Heat, R=Reset, I=Info): ");
        scanf(" %c", &c); // The space before %c fixes the buffer bug!
        
        //Handles input based on current state
        switch (currentState) {
            
            // --- IDLE STATE ---
            case STATE_IDLE:
                if (c == 'S') {
                    currentState = STATE_RUNNING;
                    printf(">> STARTING MOTOR...\n");
                    updateMotor(&state, currentState);
                }
                break;

            // --- RUNNING STATE ---
            case STATE_RUNNING:
                if (c == 'H') {
                    //Simulate Overheat
                    printf(">> SIMULATING OVERHEAT!\n");
                    state.statusRegister |= ERROR_OVERHEAT; //Set flag
                    currentState = STATE_FAULT;            //Crash system
                    updateMotor(&state, currentState);     //Update hardware
                }
                break;

            // --- FAULT STATE ---
            case STATE_FAULT:
                if (c == 'R') {
                    printf(">> RESETTING SYSTEM...\n");
                    state.statusRegister = 0; //Clear flags
                    state.lastMaintenanceTime = currentTime;
                    printf("Maintenance Logged at: %d\n", state.lastMaintenanceTime);
                    currentState = STATE_IDLE;
                } else {
                    printf("!! CRITICAL ERROR !! Press 'R' to Reset.\n");
                }
                break;
                
        }
        
        loop++;
    }

    return 0;
}
