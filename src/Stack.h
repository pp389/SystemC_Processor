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

template<int IADDR_WIDTH, int STACK_ADDR_WIDTH, int STACK_DEPTH>
void Stack<IADDR_WIDTH, STACK_ADDR_WIDTH, STACK_DEPTH>::process() {
    if (!reset.read()) {
        sp = STACK_DEPTH;
        full = (sp == 0);
        empty = sp[STACK_ADDR_WIDTH];
        data_out.write(0);
    } else {
        if (wr.read() && !full) {
            sp = sp - 1;
            ram[sp] = data_in.read();
            full = (sp == 0);
            empty = sp[STACK_ADDR_WIDTH];
        } else if (rd.read() && !empty) {
            data_out.write(ram[sp]);
            sp = sp + 1;
            full = (sp == 0);
            empty = sp[STACK_ADDR_WIDTH];
        }

        if ((empty && rd.read()) || (full && wr.read()) || (rd.read() && wr.read()))
            error.write(true);
        else
            error.write(false);
    }
}

#endif //STACK_H
