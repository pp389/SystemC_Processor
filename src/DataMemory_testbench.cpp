#include <systemc.h>
#include "DataMemory.h"

SC_MODULE(DataMemory_testbench) {
    //signals isntance
    sc_signal<bool> clk;
    sc_signal<bool> we;
    sc_signal<sc_uint<8>> a;    // Address signal (8 bits)
    sc_signal<sc_uint<8>> wd;   // Write data signal (8 bits)
    sc_signal<sc_uint<8>> rd;   // Read data signal (8 bits)

    //data memory instance
    DataMemory<8, 8> *uut;

    void generateClockSignal() {
        while (true) {
            clk.write(false);
            wait(5, SC_NS);

            clk.write(true);
            wait(5, SC_NS);
        }
    }

    // Test sequence
    void test() {
        // Test 1: Write to address 0x01
        a.write(0x01);
        wd.write(0x01);
        we.write(true);
        wait(10, SC_NS);

        // Test 2: Read from address 0x01
        we.write(false);
        wait(100, SC_NS);
        cout << "Test 2: Address 0x01 | Expected: 0x01 | Got: " << rd.read() << endl;

        // Test 3: Write to address 0x02
        a.write(0x02);
        wd.write(0x05);
        we.write(true);
        wait(100, SC_NS);

        // Test 4: Read from address 0x02
        we.write(false);
        wait(10, SC_NS);
        cout << "Test 4: Address 0x02 | Expected: 0x05 | Got: " << rd.read() << endl;

        // Test 5: Check if address 0x01 is still 0x01
        a.write(0x01);
        wait(100, SC_NS);
        cout << "Test 5: Address 0x01 | Expected: 0x01 | Got: " << rd.read() << endl;

        sc_stop();
    }

    SC_CTOR(DataMemory_testbench) {
        uut = new DataMemory<8, 8>("DataMemory");
        uut->clk(clk);
        uut->we(we);
        uut->a(a);
        uut->wd(wd);
        uut->rd(rd);

        // Create processes
        SC_THREAD(generateClockSignal);
        SC_THREAD(test);
    }

    ~DataMemory_testbench() {
        delete uut;
    }
};

int sc_main(int argc, char* argv[]) {
    DataMemory_testbench tb("tb");

    sc_start();

    return 0;
}
