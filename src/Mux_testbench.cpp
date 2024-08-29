#include <systemc.h>
#include "Mux.h"

template<int DATA_WIDTH = 8>
SC_MODULE(Mux2_1_testbench) {
    //signals declaration
    sc_signal<sc_uint<8>> d0, d1;
    sc_signal<bool> s;
    sc_signal<sc_uint<8>> y;

    //mux instance
    Mux2_1<DATA_WIDTH> *mux;

    SC_CTOR(Mux2_1_testbench) {
        mux = new Mux2_1<8>("mux");
        mux->d0(d0);
        mux->d1(d1);
        mux->s(s);
        mux->y(y);

        // Proces testowy
        SC_THREAD(test);
    }


    void test() {
        // Test 1: s = 0, selects d0
        d0.write(10);
        d1.write(20);
        s.write(0);
        wait(10, SC_NS);
        assert(y.read() == d0.read());
        cout << "Test 1 -- s=0 | d0=" << d0.read() << " | d1=" << d1.read() << " | y=" << y.read() << " | " << (y.read() == d0.read() ? "PASS" : "FAIL") << endl;

        // Test 2: s = 1, selects d1
        s.write(1);
        wait(10, SC_NS);
        assert(y.read() == d1.read());
        cout << "Test 2 -- s=1 | d0=" << d0.read() << " | d1=" << d1.read() << " | y=" << y.read() << " | " << (y.read() == d1.read() ? "PASSED" : "FAILED") << endl;

        // Test 3: Input values changed, s=0
        d0.write(42);
        d1.write(84);
        s.write(0);
        wait(10, SC_NS);
        assert(y.read() == d0.read());
        cout << "Test 3: s=0 | d0=" << d0.read() << " | d1=" << d1.read() << " | y=" << y.read() << " | " << (y.read() == d0.read() ? "PASSED" : "FAILED") << endl;

        // Test 4: s=1, values same as in test3
        s.write(1);
        wait(10, SC_NS);
        assert(y.read() == d1.read());
        cout << "Test 4: s=1 | d0=" << d0.read() << " | d1=" << d1.read() << " | y=" << y.read() << " | " << (y.read() == d1.read() ? "PASSED" : "FAILED") << endl;
    }

    ~Mux2_1_testbench() {
        delete mux;
    }
};

int sc_main(int argc, char* argv[]) {
    Mux2_1_testbench tb("tb");

    sc_start();

    return 0;
}
