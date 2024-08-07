#include "ALU.h"

template<int DATA_WIDTH>
void ALU<DATA_WIDTH>::alu_process() {
    c = false;
    switch (icode) {
        case 0b00: {
            switch (opcode) {
                case 0b0111: {
                    sc_uint<DATA_WIDTH + 1> result = a.read() + b.read();
                    c.write(result[DATA_WIDTH]);
                    out.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b0101: {
                    out.write(a.read() & b.read());
                    break;
                }
                case 0b0001: {
                    out.write(0);
                    break;
                }
                case 0b1001: {
                    out.write(~a.read());
                    break;
                }
                case 0b0011:
                case 0b1011: {
                    sc_uint<DATA_WIDTH + 1> result = a.read() - 1;
                    c.write(result[DATA_WIDTH]);
                    out.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b1010:
                case 0b1111: {
                    sc_uint<DATA_WIDTH + 1> result = a.read() + 1;
                    c.write(result[DATA_WIDTH]);
                    out.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b0100: {
                    out.write(a.read() | b.read());
                    break;
                }
                case 0b1000: {
                    out.write(a.read());
                    break;
                }
                case 0b0000: {
                    out.write(b.read());
                    break;
                }
                case 0b1101: { // rlf
                    c.write(a.read()[DATA_WIDTH - 1]);
                    out.write((a.read() << 1) | ffc.read());
                    break;
                }
                case 0b1100: { // rrf
                    c.write(a.read()[0]);
                    out.write((ffc.read() << (DATA_WIDTH - 1)) | (a.read() >> 1));
                    break;
                }
                case 0b0010: {
                    sc_uint<DATA_WIDTH + 1> result = a.read() - b.read();
                    c.write(result[DATA_WIDTH]);
                    out.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b1110: {
                    out.write((a.read().range(3, 0), a.read().range(7, 4)));
                    break;
                }
                case 0b0110: {
                    out.write(a.read() ^ b.read());
                    break;
                }
                default: {
                    out.write(b.read());
                    break;
                }
            }
            break;
        }
        case 0b01: {
            switch (opcode.range(3, 2)) {
                case 0b00: {
                    out.write(a.read() & (~(1 << bn)));
                    break;
                }
                case 0b01: {
                    out.write(a.read() | (1 << bn));
                    break;
                }
                case 0b10:
                case 0b11: {
                    out.write(a.read() & (1 << bn));
                    break;
                }
            }
            break;
        }
        case 0b11: {
            switch (opcode) {
                case 0b1111:
                case 0b1110: {
                    sc_uint<DATA_WIDTH + 1> result = a.read() + b.read();
                    c.write(result[DATA_WIDTH]);
                    out.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b1001: {
                    out.write(a.read() & b.read());
                    break;
                }
                case 0b1000: {
                    out.write(a.read() | b.read());
                    break;
                }
                case 0b0000: {
                    out.write(a.read());
                    break;
                }
                case 0b0001:
                case 0b0010: {
                    out.write(b.read());
                    break;
                }
                case 0b1101:
                case 0b1100: {
                    sc_uint<DATA_WIDTH + 1> result = a.read() - b.read();
                    c.write(result[DATA_WIDTH]);
                    out.write(result.range(DATA_WIDTH - 1, 0));
                    break;
                }
                case 0b1010: {
                    out.write(a.read() ^ b.read());
                    break;
                }
                case 0b0100: {
                    out.write(a.read());
                    break;
                }
                case 0b0101: {
                    out.write(b.read());
                    break;
                }
                case 0b0110: {
                    out.write(b.read());
                    break;
                }
                default: {
                    out.write(b.read());
                    break;
                }
            }
            break;
          	default:
          		out.write(b.read());
        }
    }
}
