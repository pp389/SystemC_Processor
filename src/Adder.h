#ifndef ADDER_H
#define ADDER_H

#include <systemc>

using namespace sc_core;
using namespace sc_dt;

template<int WIDTH = 8>
SC_MODULE(Adder) {
    //adder inputs (two values to be added)
    sc_in<sc_uint<WIDTH>> a, b;

    //output - addition result
    sc_out<sc_uint<WIDTH>> result;

    //output - carry out
    sc_out<bool> carryOut;

    SC_CTOR(Adder) {
        SC_METHOD(process);
        sensitive << a << b;
    }

    void process();
};

template<int WIDTH>
void Adder<WIDTH>::process() {
    sc_uint<WIDTH + 1> sum = a.read() + b.read();
    carryOut.write(sum[WIDTH]);
    result.write(sum.range(WIDTH-1, 0));
}

#endif //ADDER_H
