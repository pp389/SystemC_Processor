#include  "InstructionMemory.h"

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