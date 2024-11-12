#include "gtest/gtest.h"


#ifdef ARDUINO


#else

#include "TinyStateMachine.h"

int main(int num_args, char* args[]) {

    ::testing::InitGoogleTest(&num_args, args);

    RUN_ALL_TESTS();

    return 0;
}

TEST(TinyStateMachine, AddStates) {
    TinyStateMachine tsm = TinyStateMachine(5, 10);

}
#endif

