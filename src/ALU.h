#ifndef ALU_H
#define ALU_H

#include <systemc>

using namespace sc_core;
using namespace sc_dt;

template<int DATA_WIDTH = 8>
SC_MODULE(ALU) {
    //first operand (from register file or constant value from instruction)
    sc_in<sc_uint<DATA_WIDTH>> a;

    //second operand (always from accumulator)
    sc_in<sc_uint<DATA_WIDTH>> b;

    //part of the instruction code (bits [13:7])
    sc_in<sc_uint<7>> in_instr;

    //binded to output of the flip-flop which stores the carry value
    sc_in<bool> ffc;

    //ALU output (result of an operation)
    sc_out<sc_uint<DATA_WIDTH>> out;

    //carry
    sc_out<bool> c;

    //instruction group code (in_instr[6:5])
    sc_uint<2> icode;

    //operation code (in_instr[4:1])
    sc_uint<4> opcode;

    //bit number (in_instr[2:0])
    sc_uint<3> bn;

    SC_CTOR(ALU) {
        icode = in_instr.read().range(6, 5);
        opcode = in_instr.read().range(4, 1);
        bn = in_instr.read().range(2, 0);

        SC_METHOD(alu_process);
        sensitive << a << b << in_instr << ffc;
    }

    void alu_process();
};

#endif //ALU_H