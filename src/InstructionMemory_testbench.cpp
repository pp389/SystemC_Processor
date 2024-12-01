#include <systemc.h>
#include "InstructionMemory.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

SC_MODULE(InstructionMemory_testbench) {
    //signals declaration
    sc_signal<sc_uint<10>> address;
    sc_signal<sc_uint<16>> instruction;

    //instruction memory instance
    InstructionMemory<10, 16>* instructionMemory;

    void test() {
        // Test 1: Read from address 0
        address.write(0);
        wait(5, SC_NS);
        cout << "Test 1: Address 0 | Expected value from file | Got rd=" << instruction.read() << endl;

        // Test 2: Read from address 1
        address.write(1);
        wait(5, SC_NS);
        cout << "Test 2: Address 1 | Expected value from file | Got rd=" << instruction.read() << endl;

        // Test 3: Read from address 10
        address.write(10);
        wait(5, SC_NS);
        cout << "Test 3: Address 10 | Expected value from file | Got rd=" << instruction.read() << endl;

        // Test 4: Read from last address (DEPTH-1)
        address.write(1023);
        wait(5, SC_NS);
        cout << "Test 4: Address 1023 | Expected value from file | Got rd=" << instruction.read() << endl;

        sc_stop();
    }

    SC_CTOR(InstructionMemory_testbench) {
        instructionMemory = new InstructionMemory<10, 16>("instructionMemoryInstance");
        instructionMemory->address(address);
        instructionMemory->instruction(instruction);

        SC_THREAD(test);
    }

    ~InstructionMemory_testbench() {
        delete instructionMemory;
    }
};

int sc_main(int argc, char* argv[]) {
    InstructionMemory_testbench instructionMemoryTestbench("tb");

    sc_start();

    return 0;
}
