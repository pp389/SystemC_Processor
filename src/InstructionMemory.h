#ifndef INSTRUCTIONMEMORY_H
#define INSTRUCTIONMEMORY_H

#include <systemc.h>
#include <fstream>
#include <sstream>

template<int ADDR_SIZE = 10, int DEPTH = 1024, int WORD_SIZE = 16>
SC_MODULE(InstructionMemory) {
    sc_in<sc_uint<ADDR_SIZE>> a;
    sc_out<sc_uint<WORD_SIZE>> rd;

    sc_uint<WORD_SIZE> RAM[DEPTH];

    void read_memory();

    void init_memory(const char* filename);

    SC_CTOR(InstructionMemory) {
        SC_METHOD(read_memory);
        sensitive << a;
        init_memory("instructions.txt");
    }
};

template<int ADDR_SIZE, int DEPTH, int WORD_SIZE>
void InstructionMemory<ADDR_SIZE, DEPTH, WORD_SIZE>::read_memory() {
    rd.write(RAM[a.read()]);
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


#endif //INSTRUCTIONMEMORY_H
