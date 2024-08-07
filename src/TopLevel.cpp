#include "TopLevel.h"

template<
    int DATA_WIDTH,
    int DADDR_WIDTH,
    int INSTR_WIDTH,
    int IADDR_WIDTH,
    int STACK_ADDR_WIDTH,
    int REGFILE_ADDR_WIDTH,
    int STACK_DEPTH,
    int REGFILE_DEPTH
>
void TopLevel<DATA_WIDTH,
     DADDR_WIDTH,
     INSTR_WIDTH,
     IADDR_WIDTH,
     STACK_ADDR_WIDTH,
     REGFILE_ADDR_WIDTH,
     STACK_DEPTH,
     REGFILE_DEPTH>::assign_instr()
{
    Instr.write(IRD.read().range(INSTR_WIDTH-1, 0));
}
