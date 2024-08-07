#ifndef ADDER_H
#define ADDER_H

#include <systemc>

using namespace sc_core;
using namespace sc_dt;

template<int WIDTH = 8>
SC_MODULE(Adder) {
    sc_in<sc_uint<WIDTH>> a, b;
    sc_out<sc_uint<WIDTH>> y;
    sc_out<bool> cout;

    SC_CTOR(Adder) {
        SC_METHOD(process);
        sensitive << a << b;
    }

    void process();
};

#endif //ADDER_H
