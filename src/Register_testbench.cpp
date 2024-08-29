#include <systemc.h>
#include "Register.h"

SC_MODULE(Register_testbench) {
    //signals declaratiuuton
    sc_signal<bool> clk;
    sc_signal<bool> reset;
    sc_signal<sc_uint<8>> d;
    sc_signal<sc_uint<8>> q;

    //register instance
    Register<8> *registerInstance;

    void generateClockSignal() {
        while (true) {
            clk.write(false);
            wait(5, SC_NS);

            clk.write(true);
            wait(5, SC_NS);
        }
    }

    void test() {
        // Test 1: Reset activation
        reset.write(false);
        d.write(0xAA);
        wait(10, SC_NS);
        cout << "Test 1: Reset active | d=" << d.read() << " | q=" << q.read()
             << " | Expected q=0 | " << ((q.read() == 0) ? "PASSED" : "FAILED") << endl;

        // Test 2: Reset deactivation and setting d
        reset.write(true);
        wait(10, SC_NS);
        cout << "Test 2: Reset inactive | d=" << d.read() << " | q=" << q.read()
             << " | Expected q=170 | " << ((q.read() == 0xAA) ? "PASSED" : "FAILED") << endl;

        // Test 3: d value change
        d.write(0x55);
        wait(10, SC_NS);
        cout << "Test 3: d change to 55 | d=" << d.read() << " | q=" << q.read()
             << " | Expected q=85 | " << ((q.read() == 0x55) ? "PASSED" : "FAILED") << endl;

        // Test 4: Reset activation
        reset.write(false);
        d.write(0xFF);
        wait(10, SC_NS);
        cout << "Test 4: Reset active again | d=" << d.read() << " | q=" << q.read()
             << " | Expected q=0 | " << ((q.read() == 0) ? "PASSED" : "FAILED") << endl;

        sc_stop();
    }

    SC_CTOR(Register_testbench) {
        registerInstance = new Register<8>("registerInstance");
        registerInstance->clk(clk);
        registerInstance->reset(reset);
        registerInstance->d(d);
        registerInstance->q(q);

        SC_THREAD(generateClockSignal);
        SC_THREAD(test);
    }

    ~Register_testbench() {
        delete registerInstance;
    }
};

int sc_main(int argc, char* argv[]) {
    Register_testbench tb("tb");

    sc_start();

    return 0;
}
