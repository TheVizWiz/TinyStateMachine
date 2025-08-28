#include "TinyStateMachine.h"
//#include "iostream"
//#include "stdlib.h"

int counter = 0;

int main(int numArgs, char *args[]) {

    TinyStateMachine tsm = TinyStateMachine();

//    tsm.add_state_el([] {
//        std::cout << "STARTING STATE 1" << std::endl;
//    }, [] {
//        std::cout << "counter: " << counter << std::endl;
//        counter++;
//    });
//    tsm.add_state_loop([] {
//        std::cout << "counter: " << counter << std::endl;
//        counter--;
//    });
//
//    tsm.add_transition(0, 1, [] {
//        return counter >= 10;
//    });
//
//    tsm.add_transition(1, 0, [] {
//        return counter <= 0;
//    });
//
//    while (true)
//        tsm.loop();

}