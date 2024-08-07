#ifndef STACK_H
#define STACK_H

#include <systemc>

using namespace sc_core;
using namespace sc_dt;

template<int IADDR_WIDTH = 10, int STACK_ADDR_WIDTH = 3, int STACK_DEPTH = 8>
SC_MODULE(Stack) {
    sc_in<sc_uint<IADDR_WIDTH>> data_in;
    sc_in<bool> clk, reset, rd, wr;
    sc_out<sc_uint<IADDR_WIDTH>> data_out;
    sc_out<bool> error;

    sc_uint<IADDR_WIDTH> ram[STACK_DEPTH];
    sc_uint<STACK_ADDR_WIDTH + 1> sp;
    bool empty, full;

    SC_CTOR(Stack) {
        SC_METHOD(process);
        sensitive << clk.pos() << reset.neg();
    }

    void process();
};

#endif //STACK_H
