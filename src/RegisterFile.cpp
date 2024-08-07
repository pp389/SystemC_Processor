#include "RegisterFile.h"

template<int ADDR_SIZE, int DEPTH, int WORD_SIZE>
void RegisterFile<ADDR_SIZE, DEPTH, WORD_SIZE>::process() {
    if (we.read())
        RF[a.read()] = wd.read();
    rd.write(RF[a.read()]);
}