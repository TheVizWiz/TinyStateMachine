#include "Arduino.h"
#include "TinyStateMachine.h"


int counter = 0;
TinyStateMachine tsm = TinyStateMachine(5, 10);


void setup() {
    tsm.add_state_loop([] {
        Serial.print("counter: ");
        Serial.println(counter);
        counter++;
    });
    tsm.add_state_loop([] {
        Serial.print("counter: ");
        Serial.println(counter);
        counter--;
    });

    tsm.add_transition(0, 1, [] {
        return counter >= 10;
    });

    tsm.add_transition(1, 0, [] {
        return counter <= 0;
    });

    tsm.startup();
}

void loop() {

    tsm.loop();

}