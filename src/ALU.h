#ifndef ALU_H
#define ALU_H

#include <systemc>
#include <bitset>

using namespace sc_core;
using namespace sc_dt;

template<int DATA_WIDTH = 8>
SC_MODULE(ALU) {
    //first operand (from register file or constant value from instruction)
    sc_in<sc_uint<DATA_WIDTH>> a;

    //second operand (always from accumulator)
    sc_in<sc_uint<DATA_WIDTH>> b;

    //part of the instruction code (bits [13:7])
    sc_in<sc_uint<7>> instruction;

    //binded to output of the flip-flop which stores the carry value
    sc_in<bool> carryFlipFlop;

    //ALU output (result of an operation)
    sc_out<sc_uint<DATA_WIDTH>> output;

    //carry
    sc_out<bool> carryFlag;

    //instruction group code (instruction[6:5])
    sc_uint<2> instructionGroupCode;

    //operation code (instruction[4:1])
    sc_uint<4> operationCode;

    //bit number (instruction[2:0])
    sc_uint<3> bitNumber;

    bool traceEnabled = false;

    SC_CTOR(ALU) {
        SC_METHOD(alu_process);
        sensitive << instruction << a << b << carryFlipFlop;
    }

    void alu_process();

    void trace_operation(std::string icode, std::string opcode, std::string instr);
};

template<int DATA_WIDTH>
void ALU<DATA_WIDTH>::alu_process() {
    instructionGroupCode = instruction.read().range(6, 5);
    operationCode = instruction.read().range(4, 1);
    bitNumber = instruction.read().range(2, 0);

    carryFlag = false;
    switch (instructionGroupCode) {
        case 0b00: {
            switch (operationCode) {
                case 0b0111: {
                    trace_operation("0b00", "0b0111", "addwf");
                    sc_uint<DATA_WIDTH + 1> result = a.read() + b.read();
                    carryFlag.write(result[DATA_WIDTH]);
                    output.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b0101: {
                    trace_operation("0b00", "0b0101", "andwf");
                    output.write(a.read() & b.read());
                    break;
                }
                case 0b0001: {
                    trace_operation("0b00", "0b0001", "clrf, clrw");
                    output.write(0);
                    break;
                }
                case 0b1001: {
                    trace_operation("0b00", "0b1001", "comf");
                    output.write(~a.read());
                    break;
                }
                case 0b0011:
                case 0b1011: {
                    trace_operation("0b00", "0b0011, 0b1011", "decf, decfsz");
                    sc_uint<DATA_WIDTH + 1> result = a.read() - 1;
                    carryFlag.write(result[DATA_WIDTH]);
                    output.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b1010:
                case 0b1111: {
                    trace_operation("0b00", "0b1010, 0b1111", "incf, incfsz");
                    sc_uint<DATA_WIDTH + 1> result = a.read() + 1;
                    carryFlag.write(result[DATA_WIDTH]);
                    output.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b0100: {
                    trace_operation("0b00", "0b0100", "iorwf");
                    output.write(a.read() | b.read());
                    break;
                }
                case 0b1000: {
                    trace_operation("0b00", "0b1000", "movf");
                    output.write(a.read());
                    break;
                }
                case 0b0000: {
                    trace_operation("0b00", "0b0000", "movwf, nop");
                    output.write(b.read());
                    break;
                }
                case 0b1101: {
                    trace_operation("0b00", "0b1101", "rlf");
                    carryFlag.write(a.read()[DATA_WIDTH - 1]);
                    output.write((a.read() << 1) | carryFlipFlop.read());
                    break;
                }
                case 0b1100: {
                    trace_operation("0b00", "0b1100", "rrf");
                    carryFlag.write(a.read()[0]);
                    output.write((carryFlipFlop.read() << (DATA_WIDTH - 1)) | (a.read() >> 1));
                    break;
                }
                case 0b0010: {
                    trace_operation("0b00", "0b0010", "subwf");
                    sc_uint<DATA_WIDTH + 1> result = a.read() - b.read();
                    carryFlag.write(result[DATA_WIDTH]);
                    output.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b1110: {
                    trace_operation("0b00", "0b1110", "swapf");
                    output.write((a.read().range(3, 0), a.read().range(7, 4)));
                    break;
                }
                case 0b0110: {
                    trace_operation("0b00", "0b0110", "xorwf");
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
                    trace_operation("0b01", "0b00", "bcf");
                    output.write(a.read() & (~(1 << bitNumber)));
                    break;
                }
                case 0b01: {
                    trace_operation("0b01", "0b01", "bsf");
                    output.write(a.read() | (1 << bitNumber));
                    break;
                }
                case 0b10:
                case 0b11: {
                    trace_operation("0b01", "0b10, 0b11", "btfsc, btfss");
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
                    trace_operation("0b11", "0b1111, 0b1110", "addlw");
                    sc_uint<DATA_WIDTH + 1> result = a.read() + b.read();
                    carryFlag.write(result[DATA_WIDTH]);
                    output.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b1001: {
                    trace_operation("0b11", "0b1001", "andlw");
                    output.write(a.read() & b.read());
                    break;
                }
                case 0b1000: {
                    trace_operation("0b11", "0b1000", "iorlw");
                    output.write(a.read() | b.read());
                    break;
                }
                case 0b0000: {
                    trace_operation("0b11", "0b0000", "movlw");
                    output.write(a.read());
                    break;
                }
                case 0b0001:
                case 0b0010: {
                    trace_operation("0b11", "0b1001, 0b0010", "lw, sw");
                    output.write(b.read());
                    break;
                }
                case 0b1101:
                case 0b1100: {
                    trace_operation("0b11", "0b1101, 0b1100", "sublw");
                    sc_uint<DATA_WIDTH + 1> result = a.read() - b.read();
                    carryFlag.write(result[DATA_WIDTH]);
                    output.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b1010: {
                    trace_operation("0b11", "0b1010", "xorlw");
                    output.write(a.read() ^ b.read());
                    break;
                }
                case 0b0100: {
                    trace_operation("0b11", "0b0100", "retlw");
                    output.write(a.read());
                    break;
                }
                case 0b0101: {
                    trace_operation("0b11", "0b0101", "gotoz");
                    output.write(b.read());
                    break;
                }
                case 0b0110: {
                    trace_operation("0b11", "0b0110", "gotonz");
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

template<int DATA_WIDTH>
void ALU<DATA_WIDTH>::trace_operation(std::string icode, std::string opcode, std::string instr) {
    if(traceEnabled) 
        std::cout << "time = " << sc_time_stamp() << " [ALU] icode " << icode << ", opcode " << opcode << ": " << instr << std::endl;
}

#endif //ALU_H