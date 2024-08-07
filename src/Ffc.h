#ifndef FFC_H
#define FFC_H

#include <systemc>

using namespace sc_core;
using namespace sc_dt;

SC_MODULE(Ffc) {
    sc_in<bool> clk, reset, d;
    sc_out<bool> q;

    SC_CTOR(Ffc) {
        SC_METHOD(process);
        sensitive << clk.pos() << reset.neg();
    }

    void process();
};

#endif
