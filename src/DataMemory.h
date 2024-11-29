#ifndef DATAMEMORY_H
#define DATAMEMORY_H

#include <systemc.h>
#include <iostream>
#include <bitset>

template<int ADDRESS_SIZE = 8, int WORD_SIZE = 8>
SC_MODULE(DataMemory) {
    sc_in<bool> clock, writeEnabled;
    sc_in<sc_uint<ADDRESS_SIZE>> address;
    sc_in<sc_uint<WORD_SIZE>> writeData;
    sc_out<sc_uint<WORD_SIZE>> readData;

    sc_uint<WORD_SIZE> RAM[1 << ADDRESS_SIZE];

    bool traceEnabled = true;

    void read_memory();
    void write_memory();
    void dump();

    SC_CTOR(DataMemory) {
        SC_METHOD(read_memory);
        sensitive << address;
        SC_METHOD(write_memory);
        sensitive << clock.pos();
    }
};

template<int ADDRESS_SIZE, int WORD_SIZE>
void DataMemory<ADDRESS_SIZE, WORD_SIZE>::read_memory() {
    readData.write(RAM[address.read()]);
    if (traceEnabled) {
        std:cout << "time = " << sc_time_stamp() << ", [DMEM] Data memory read - address [" << address.read() << "], value " <<
            std::bitset<WORD_SIZE>(readData.read()) << std::endl << std::endl;
    }
}

template<int ADDRESS_SIZE, int WORD_SIZE>
void DataMemory<ADDRESS_SIZE, WORD_SIZE>::write_memory() {
    if (writeEnabled.read()) {
        RAM[address.read()] = writeData.read();
        if (traceEnabled) {
        std:cout << "time = " << sc_time_stamp() << ", [DMEM] Data memory write - address [" << address.read() << "], value " <<
            std::bitset<WORD_SIZE>(writeData.read()) << std::endl << std::endl;
        }
    }
}

template<int ADDRESS_SIZE, int WORD_SIZE>
void DataMemory<ADDRESS_SIZE, WORD_SIZE>::dump() {
    std::cout << "Data memory dump: " << std::endl;
    for (int i = 0; i < (1 << ADDRESS_SIZE); i++) {
        std::cout << "Address: [" << std::hex << i << "], value: " << std::dec << RAM[i] << std::endl;
    }
    std::cout << std::endl;
}

#endif //DATAMEMORY_H
