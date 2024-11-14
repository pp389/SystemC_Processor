#ifndef INSTRUCTIONMEMORY_H
#define INSTRUCTIONMEMORY_H

#include <systemc.h>
#include <fstream>
#include <sstream>
#include <bitset>

template<int ADDR_SIZE = 10, int DEPTH = 1024, int WORD_SIZE = 16>
SC_MODULE(InstructionMemory) {
    sc_in<sc_uint<ADDR_SIZE>> a;
    sc_out<sc_uint<WORD_SIZE>> rd;

    sc_uint<WORD_SIZE> RAM[DEPTH];

    bool traceEnabled = false;

    void read_memory();

    void init_memory(const char* filename);

    void init_memory();

    void dump();

    void trace_operation();

    SC_CTOR(InstructionMemory) {
        init_memory();
        SC_METHOD(read_memory);
        sensitive << a;
    }
};

template<int ADDR_SIZE, int DEPTH, int WORD_SIZE>
void InstructionMemory<ADDR_SIZE, DEPTH, WORD_SIZE>::read_memory() {
    rd.write(RAM[a.read()]);
    trace_operation();
}

template<int ADDR_SIZE, int DEPTH, int WORD_SIZE>
void InstructionMemory<ADDR_SIZE, DEPTH, WORD_SIZE>::init_memory(const char* filename) {
    std::ifstream file(filename);
    std::string line;
    int i = 0;
    while (std::getline(file, line) && i < DEPTH) {
        std::istringstream iss(line);
        sc_uint<WORD_SIZE> value;
        iss >> value;
        RAM[i++] = value;
    }
}

template<int ADDR_SIZE, int DEPTH, int WORD_SIZE>
void InstructionMemory<ADDR_SIZE, DEPTH, WORD_SIZE>::init_memory() {
    std::cout << "init_memory time = " << sc_time_stamp() << std::endl;
    RAM[0] = 0b0011000000000111;
    RAM[1] = 0b0000000010000001;
    RAM[3] = 0b0011000000000101;
    RAM[4] = 0b0000000010000011;
    RAM[6] = 0b0011000100000000;
    RAM[8] = 0b0011001000000111;
    //dump();
}

template<int ADDR_SIZE, int DEPTH, int WORD_SIZE>
void InstructionMemory<ADDR_SIZE, DEPTH, WORD_SIZE>::dump() {
    std::cout << "Instruction memory dump: " << std::endl;
    for (int i = 0; i < DEPTH; i++) {
        std::cout << "Address: [" << std::hex << i << "], value: " << std::bitset<WORD_SIZE>(RAM[i]) << std::endl;
    }
    std::cout << std::endl;
}

template<int ADDR_SIZE, int DEPTH, int WORD_SIZE>
void InstructionMemory<ADDR_SIZE, DEPTH, WORD_SIZE>::trace_operation() {
    if (traceEnabled) {
        std::cout << "time = " << sc_time_stamp() << "[IMEM] Instruction memory read - address: [" << std::hex << a.read() << "], value " <<
            std::bitset<WORD_SIZE>(rd.read()) << std::endl << std::endl;
    }
}

#endif //INSTRUCTIONMEMORY_H
