#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <systemc>

using namespace sc_core;
using namespace sc_dt;

SC_MODULE(Controller) {
    //14-bit instruction code
    sc_in<sc_uint<14>> instructionCode;

    //z signal indicates a zero value of the operation result, and the pz signal indicates a zero value of the previous operation
    sc_in<bool> z, pz;

    //readStack signal is generated for return and retlw instructions to allow exit from subroutine
    sc_out<bool> readStack;

    //writeStack signal enables writing to the stack and is generated for the 'call' instruction
    sc_out<bool> writeStack;

    //gocall signal  is generated for the 'goto' instruction and the 'call' instruction, as well as after setting the gotoznz signal
    sc_out<bool> goCall;

    //skip signal is generated during the execution of the incfsz, decfsz, btfsc and btfss instructions
    sc_out<bool> skip;

    //registerFileWrite signal enables writing to the register file
    sc_out<bool> registerFileWrite;

    //signal ti used to select the first ALU operand is generated for all c-format instructions
    sc_out<bool> ti;

    sc_out<bool> lw;

    //accumulatorWrite signal enables writing to the accumulator
    sc_out<bool> accumulatorWrite;

    sc_out<bool> sw;

    //The gotoznz signal is generated for the branch instruction gotoz in the case of a zero result of the previous operation
    //and also for the gotonz instruction in the case of a non-zero result of the previous operation
    sc_out<bool> gotoznz;

    bool traceEnabled = false;

    SC_CTOR(Controller) {
        SC_METHOD(process);
        sensitive << instructionCode << z << pz;
    }

    void process();

    void trace_operation();
};

#endif //CONTROLLER_H
