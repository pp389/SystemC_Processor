#include "DataMemory.h"

template<int ADDR_SIZE, int WORD_SIZE>
void DataMemory<ADDR_SIZE, WORD_SIZE>::read_memory() {
    rd.write(RAM[a.read()]);
}

template<int ADDR_SIZE, int WORD_SIZE>
void DataMemory<ADDR_SIZE, WORD_SIZE>::write_memory() {
    if (we.read()) {
        RAM[a.read()] = wd.read();
    }
}