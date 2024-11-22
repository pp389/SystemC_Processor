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
        aluInstance->traceEnabled = true;

        SC_THREAD(test);
    }

    void test_add() {
        std::cout << "----------------ADDITION TEST----------------" << std::endl;
        a.write(10);
        b.write(5);
        in_instr.write(0b0001110);
        wait(5, SC_NS);
        cout << "Test 1 - ADD: a = " << a.read() << ", b = " << b.read()
            << ", output = " << out.read() << ", expected = 15" << endl;
        std::cout << "---------------------------------------------" << std::endl;
    }

    void test_and() {
        std::cout << "----------------'AND' OPERATION TEST----------------" << std::endl;
        a.write(15);
        b.write(5);
        in_instr.write(0b0001010);
        wait(5, SC_NS);
        cout << "Test 2 - AND: a = " << a.read() << ", b = " << b.read()
            << ", output = " << out.read() << ", expected = 5" << endl;
        std::cout << "---------------------------------------------" << std::endl;
    }

    void test_not() {
        std::cout << "----------------'NOT' OPERATION TEST----------------" << std::endl;
        a.write(0);
        in_instr.write(0b0010010);
        wait(5, SC_NS);
        cout << "Test 3 - NOT: a = " << a.read() << ", output = " << out.read() << ", expected = 255" << endl;
        std::cout << "---------------------------------------------" << std::endl;
    }

    void test_decrementation() {
        std::cout << "----------------DECREMENTATION TEST----------------" << std::endl;
        a.write(10);
        in_instr.write(0b0000110);
        wait(5, SC_NS);
        cout << "Test 4 - DECREMENTATION: a = " << a.read() << ", output = " << out.read() << ", expected = 9" << endl;
        std::cout << "---------------------------------------------" << std::endl;
    }

    void test_incrementation() {
        std::cout << "----------------INCREMENTATION TEST----------------" << std::endl;
        a.write(10);
        in_instr.write(0b0010100);
        wait(5, SC_NS);
        cout << "Test 5 - INCREMENTATION: a = " << a.read() << ", output = " << out.read() << ", expected = 11" << endl;
        std::cout << "---------------------------------------------" << std::endl;
    }

    void test_or() {
        std::cout << "----------------'OR' OPERATION TEST----------------" << std::endl;
        a.write(3);
        b.write(2);
        in_instr.write(0b0001000);
        wait(5, SC_NS);
        cout << "Test 6 - OR: a = " << a.read() << ", b = " << b.read()
            << ", output = " << out.read() << ", expected = 3" << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
    }

    void test_subtraction() {
        std::cout << "----------------SUBTRACTION TEST----------------" << std::endl;
        a.write(7);
        b.write(3);
        in_instr.write(0b0000100);
        wait(5, SC_NS);
        cout << "Test 7 - SUBTRACTION: a = " << a.read() << ", b = " << b.read()
            << ", output = " << out.read() << ", expected = 4" << endl;
        std::cout << "---------------------------------------------" << std::endl;
    }

    void test_xor() {
        std::cout << "----------------'XOR' OPERATION TEST----------------" << std::endl;
        a.write(10);
        b.write(8);
        in_instr.write(0b0001100);
        wait(5, SC_NS);
        cout << "Test 8 - XOR: a = " << a.read() << ", b = " << b.read()
            << ", output = " << out.read() << ", expected = 2" << endl;
        std::cout << "---------------------------------------------" << std::endl;
    }

    void test() {
        test_add();
        test_and();
        test_not();
        test_decrementation();
        test_incrementation();
        test_or();
        test_subtraction();
        test_xor();
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
