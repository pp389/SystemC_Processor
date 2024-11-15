#ifndef REGISTER_H
#define REGISTER_H

#include <systemc>

using namespace sc_core;
using namespace sc_dt;

template<int WIDTH = 8>
SC_MODULE(Register) {
    sc_in<bool> clk, reset;
    sc_in<sc_uint<WIDTH>> d;
    sc_out<sc_uint<WIDTH>> q;

    SC_CTOR(Register) {
        SC_METHOD(process);
        sensitive << clk.pos() << reset.neg();
    }

    void process();
};

template<int WIDTH>
void Register<WIDTH>::process() {
    if (!reset.read())
        q.write(0);
    else if (clk.posedge())
        q.write(d.read());
}


template<int WIDTH = 8>
SC_MODULE(Register_we) {
    sc_in<bool> clk, reset, we;
    sc_in<sc_uint<WIDTH>> d;
    sc_out<sc_uint<WIDTH>> q;

    bool traceEnabled = true;

    SC_CTOR(Register_we) {
        SC_METHOD(process);
        sensitive << clk.pos() << reset.neg();
    }

    void process();

    void trace_operation();
};

template<int WIDTH>
void Register_we<WIDTH>::process() {
    if (!reset.read())
        q.write(0);
    else if (clk.posedge()) {
        if (we.read()) {
            q.write(d.read());
            trace_operation();
        }
        else
            q.write(q.read());
    }
}

template<int WIDTH>
void Register_we<WIDTH>::trace_operation() {
    if (traceEnabled) {
        std::cout << "time = " << sc_time_stamp() << ", [ACCUMULATOR] Write to accumulator, value = " << d.read() << std::endl;
    }
}

#endif //REGISTER_H
