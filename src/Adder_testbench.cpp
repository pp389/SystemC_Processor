#include <systemc.h>
#include "Adder.h"

SC_MODULE(AdderTestbench) {
    //signals declaration
    sc_signal<sc_uint<8>> aSignal, bSignal;
    sc_signal<sc_uint<8>> sumSignal;
    sc_signal<bool> carryOutSignal;

    //adder instance
    Adder<8>* adder_instance;

    SC_CTOR(AdderTestbench) {
        adder_instance = new Adder<8>("adder_instance");

        adder_instance->a(aSignal);
        adder_instance->b(bSignal);
        adder_instance->result(sumSignal);
        adder_instance->carryOut(carryOutSignal);

        SC_THREAD(test);
    }

    void test() {
        //Test 1: Adding two values without carry
        aSignal.write(10);
        bSignal.write(20);
        wait(10, SC_NS);
        cout << "Test 1 - no carry: a = " << aSignal.read() << ", b = " << bSignal.read()
             << ", output = " << sumSignal.read() << ", carry = " << carryOutSignal.read() << endl;

        //Test 2: Adding two values with carry
        aSignal.write(200);
        bSignal.write(100);
        wait(10, SC_NS);
        cout << "Test 2 - with carry: a = " << aSignal.read() << ", b = " << bSignal.read()
             << ", output = " << sumSignal.read() << ", carry = " << carryOutSignal.read() << endl;
    }
};

int sc_main(int argc, char* argv[]) {
    AdderTestbench tb("tb");

    sc_start();

    return 0;
}
