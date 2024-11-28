#include <systemc>
#include "RegisterFile.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

SC_MODULE(RegisterFile_testbench) {
    //signals declaration
    sc_signal<bool> clock;
    sc_signal<bool> writeEnabled;
    sc_signal<sc_uint<7>> regNumber;
    sc_signal<sc_uint<8>> writeData;
    sc_signal<sc_uint<8>> readData;

    //register file instance
    RegisterFile<7, 128, 8>* registerFileInstance;

    void generateClockSignal() {
        while (true) {
            clock.write(false);
            wait(5, SC_NS);
            clock.write(true);
            wait(5, SC_NS);
        }
    }

    void test() {
        // Test 1: Write to reg 0x01
        writeEnabled.write(true);
        regNumber.write(0x01);
        writeData.write(0xAA);
        wait(10, SC_NS);
        cout << "Test 1: Write to reg 0x01 | Expected rd=170 | Got rd=" << readData.read()
             << " | " << ((readData.read() == 0xAA) ? "PASSED" : "FAILED") << endl;

        // Test 2: Read from reg 0x01
        writeEnabled.write(false);
        regNumber.write(0x01);
        wait(10, SC_NS);
        cout << "Test 2: Read from reg 0x01 | Expected rd=170 | Got rd=" << readData.read()
             << " | " << ((readData.read() == 0xAA) ? "PASSED" : "FAILED") << endl;

        // Test 3: Write to reg 0x02
        writeEnabled.write(true);
        regNumber.write(0x02);
        writeData.write(0x55);
        wait(10, SC_NS);
        cout << "Test 3: Write to reg 0x02 | Expected rd=85 | Got rd=" << readData.read()
             << " | " << ((readData.read() == 0x55) ? "PASSED" : "FAILED") << endl;

        // Test 4: Read from reg 0x02
        writeEnabled.write(false);  // Wyłączenie zapisu
        regNumber.write(0x02);  // Adres rejestru
        wait(10, SC_NS);
        cout << "Test 4: Read from reg 0x02 | Expected rd=85 | Got rd=" << readData.read()
             << " | " << ((readData.read() == 0x55) ? "PASSED" : "FAILED") << endl;

        sc_stop();
    }

    SC_CTOR(RegisterFile_testbench) {
        registerFileInstance = new RegisterFile<7, 128, 8>("registerFileInstance");
        registerFileInstance->clock(clock);
        registerFileInstance->writeEnabled(writeEnabled);
        registerFileInstance->regNumber(regNumber);
        registerFileInstance->writeData(writeData);
        registerFileInstance->readData(readData);

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
