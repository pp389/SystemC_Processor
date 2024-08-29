#include <systemc.h>
#include "InstructionMemory.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

SC_MODULE(InstructionMemory_testbench) {
    //signals declaration
    sc_signal<sc_uint<10>> a;
    sc_signal<sc_uint<16>> rd;

    //instruction memory instance
    InstructionMemory<10, 1024, 16>* instructionMemoryInstance;

    void test() {
        // Test 1: Read from address 0
        a.write(0);
        wait(5, SC_NS);
        cout << "Test 1: Address 0 | Expected value from file | Got rd=" << rd.read() << endl;

        // Test 2: Read from address 1
        a.write(1);
        wait(5, SC_NS);
        cout << "Test 2: Address 1 | Expected value from file | Got rd=" << rd.read() << endl;

        // Test 3: Read from address 10
        a.write(10);
        wait(5, SC_NS);
        cout << "Test 3: Address 10 | Expected value from file | Got rd=" << rd.read() << endl;

        // Test 4: Read from last address (DEPTH-1)
        a.write(1023);
        wait(5, SC_NS);
        cout << "Test 4: Address 1023 | Expected value from file | Got rd=" << rd.read() << endl;

        sc_stop();
    }

    SC_CTOR(InstructionMemory_testbench) {
        instructionMemoryInstance = new InstructionMemory<10, 1024, 16>("instructionMemoryInstance");
        instructionMemoryInstance->a(a);
        instructionMemoryInstance->rd(rd);

        SC_THREAD(test);
    }

    ~InstructionMemory_testbench() {
        delete instructionMemoryInstance;
    }
};

int sc_main(int argc, char* argv[]) {
    InstructionMemory_testbench tb("tb");

    sc_start();

    return 0;
}
