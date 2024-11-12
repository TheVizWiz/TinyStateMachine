#ifndef TINYSTATEMACHINE_TINYSTATEMACHINE_H
#define TINYSTATEMACHINE_TINYSTATEMACHINE_H

typedef unsigned char state_t;
typedef unsigned char transition_t;

typedef bool (*TransitionFunction)();

typedef void (*EnterFunction)();

typedef void (*LoopFunction)();

typedef void (*ExitFunction)();

class TinyStateMachine {

private:
    // state definitions
    EnterFunction *enter_funcs;
    LoopFunction *loop_funcs;
    ExitFunction *exit_funcs;
    state_t current_state = 0;
    state_t num_states = 0;
    state_t max_states = 0;

    // transition definitions
    TransitionFunction *transition_funcs;
    transition_t *from_states;
    transition_t *to_states;
    transition_t num_transitions = 0;
    transition_t max_transitions = 0;

public:
    static const unsigned char ANY_STATE = 0xFF; // largest number of states.



    /**
     * Constructor. Allocates buffers to store all of the information required for the state machine.
     * User must define the maximum size of the state machine in terms of both states and transitions in the graph.
     * NOTE: if max_states must be at most ANY_STATE - 1, or will be set to this number otherwise.
     *
     * @param max_states max states that will be added to the state machine. ANY does not count as a state for the purposes of this number.
     * @param max_transitions max transitions that will be added to the state machine.
     */
    TinyStateMachine(state_t max_states, transition_t max_transitions);

    /**
     * Destructor. Deallocates all memory allocated during the creation of the state machine.
     */
    ~TinyStateMachine();

    /**
     *
     * @param start_state the state to start the state machine with. Should not be called after startup() or loop(), or
     * can lead to undefined behavior.
     * @return true if the start state was set successfully, false otherwise (e.g. out of bounds).
     */
    bool set_start_state (state_t start_state);
    /**
     * Add a state to the state machine. The state is defined using three funcs: start, loop,
     * and stop. Start runs once when the state is entered. Loop runs once per loop of the program.
     * Stop runs once when the state is exited.
     * @param enter_func start func, runs once when the state is entered.
     * @param loop_func loop func, runs once per loop/cycle of the program. NOTE: loop func should be non-blocking if possible.
     * @param exit_func stop func, runs once when the state is exited.
     * @return true if able to add state successfully, false otherwise (e.g. too many states).
     */
    bool add_state(EnterFunction enter_func, LoopFunction loop_func, ExitFunction exit_func);

    /**
     * combinations of add state funcs, each missing one or more of the func pointers.
     */

    /**
     * Add a state by only defining the enter function. The loop and exit functions will be null.
     * @param enter_func start func, runs once when the state is entered.
     * @return true if able to add state successfully, false otherwise (e.g. too many states).
     */
    bool add_state_enter(EnterFunction enter_func);

    /**
     * Add a state by only defining the loop function. The enter and exit functions will be null.
     * @param loop_func loop func, runs once per loop/cycle of the program. NOTE: loop func should be non-blocking if possible.
     * @return true if able to add state successfully, false otherwise (e.g. too many states).
     */
    bool add_state_loop(LoopFunction enter_func);

    /**
     * Add a state by only defining the exit function. The enter and loop functions will be null.
     * @param exit_func stop func, runs once when the state is exited.
     * @return true if able to add state successfully, false otherwise (e.g. too many states).
     */
    bool add_state_exit(ExitFunction enter_func);

    /**
     * Add a state by only defining the enter and loop functions. The exit function will be null.
     * @param enter_func start func, runs once when the state is entered.
     * @param loop_func loop func, runs once per loop/cycle of the program. NOTE: loop func should be non-blocking if possible.
     * @return true if able to add state successfully, false otherwise (e.g. too many states).
     */
    bool add_state_el (EnterFunction enter_func, LoopFunction loop_func);

    /**
     * Add a state by only defining the loop and exit functions. The enter function will be null.
     * @param loop_func loop func, runs once per loop/cycle of the program. NOTE: loop func should be non-blocking if possible.
     * @param exit_func stop func, runs once when the state is exited.
     * @return true if able to add state successfully, false otherwise (e.g. too many states).
     */
    bool add_state_le (LoopFunction loop_func, ExitFunction exit_func);

    /**
     * Add a state by only defining the enter and exit functions. The loop function will be null.
     * @param enter_func start func, runs once when the state is entered.
     * @param exit_func stop func, runs once when the state is exited.
     * @return true if able to add state successfully, false otherwise (e.g. too many states).
     */
    bool add_state_ee (EnterFunction enter_func, ExitFunction exit_func);


    /**
     * Add a transition to the state machine. The transition is defined by the from and to states, as well
     * as a func pointer that should return true if the transition should succeed.
     * @param from_state the state to transition from.
     * @param to_state the state to transition to.
     * @param transition_func the transition func definition. Should return true if the transition should go through, false otherwise.
     * @return true if able to add transition successfully, false otherwise (e.g. too many transitions).
     */
    bool add_transition(state_t from_state, state_t to_state, TransitionFunction transition_func);

    /**
     * Startup func. Should be called once (i.e. in setup()) after all states and transitions are set up.
     */
    void startup();

    /**
     * Loop func. Should be called once per loop (i.e. in loop()). This should be non blocking if state funcs are set up properly.
     */
    void loop();

};


#endif //TINYSTATEMACHINE_TINYSTATEMACHINE_H
