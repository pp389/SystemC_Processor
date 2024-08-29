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
    sc_out<sc_uint<DATA_WIDTH>> output;

    //carry
    sc_out<bool> c;

    //instruction group code (in_instr[6:5])
    sc_uint<2> instructionGroupCode;

    //operation code (in_instr[4:1])
    sc_uint<4> operationCode;

    //bit number (in_instr[2:0])
    sc_uint<3> bitNumber;

    SC_CTOR(ALU) {
        SC_METHOD(alu_process);
        sensitive << a << b << in_instr << ffc;
    }

    void alu_process();
};

template<int DATA_WIDTH>
void ALU<DATA_WIDTH>::alu_process() {
    instructionGroupCode = in_instr.read().range(6, 5);
    operationCode = in_instr.read().range(4, 1);
    bitNumber = in_instr.read().range(2, 0);

    c = false;
    switch (instructionGroupCode) {
        case 0b00: {
            switch (operationCode) {
                case 0b0111: {
                    sc_uint<DATA_WIDTH + 1> result = a.read() + b.read();
                    c.write(result[DATA_WIDTH]);
                    output.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b0101: {
                    output.write(a.read() & b.read());
                    break;
                }
                case 0b0001: {
                    output.write(0);
                    break;
                }
                case 0b1001: {
                    output.write(~a.read());
                    break;
                }
                case 0b0011:
                case 0b1011: {
                    sc_uint<DATA_WIDTH + 1> result = a.read() - 1;
                    c.write(result[DATA_WIDTH]);
                    output.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b1010:
                case 0b1111: {
                    sc_uint<DATA_WIDTH + 1> result = a.read() + 1;
                    c.write(result[DATA_WIDTH]);
                    output.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b0100: {
                    output.write(a.read() | b.read());
                    break;
                }
                case 0b1000: {
                    output.write(a.read());
                    break;
                }
                case 0b0000: {
                    output.write(b.read());
                    break;
                }
                case 0b1101: { // rlf
                    c.write(a.read()[DATA_WIDTH - 1]);
                    output.write((a.read() << 1) | ffc.read());
                    break;
                }
                case 0b1100: { // rrf
                    c.write(a.read()[0]);
                    output.write((ffc.read() << (DATA_WIDTH - 1)) | (a.read() >> 1));
                    break;
                }
                case 0b0010: {
                    sc_uint<DATA_WIDTH + 1> result = a.read() - b.read();
                    c.write(result[DATA_WIDTH]);
                    output.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b1110: {
                    output.write((a.read().range(3, 0), a.read().range(7, 4)));
                    break;
                }
                case 0b0110: {
                    output.write(a.read() ^ b.read());
                    break;
                }
                default: {
                    output.write(b.read());
                    break;
                }
            }
            break;
        }
        case 0b01: {
            switch (operationCode.range(3, 2)) {
                case 0b00: {
                    output.write(a.read() & (~(1 << bitNumber)));
                    break;
                }
                case 0b01: {
                    output.write(a.read() | (1 << bitNumber));
                    break;
                }
                case 0b10:
                case 0b11: {
                    output.write(a.read() & (1 << bitNumber));
                    break;
                }
            }
            break;
        }
        case 0b11: {
            switch (operationCode) {
                case 0b1111:
                case 0b1110: {
                    sc_uint<DATA_WIDTH + 1> result = a.read() + b.read();
                    c.write(result[DATA_WIDTH]);
                    output.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b1001: {
                    output.write(a.read() & b.read());
                    break;
                }
                case 0b1000: {
                    output.write(a.read() | b.read());
                    break;
                }
                case 0b0000: {
                    output.write(a.read());
                    break;
                }
                case 0b0001:
                case 0b0010: {
                    output.write(b.read());
                    break;
                }
                case 0b1101:
                case 0b1100: {
                    sc_uint<DATA_WIDTH + 1> result = a.read() - b.read();
                    c.write(result[DATA_WIDTH]);
                    output.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b1010: {
                    output.write(a.read() ^ b.read());
                    break;
                }
                case 0b0100: {
                    output.write(a.read());
                    break;
                }
                case 0b0101: {
                    output.write(b.read());
                    break;
                }
                case 0b0110: {
                    output.write(b.read());
                    break;
                }
                default: {
                    output.write(b.read());
                    break;
                }
            }
            break;
          	default:
          		output.write(b.read());
        }
    }
}

#endif //ALU_H