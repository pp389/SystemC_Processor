#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <systemc>

using namespace sc_core;
using namespace sc_dt;

template<int ADDR_SIZE = 7, int DEPTH = 128, int WORD_SIZE = 8>
SC_MODULE(RegisterFile) {
    sc_in<bool> clk, we;
    sc_in<sc_uint<ADDR_SIZE>> a;
    sc_in<sc_uint<WORD_SIZE>> wd;
    sc_out<sc_uint<WORD_SIZE>> rd;

    sc_uint<WORD_SIZE> RF[DEPTH];

    SC_CTOR(RegisterFile) {
        SC_METHOD(process);
        sensitive << clk.pos();
    }

    void process();
};

template<int ADDR_SIZE, int DEPTH, int WORD_SIZE>
void RegisterFile<ADDR_SIZE, DEPTH, WORD_SIZE>::process() {
    if (we.read())
        RF[a.read()] = wd.read();
    rd.write(RF[a.read()]);
}

#endif //REGISTERFILE_H
