#include <systemc.h>
#include "Ffc.h"

SC_MODULE(Ffc_testbench) {
    //Signals declaration
    sc_signal<bool> clk;
    sc_signal<bool> reset;
    sc_signal<bool> d;
    sc_signal<bool> q;

    //Ffc module instance
    Ffc *ffc;

    void generateClockSignal() {
        while (true) {
            clk.write(0);
            wait(5, SC_NS);

            clk.write(1);
            wait(5, SC_NS);
        }
    }

    void test() {
        // Test 1: Asynchronous reset
        reset.write(1); d.write(0);
        wait(10, SC_NS);
        cout << "Test 1: Reset active | d=" << d.read() << " | q=" << q.read() << " | Expected q=0 | " << (q.read() == 0 ? "PASSED" : "FAILED") << endl;

        // Test 2: change d input while reset if off
        d.write(0);
        wait(10, SC_NS);
        cout << "Test 3: d change to 0 | d=" << d.read() << " | q=" << q.read() << " | Expected q=0 | " << (q.read() == 0 ? "PASSED" : "FAILED") << endl;

        // Test 3: reset while clock signal change
        d.write(0); reset.write(1);
        wait(10, SC_NS);
        cout << "Test 5: Reset active again | d=" << d.read() << " | q=" << q.read() << " | Expected q=0 | " << (q.read() == 0 ? "PASSED" : "FAILED") << endl;

        sc_stop();
    }

    SC_CTOR(Ffc_testbench) {
        ffc = new Ffc("ffc");
        ffc->clk(clk);
        ffc->reset(reset);
        ffc->d(d);
        ffc->q(q);

        SC_THREAD(generateClockSignal);
        SC_THREAD(test);
    }

    ~Ffc_testbench() {
        delete ffc;
    }
};

int sc_main(int argc, char* argv[]) {
    Ffc_testbench tb("tb");

    sc_start();

    return 0;
}
