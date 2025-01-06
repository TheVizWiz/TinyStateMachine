# TinyStateMachine
A tiny state machine library for state-based architecture on a microcontroller. 
Supports states and transitions in callback-based architecture.

## Usage
- States are defined based on three different callbacks: `enter`, `loop`, and `exit`.
- Each of these callbacks defines what should happen in those states
  - `enter` runs once each time the state is entered
  - `loop` runs once per cycle the state machine is active
  - `exit` runs when the state is exited
- States are transitioned between using a `TransitionFunction`, which checks
if a transition should be successful between the from and to states.

After all the states are set up (usually done in `setup()`), run `state_machine.startup()`.
Then, in `loop()`, call `state_machine.loop()`. If set up properly, `loop` functions can be non-blocking,
allowing for multiple state machines to be created at the same time.

## Example

Here's an example program that creates two states. One counts up to 10, the other counts down to 0. The state machine then cycles between them.

```c++
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
```


