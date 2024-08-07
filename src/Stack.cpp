#include "Stack.h"

template<int IADDR_WIDTH, int STACK_ADDR_WIDTH, int STACK_DEPTH>
void Stack<IADDR_WIDTH, STACK_ADDR_WIDTH, STACK_DEPTH>::process() {
    if (!reset.read()) {
        sp = STACK_DEPTH;
        full = (sp == 0);
        empty = sp[STACK_ADDR_WIDTH];
        data_out.write(0);
    } else {
        if (wr.read() && !full) {
            sp = sp - 1;
            ram[sp] = data_in.read();
            full = (sp == 0);
            empty = sp[STACK_ADDR_WIDTH];
        } else if (rd.read() && !empty) {
            data_out.write(ram[sp]);
            sp = sp + 1;
            full = (sp == 0);
            empty = sp[STACK_ADDR_WIDTH];
        }

        if ((empty && rd.read()) || (full && wr.read()) || (rd.read() && wr.read()))
            error.write(true);
        else
            error.write(false);
    }
}