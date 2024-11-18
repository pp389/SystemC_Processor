#ifndef DATAMEMORY_H
#define DATAMEMORY_H

#include <systemc.h>
#include <iostream>
#include <bitset>

template<int ADDR_SIZE = 8, int WORD_SIZE = 8>
SC_MODULE(DataMemory) {
    sc_in<bool> clk;
    sc_in<bool> we;
    sc_in<sc_uint<ADDR_SIZE>> a;
    sc_in<sc_uint<WORD_SIZE>> wd;
    sc_out<sc_uint<WORD_SIZE>> rd;

    sc_uint<WORD_SIZE> RAM[1 << ADDR_SIZE];

    bool traceEnabled = true;

    void read_memory();
    void write_memory();
    void dump();

    SC_CTOR(DataMemory) {
        SC_METHOD(read_memory);
        sensitive << a << we;
        SC_METHOD(write_memory);
        sensitive << clk.pos();
        RAM[0] = 0xA;
    }
};

template<int ADDR_SIZE, int WORD_SIZE>
void DataMemory<ADDR_SIZE, WORD_SIZE>::read_memory() {
    rd.write(RAM[a.read()]);
    if (traceEnabled) {
        std:cout << "time = " << sc_time_stamp() << ", [DMEM] Data memory read - address [" << a.read() << "], value " <<
            std::bitset<WORD_SIZE>(rd.read()) << std::endl << std::endl;
    }
}

template<int ADDR_SIZE, int WORD_SIZE>
void DataMemory<ADDR_SIZE, WORD_SIZE>::write_memory() {
    if (we.read()) {
        RAM[a.read()] = wd.read();
        if (traceEnabled) {
        std:cout << "time = " << sc_time_stamp() << ", [DMEM] Data memory write - address [" << a.read() << "], value " <<
            std::bitset<WORD_SIZE>(wd.read()) << std::endl << std::endl;
        }
    }
}

template<int ADDR_SIZE, int WORD_SIZE>
void DataMemory<ADDR_SIZE, WORD_SIZE>::dump() {
    std::cout << "Data memory dump: " << std::endl;
    for (int i = 0; i < (1 << ADDR_SIZE); i++) {
        std::cout << "Address: [" << std::hex << i << "], value: " << std::bitset<WORD_SIZE>(RAM[i]) << std::endl;
    }
    std::cout << std::endl;
}

#endif //DATAMEMORY_H
