#include <systemc.h>
#include "DataMemory.h"

SC_MODULE(DataMemory_testbench) {
    sc_clock clk{ "clk", 5, SC_NS };
    sc_signal<bool> writeEnabled;
    sc_signal<sc_uint<8>> address;
    sc_signal<sc_uint<8>> writeData;  
    sc_signal<sc_uint<8>> readData;  

    DataMemory<8, 8>* dataMemory;

    void test() {
        // Test 1: Write to address 0x01
        address.write(0x01);
        writeData.write(0x01);
        writeEnabled.write(true);
        wait(5, SC_NS);

        // Test 2: Read from address 0x01
        writeEnabled.write(false);
        address.write(0x01);
        wait(5, SC_NS);
        cout << "Test 2: Address 0x01 | Expected: 0x01 | Got: " << readData.read() << endl;

        // Test 3: Write to address 0x02
        address.write(0x02);
        writeData.write(0x05);
        writeEnabled.write(true);
        wait(5, SC_NS);

        // Test 4: Read from address 0x02
        writeEnabled.write(false);
        address.write(0x02);
        wait(5, SC_NS);
        cout << "Test 4: Address 0x02 | Expected: 0x05 | Got: " << readData.read() << endl;

        // Test 5: Check if address 0x01 is still 0x01
        address.write(0x01);
        wait(5, SC_NS);
        cout << "Test 5: Address 0x01 | Expected: 0x01 | Got: " << readData.read() << endl;

        sc_stop();
    }

    SC_CTOR(DataMemory_testbench) {
        dataMemory = new DataMemory<8, 8>("DataMemory");
        dataMemory->clock(clk);
        dataMemory->writeEnabled(writeEnabled);
        dataMemory->address(address);
        dataMemory->writeData(writeData);
        dataMemory->readData(readData);
        dataMemory->traceEnabled = false;

        SC_THREAD(test);
    }

    ~DataMemory_testbench() {
        delete dataMemory;
    }
};

int sc_main(int argc, char* argv[]) {
    DataMemory_testbench dataMemoryTestbench("dataMemoryTestbench");

    sc_start();

    return 0;
}
