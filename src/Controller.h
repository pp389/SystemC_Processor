#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <systemc>

using namespace sc_core;
using namespace sc_dt;

SC_MODULE(Controller) {
    sc_in<sc_uint<14>> Instr;
    sc_in<bool> z, pz;
    sc_out<bool> readStack, writeStack, gocall, skip;
    sc_out<bool> d;
    sc_out<bool> ti, lw, wew;
    sc_out<bool> sw;
    sc_out<bool> gotoznz;

    SC_CTOR(Controller) {
        SC_METHOD(process);
        sensitive << Instr << z << pz;
    }
    void process();
};

#endif //CONTROLLER_H
