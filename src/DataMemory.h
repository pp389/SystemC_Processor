#ifndef DATAMEMORY_H
#define DATAMEMORY_H

#include <systemc.h>

template<int ADDR_SIZE = 8, int WORD_SIZE = 8>
SC_MODULE(DataMemory) {
    sc_in<bool> clk;
    sc_in<bool> we;
    sc_in<sc_uint<ADDR_SIZE>> a;
    sc_in<sc_uint<WORD_SIZE>> wd;
    sc_out<sc_uint<WORD_SIZE>> rd;

    sc_uint<WORD_SIZE> RAM[1 << ADDR_SIZE];

    void read_memory();
    void write_memory();

    SC_CTOR(DataMemory) {
        SC_METHOD(read_memory);
        sensitive << a;
        SC_METHOD(write_memory);
        sensitive << clk.pos();
    }
};


#endif //DATAMEMORY_H
