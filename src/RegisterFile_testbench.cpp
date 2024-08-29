#include <systemc>
#include "RegisterFile.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

SC_MODULE(RegisterFile_testbench) {
    //signals declaration
    sc_signal<bool> clk;
    sc_signal<bool> we;
    sc_signal<sc_uint<7>> a;
    sc_signal<sc_uint<8>> wd;
    sc_signal<sc_uint<8>> rd;

    //register file instance
    RegisterFile<7, 128, 8>* registerFileInstance;

    void generateClockSignal() {
        while (true) {
            clk.write(false);
            wait(5, SC_NS);
            clk.write(true);
            wait(5, SC_NS);
        }
    }

    void test() {
        // Test 1: Write to reg 0x01
        we.write(true);
        a.write(0x01);
        wd.write(0xAA);
        wait(10, SC_NS);
        cout << "Test 1: Write to reg 0x01 | Expected rd=170 | Got rd=" << rd.read()
             << " | " << ((rd.read() == 0xAA) ? "PASSED" : "FAILED") << endl;

        // Test 2: Read from reg 0x01
        we.write(false);
        a.write(0x01);
        wait(10, SC_NS);
        cout << "Test 2: Read from reg 0x01 | Expected rd=170 | Got rd=" << rd.read()
             << " | " << ((rd.read() == 0xAA) ? "PASSED" : "FAILED") << endl;

        // Test 3: Write to reg 0x02
        we.write(true);
        a.write(0x02);
        wd.write(0x55);
        wait(10, SC_NS);
        cout << "Test 3: Write to reg 0x02 | Expected rd=85 | Got rd=" << rd.read()
             << " | " << ((rd.read() == 0x55) ? "PASSED" : "FAILED") << endl;

        // Test 4: Read from reg 0x02
        we.write(false);  // Wyłączenie zapisu
        a.write(0x02);  // Adres rejestru
        wait(10, SC_NS);
        cout << "Test 4: Read from reg 0x02 | Expected rd=85 | Got rd=" << rd.read()
             << " | " << ((rd.read() == 0x55) ? "PASSED" : "FAILED") << endl;

        sc_stop();
    }

    SC_CTOR(RegisterFile_testbench) {
        registerFileInstance = new RegisterFile<7, 128, 8>("registerFileInstance");
        registerFileInstance->clk(clk);
        registerFileInstance->we(we);
        registerFileInstance->a(a);
        registerFileInstance->wd(wd);
        registerFileInstance->rd(rd);

        SC_THREAD(generateClockSignal);  // Generowanie zegara
        SC_THREAD(test);     // Procedura testowa
    }

    ~RegisterFile_testbench() {
        delete registerFileInstance;
    }
};

int sc_main(int argc, char* argv[]) {
    RegisterFile_testbench tb("tb");

    sc_start();

    return 0;
}
