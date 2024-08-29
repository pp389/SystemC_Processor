#ifndef MUX_H
#define MUX_H

#include <systemc.h>

using namespace sc_core;
using namespace sc_dt;

template<int WIDTH = 8>
SC_MODULE(Mux2_1) {

    //multiplexer inputs
    sc_in<sc_uint<WIDTH>> d0, d1;
    sc_in<bool> s;

    //multiplexer outputs
    sc_out<sc_uint<WIDTH>> y;

    SC_CTOR(Mux2_1) {
        SC_METHOD(process);
        sensitive << d0 << d1 << s;
    }

    void process();
};

template<int WIDTH>
void Mux2_1<WIDTH>::process() {
    y.write(s.read() ? d1.read() : d0.read());
}

#endif //MUX_H
