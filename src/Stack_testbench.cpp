#include <systemc>
#include "Stack.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

SC_MODULE(StackTB) {
    //signals declaration
    sc_clock clk{"clk", 5, SC_NS};
    sc_signal<bool> reset;
    sc_signal<bool> rd;
    sc_signal<bool> wr;
    sc_signal<sc_uint<10>> data_in;
    sc_signal<sc_uint<10>> data_out;
    sc_signal<bool> error;

    //stack instance
    Stack<10, 3, 8> *stackInstance;

    void test() {
        //Reset stack
        reset.write(false);
        wait(10, SC_NS);
        reset.write(true);
        wait(10, SC_NS);

        // Test 1: Write to empty stack (push)
        wr.write(true);
        rd.write(false);
        data_in.write(0x3FF);  //1023 decimal
        wait(10, SC_NS);
        cout << "Test 1: Push 0x3FF | Expected error=0 | Got error=" << error.read()
             << " | " << ((error.read() == false) ? "PASSED" : "FAILED") << endl;

        // Test 2: Read from stack (pop)
        wr.write(false);
        rd.write(true);
        wait(10, SC_NS);
        cout << "Test 2: Pop | Expected data_out=0x3FF | Got data_out=" << data_out.read()
             << " | " << ((data_out.read() == 0x3FF) ? "PASSED" : "FAILED") << endl;

        // Test 3: Read from empty stack (pop)
        rd.write(true);
        wait(10, SC_NS);
        cout << "Test 3: Pop on empty stack | Expected error=1 | Got error=" << error.read()
             << " | " << ((error.read() == true) ? "PASSED" : "FAILED") << endl;

        // Test 4: Write to full stack (push)
        wr.write(true);
        rd.write(false);
        for (int i = 0; i < 8; i++) {
            data_in.write(i);
            wait(10, SC_NS);
        }
        data_in.write(0xFF);
        wait(10, SC_NS);
        cout << "Test 4: Push on full stack | Expected error=1 | Got error=" << error.read()
             << " | " << ((error.read() == true) ? "PASSED" : "FAILED") << endl;

        sc_stop();
    }

    SC_CTOR(StackTB) {
        stackInstance = new Stack<10, 3, 8>("stackInstance");
        stackInstance->clock(clk);
        stackInstance->reset(reset);
        stackInstance->readEnabled(rd);
        stackInstance->writeEnabled(wr);
        stackInstance->dataInput(data_in);
        stackInstance->dataOutput(data_out);
        stackInstance->errorFlag(error);

        SC_THREAD(test);
    }

    ~StackTB() {
        delete stackInstance;
    }
};

int sc_main(int argc, char* argv[]) {
    StackTB tb("tb");

    sc_start();

    return 0;
}
