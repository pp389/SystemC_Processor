#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <systemc>

using namespace sc_core;
using namespace sc_dt;

template<int ADDRESS_SIZE = 7, int REGISTERS_COUNT = 128, int WORD_SIZE = 8>
SC_MODULE(RegisterFile) {
    sc_in<bool> clock, writeEnabled;
    sc_in<sc_uint<ADDRESS_SIZE>> regNumber; //used to specify on which register we want to perform operation
    sc_in<sc_uint<WORD_SIZE>> writeData; //used for writing data to register
    sc_out<sc_uint<WORD_SIZE>> readData; //used for reading data from register

    sc_uint<WORD_SIZE> registers[REGISTERS_COUNT];

    bool traceEnabled = false;

    SC_CTOR(RegisterFile) {
        SC_METHOD(process);
        sensitive << clock.pos();
    }

    void process();

    void trace_operation();

    void dump();
};

template<int ADDRESS_SIZE, int REGISTERS_COUNT, int WORD_SIZE>
void RegisterFile<ADDRESS_SIZE, REGISTERS_COUNT, WORD_SIZE>::process() {
    if (writeEnabled.read()) {
        registers[regNumber.read()] = writeData.read();
    }
    readData.write(registers[regNumber.read()]);
}

template<int ADDRESS_SIZE, int REGISTERS_COUNT, int WORD_SIZE>
void RegisterFile<ADDRESS_SIZE, REGISTERS_COUNT, WORD_SIZE>::trace_operation() {
    if (traceEnabled) {
        std::cout << "time = " << sc_time_stamp() << "[REGFILE] Write to register number " << a.read() << ", data = " << registers[a.read()] << std::endl;
    }
}

template<int ADDRESS_SIZE, int REGISTERS_COUNT, int WORD_SIZE>
void RegisterFile<ADDRESS_SIZE, REGISTERS_COUNT, WORD_SIZE>::dump() {
    std::cout << std::endl << "[REGFILE] Register file dump" << std::endl;
    for (int i = 0; i < DEPTH; i++) {
        std::cout << "Register number: " << i << ", value: " << registers[i] << std::endl;
    }
}

#endif //REGISTERFILE_H
