#include <systemc.h>
#include "ALU.h"

template<int DATA_WIDTH = 8>
SC_MODULE(ALU_testbench) {
    //signals declaration
    sc_signal<sc_uint<8>> a, b;              //8-bit ALU inputs
    sc_signal<sc_uint<7>> in_instr;          //7-bit ALU instruction
    sc_signal<sc_uint<8>> out;               //8-bit ALU output
    sc_signal<bool> ffc, carry_out;          //carry flags

    //ALU instance
    ALU<DATA_WIDTH> *aluInstance;

    SC_CTOR(ALU_testbench) {
        aluInstance = new ALU<DATA_WIDTH>("aluInstance");

        aluInstance->a(a);
        aluInstance->b(b);
        aluInstance->in_instr(in_instr);
        aluInstance->output(out);
        aluInstance->ffc(ffc);
        aluInstance->c(carry_out);

        SC_THREAD(test);
    }

    void test() {
        //add two values test
        a.write(10);
        b.write(5);
        in_instr.write(0b01110);
        wait(5, SC_NS);
        cout << "Test 1 - ADD: a = " << a.read() << ", b = " << b.read()
             << ", output = " << out.read() << endl;

        //'and' on two values
        a.write(15);
        b.write(5);
        in_instr.write(0b01010);
        wait(5, SC_NS);
        cout << "Test 2 - AND: a = " << a.read() << ", b = " << b.read()
             << ", output = " << out.read() << endl;

        //'not' operation test
        a.write(0);
        in_instr.write(0b10010);
        wait(5, SC_NS);
        cout << "Test 3 - NOT: a = " << a.read() << ", output = " << out.read() << endl;

        //decrementation test
        a.write(10);
        in_instr.write(0b00110);
        wait(5, SC_NS);
        cout << "Test 4 - DECREMENTATION: a = " << a.read() << ", output = " << out.read() << endl;

        //incrementation test
        a.write(10);
        in_instr.write(0b10100);
        wait(5, SC_NS);
        cout << "Test 5 - INCREMENTATION: a = " << a.read() << ", output = " << out.read() << endl;

        //'or' test
        a.write(3);
        b.write(2);
        in_instr.write(0b01000);
        wait(5, SC_NS);
        cout << "Test 6 - OR: a = " << a.read() << ", b = " << b.read()
             << ", output = " << out.read() << endl;

        //subtraction test
        a.write(7);
        b.write(3);
        in_instr.write(0b00100);
        wait(5, SC_NS);
        cout << "Test 7 - SUBTRACTION: a = " << a.read() << ", b = " << b.read()
             << ", output = " << out.read() << endl;

        //'xor' test
        a.write(10);
        b.write(8);
        in_instr.write(0b01100);
        wait(5, SC_NS);
        cout << "Test 8 - XOR: a = " << a.read() << ", b = " << b.read()
             << ", output = " << out.read() << endl;
    }

    ~ALU_testbench() {
        delete aluInstance;
    }
};

int sc_main(int argc, char* argv[]) {
    ALU_testbench tb("tb");

    sc_start();

    return 0;
}
