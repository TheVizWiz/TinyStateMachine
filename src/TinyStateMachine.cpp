#include "TinyStateMachine.h"
#include <stdlib.h> // for malloc and free

TinyStateMachine::TinyStateMachine(state_t max_states, transition_t max_transitions) {

    // if max states is too high, set it to the correct largest number.
    if (max_states >= TinyStateMachine::ANY_STATE) max_states = TinyStateMachine::ANY_STATE - 1;

    this->max_transitions = max_transitions;
    this->transition_funcs = (TransitionFunction *) malloc(sizeof(TransitionFunction) * this->max_transitions);
    this->from_states = (state_t *) malloc(sizeof(state_t) * this->max_transitions);
    this->to_states = (state_t *) malloc(sizeof(state_t) * this->max_transitions);

    this->max_states = max_states;
    this->num_states = 0;
    this->enter_funcs = (EnterFunction *) malloc(sizeof(EnterFunction) * this->max_states);
    this->loop_funcs = (LoopFunction *) malloc(sizeof(LoopFunction) * this->max_states);
    this->exit_funcs = (ExitFunction *) malloc(sizeof(ExitFunction) * this->max_states);
}

TinyStateMachine::~TinyStateMachine() {
    // free transition allocations
    free(from_states);
    free(to_states);
    free(transition_funcs);

    // free state allocations
    free(enter_funcs);
    free(loop_funcs);
    free(exit_funcs);
}

bool TinyStateMachine::set_start_state(state_t start_state) {
    if (start_state >= num_states) return false;

    this->current_state = start_state;
    return true;

}

void TinyStateMachine::startup() {
    // run the start func on the first state
    if (every_state_enter_func)
        every_state_enter_func();

    if (enter_funcs[current_state])
        enter_funcs[current_state]();
}

void TinyStateMachine::loop() {
    // run loop on the current state
    if (every_state_loop_func)
        every_state_loop_func();
    if (loop_funcs[current_state])
        loop_funcs[current_state]();

    // check if any transitions need to happen.
    state_t to_state = current_state;
    for (int i = 0; i < num_transitions; i++) {
        // check if from state is the current state OR any state.
        // If it is and the transition func succeeds, we need to transition.
        // transition func will never be null do we don't have to check
        if ((from_states[i] == current_state || from_states[i] == TinyStateMachine::ANY_STATE)
            && transition_funcs[i]()) {
            to_state = to_states[i];
            break;
        }
    }

    if (to_state == current_state) {
        // none of the transition funcs succeeded, can exit loop() gracefully
        return;
    }

    // exit the current state, enter the next state, and set current state to next state
    // need to do null checks for func pointers here.
    if (every_state_exit_func) every_state_exit_func();
    if (exit_funcs[current_state]) exit_funcs[current_state]();
    current_state = to_state;
    if (enter_funcs[current_state]) enter_funcs[current_state]();
}

state_t TinyStateMachine::add_state(EnterFunction enter_func, LoopFunction loop_func, ExitFunction exit_func) {
    if (num_states >= max_states) return TinyStateMachine::NULL_STATE;

    enter_funcs[num_states] = enter_func;
    loop_funcs[num_states] = loop_func;
    exit_funcs[num_states] = exit_func;
    num_states++;
    // since we just incremented number of states, return states - 1 for the added state number.
    return num_states - 1;
}

state_t TinyStateMachine::add_state() {
    return this->add_state(nullptr, nullptr, nullptr);
}

state_t TinyStateMachine::add_state_enter(EnterFunction enter_func) {
    return this->add_state(enter_func, nullptr, nullptr);
}

state_t TinyStateMachine::add_state_loop(LoopFunction loop_func) {
    return this->add_state(nullptr, loop_func, nullptr);
}

state_t TinyStateMachine::add_state_exit(ExitFunction exit_func) {
    return this->add_state(nullptr, nullptr, exit_func);
}

state_t TinyStateMachine::add_state_ee(EnterFunction enter_func, ExitFunction exit_func) {
    return this->add_state(enter_func, nullptr, exit_func);
}

state_t TinyStateMachine::add_state_el(EnterFunction enter_func, LoopFunction loop_func) {
    return this->add_state(enter_func, loop_func, nullptr);
}

state_t TinyStateMachine::add_state_le(LoopFunction loop_func, ExitFunction exit_func) {
    return this->add_state(nullptr, loop_func, exit_func);
}

bool TinyStateMachine::add_every_state_enter(EnterFunction enter_func) {
    this->every_state_enter_func = enter_func;
    return true;
}

bool TinyStateMachine::add_every_state_loop(LoopFunction loop_func) {
    this->every_state_loop_func = loop_func;
    return true;
}

bool TinyStateMachine::add_every_state_exit(ExitFunction exit_func) {
    this->every_state_exit_func = exit_func;
    return true;
}

bool TinyStateMachine::add_transition(state_t from_state, state_t to_state, TransitionFunction transition_func) {
    if (num_transitions >= max_transitions) return false;

    from_states[num_transitions] = from_state;
    to_states[num_transitions] = to_state;
    transition_funcs[num_transitions] = transition_func;
    num_transitions++;
    return true;
}

