#ifndef INSTRUCTIONMEMORY_H
#define INSTRUCTIONMEMORY_H

#include <systemc.h>
#include <fstream>
#include <sstream>
#include <bitset>

template<int ADDRESS_SIZE = 10, int WORD_SIZE = 16>
SC_MODULE(InstructionMemory) {
    sc_in<sc_uint<ADDRESS_SIZE>> address;
    sc_out<sc_uint<WORD_SIZE>> instruction;

    sc_uint<WORD_SIZE> RAM[1 << ADDRESS_SIZE];

    bool traceEnabled = false;

    void read_memory();

    void init_memory(const char* filename);

    void init_memory();

    void dump();

    void trace_operation();

    SC_CTOR(InstructionMemory) {
        init_memory();
        SC_METHOD(read_memory);
        sensitive << address;
    }
};

template<int ADDRESS_SIZE, int WORD_SIZE>
void InstructionMemory<ADDRESS_SIZE, WORD_SIZE>::read_memory() {
    instruction.write(RAM[address.read()]);
    trace_operation();
}

template<int ADDRESS_SIZE, int WORD_SIZE>
void InstructionMemory<ADDRESS_SIZE, WORD_SIZE>::init_memory(const char* filename) {
    std::ifstream file(filename);
    std::string line;
    int i = 0;
    while (std::getline(file, line) && i < (1 << ADDR_SIZE)) {
        std::istringstream iss(line);
        sc_uint<WORD_SIZE> value;
        iss >> value;
        RAM[i++] = value;
    }
}

template<int ADDRESS_SIZE, int WORD_SIZE>
void InstructionMemory<ADDRESS_SIZE, WORD_SIZE>::init_memory() {
    std::cout << "init_memory time = " << sc_time_stamp() << std::endl;
    RAM[0] = 0b0011000000000111; //movlw 7 - 7 to acc
    RAM[1] = 0b0000000010000001; //movwf 1 - acc to reg 1
    RAM[2] = 0b0011000000000011; //movlw 3 - 3 to acc
    RAM[3] = 0b0000000010000011; //movwf 3 - acc to reg 3
    RAM[4] = 0b0011111000001111; //addlw 15 - acc + 15 -> acc = 18
    RAM[5] = 0b0011001000000000; //sw 0 - acc -> dm[0]
    RAM[6] = 0b0000101010001000; //incf 8, 1 - reg 8 should be 1
    RAM[7] = 0b0011000000000001; //movlw 1 - acc should be 1
    RAM[8] = 0b0000001010000001; //subwf 1 - 7 - 1 = 6 in reg 1
    RAM[9] = 0b0011110000011111; //sublw 31 - 1 = 30
    RAM[10] = 0b0000000010001111; //movwf 15 - acc to reg 15
    RAM[11] = 0b0011000100000000; //lw 0 - dm[0] to acc
    //dump();
}

template<int ADDRESS_SIZE, int WORD_SIZE>
void InstructionMemory<ADDRESS_SIZE, WORD_SIZE>::dump() {
    std::cout << "Instruction memory dump: " << std::endl;
    for (int i = 0; i < (1 << ADDRESS_SIZE); i++) {
        std::cout << "Address: [" << std::hex << i << "], value: " << std::bitset<WORD_SIZE>(RAM[i]) << std::endl;
    }
    std::cout << std::endl;
}

template<int ADDRESS_SIZE, int WORD_SIZE>
void InstructionMemory<ADDRESS_SIZE, WORD_SIZE>::trace_operation() {
    if (traceEnabled) {
        std::cout << "time = " << sc_time_stamp() << "[IMEM] Instruction memory read - address: [" << std::hex << address.read() << "], value " <<
            std::bitset<WORD_SIZE>(instruction.read()) << std::endl << std::endl;
    }
}

#endif //INSTRUCTIONMEMORY_H
