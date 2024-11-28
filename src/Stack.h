#ifndef STACK_H
#define STACK_H

#include <systemc>

using namespace sc_core;
using namespace sc_dt;

template<int INSTRUCTION_ADDR_WIDTH = 10, int STACK_ADDR_WIDTH = 3, int STACK_SIZE = 8>
SC_MODULE(Stack) {
    sc_in<sc_uint<INSTRUCTION_ADDR_WIDTH>> dataInput;
    sc_in<bool> clock, reset, readEnabled, writeEnabled;

    sc_out<sc_uint<INSTRUCTION_ADDR_WIDTH>> dataOutput;
    sc_out<bool> errorFlag;

    sc_uint<STACK_ADDR_WIDTH + 1> stackPointer;
    sc_uint<INSTRUCTION_ADDR_WIDTH> stack[STACK_SIZE];

    bool isEmpty, isFull;

    SC_CTOR(Stack) {
        SC_METHOD(process);
        sensitive << clock.pos() << reset.neg();
    }

    void process();
};

template<int INSTRUCTION_ADDR_WIDTH, int STACK_ADDR_WIDTH, int STACK_SIZE>
void Stack<INSTRUCTION_ADDR_WIDTH, STACK_ADDR_WIDTH, STACK_SIZE>::process() {
    if (!reset.read()) {
        stackPointer = STACK_SIZE;
        isFull = (stackPointer == 0);
        isEmpty = stackPointer[STACK_ADDR_WIDTH];
        dataOutput.write(0);
    } else {
        if (writeEnabled.read() && !isFull) {
            stackPointer--;
            stack[stackPointer] = dataInput.read();
            isFull = (stackPointer == 0);
            isEmpty = stackPointer[STACK_ADDR_WIDTH];
        } 
        else if (readEnabled.read() && !isEmpty) {
            dataOutput.write(stack[stackPointer]);
            stackPointer++;
            isFull = (stackPointer == 0);
            isEmpty = stackPointer[STACK_ADDR_WIDTH];
        }

        if ((isEmpty && readEnabled.read()) || (isFull && writeEnabled.read()) || (readEnabled.read() && writeEnabled.read()))
            errorFlag.write(true);
        else
            errorFlag.write(false);
    }
}

#endif //STACK_H
