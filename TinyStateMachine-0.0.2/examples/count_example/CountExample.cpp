#include "Arduino.h"
#include "TinyStateMachine.h"

#define STATE_ASCENDING 0
#define STATE_DESCENDING 1

int counter = 0;
// set up a TSM with a maximum of 5 states and 10 transitions.
TinyStateMachine tsm = TinyStateMachine(5, 10);


void setup() {
    // set up the first state (index 0). By using add_state_loop, only the loop() function of the state is defined.
    tsm.add_state_loop([] {
        Serial.print("counter: ");
        Serial.println(counter);
        counter++;
    });

    // set up the second state (index 1).
    tsm.add_state_loop([] {
        Serial.print("counter: ");
        Serial.println(counter);
        counter--;
    });

    // transition from the first to the second state if the counter is greater than 10.
    tsm.add_transition(STATE_ASCENDING, STATE_DESCENDING, [] {
        return counter >= 10;
    });

    // transition from the second to the first state if the counter is less than 0.
    tsm.add_transition(STATE_DESCENDING, STATE_ASCENDING, [] {
        return counter <= 0;
    });

    tsm.startup();
}

void loop() {

    tsm.loop();

}