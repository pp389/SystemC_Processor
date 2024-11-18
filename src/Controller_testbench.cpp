#include <systemc.h>
#include "Controller.h"

using namespace sc_core;
using namespace sc_dt;

SC_MODULE(Controller_testbench) {
    Controller* controller;

    sc_signal<sc_uint<14>> instructionCode;
    sc_signal<bool> z, pz;
    sc_signal<bool> readStack, writeStack, goCall, skip, registerFileWrite;
    sc_signal<bool> ti, lw, accumulatorWrite, sw, gotoznz;

    void compareActualValuesWithExpected(bool readStack_expected, bool writeStack_expected, bool goCall_expected,
        bool skip_expected, bool registerFileWrite_expected, bool ti_expected, bool lw_expected, 
        bool accumulatorWrite_expected, bool sw_expected, bool gotoznz_expected) {

        std::cout << "readStack expected value = " << readStack_expected << " | Got readStack = " << readStack.read() << std::endl;
        std::cout << "writeStack expected value = " << writeStack_expected << " | Got writeStack = " << writeStack.read() << std::endl;
        std::cout << "goCall expected value = " << goCall_expected << " | Got goCall = " << goCall.read() << std::endl;
        std::cout << "skip expected value = " << skip_expected << " | Got skip = " << skip.read() << std::endl;
        std::cout << "registerFileWrite expected value = " << registerFileWrite_expected << " | Got registerFileWrite = " << registerFileWrite.read() << std::endl;
        std::cout << "ti expected value = " << ti_expected << " | Got ti = " << ti.read() << std::endl;
        std::cout << "lw expected value = " << lw_expected << " | Got lw = " << lw.read() << std::endl;
        std::cout << "accumulatorWrite expected value = " << accumulatorWrite_expected << " | Got accumulatorWrite = " << accumulatorWrite.read() << std::endl;
        std::cout << "sw expected value = " << sw_expected << " | Got sw = " << sw.read() << std::endl;
        std::cout << "gotoznz expected value = " << gotoznz_expected << " | Got gotoznz = " << gotoznz.read() << std::endl;
    }

    void test_addwf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - addwf instruction" << std::endl;
        instructionCode.write(0b00011100000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, registerFileWrite, 0, 0, !registerFileWrite, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_andwf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - andwf instruction" << std::endl;
        instructionCode.write(0b00010100000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, registerFileWrite, 0, 0, !registerFileWrite, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_clrf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - clrf instruction" << std::endl;
        instructionCode.write(0b00000110000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, 1, 0, 0, 0, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_clrw() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - clrw instruction" << std::endl;
        instructionCode.write(0b00000100000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_comf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - comf instruction" << std::endl;
        instructionCode.write(0b00100100000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, registerFileWrite, 0, 0, !registerFileWrite, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_decf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - decf instruction" << std::endl;
        instructionCode.write(0b00001100000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, registerFileWrite, 0, 0, !registerFileWrite, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_decfsz() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - decfsz instruction" << std::endl;
        instructionCode.write(0b00101100000000);
        z.write(1);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 1, registerFileWrite, 0, 0, !registerFileWrite, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_incf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - incf instruction" << std::endl;
        instructionCode.write(0b00101000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, registerFileWrite, 0, 0, !registerFileWrite, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_incfsz() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - incfsz instruction" << std::endl;
        instructionCode.write(0b00111100000000);
        z.write(1);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 1, registerFileWrite, 0, 0, !registerFileWrite, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_iorwf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - iorwf instruction" << std::endl;
        instructionCode.write(0b00010000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, registerFileWrite, 0, 0, !registerFileWrite, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_movf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - movf instruction" << std::endl;
        instructionCode.write(0b00100000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, registerFileWrite, 0, 0, !registerFileWrite, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_movwf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - movwf instruction" << std::endl;
        instructionCode.write(0b00000010000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, 1, 0, 0, 0, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_nop() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - nop instruction" << std::endl;
        instructionCode.write(0b00000000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_rlf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - rlf instruction" << std::endl;
        instructionCode.write(0b00110100000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, registerFileWrite, 0, 0, !registerFileWrite, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_rrf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - rrf instruction" << std::endl;
        instructionCode.write(0b00110000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, registerFileWrite, 0, 0, !registerFileWrite, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_subwf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - subwf instruction" << std::endl;
        instructionCode.write(0b00001000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, registerFileWrite, 0, 0, !registerFileWrite, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_swapf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - swapf instruction" << std::endl;
        instructionCode.write(0b00111000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, registerFileWrite, 0, 0, !registerFileWrite, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_xorwf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - xorwf instruction" << std::endl;
        instructionCode.write(0b00011000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, registerFileWrite, 0, 0, !registerFileWrite, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_bcf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - bcf instruction" << std::endl;
        instructionCode.write(0b01000000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, 1, 0, 0, 0, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_bsf() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - bsf instruction" << std::endl;
        instructionCode.write(0b01010000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, 1, 0, 0, 0, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_btfsc() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - btfsc instruction" << std::endl;
        instructionCode.write(0b01100000000000);
        z.write(1);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 1, 0, 0, 0, 1, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_btfss() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - btfss instruction" << std::endl;
        instructionCode.write(0b01110000000000);
        z.write(0);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 1, 0, 0, 0, 1, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_addlw() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - addlw instruction" << std::endl;
        instructionCode.write(0b11111000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, 0, 1, 0, 1, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_andlw() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - andlw instruction" << std::endl;
        instructionCode.write(0b11100100000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, 0, 1, 0, 1, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_iorlw() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - iorlw instruction" << std::endl;
        instructionCode.write(0b11100000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, 0, 1, 0, 1, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_movlw() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - movlw instruction" << std::endl;
        instructionCode.write(0b11000000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, 0, 1, 0, 1, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_lw() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - lw instruction" << std::endl;
        instructionCode.write(0b11000100000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, 0, 1, 1, 1, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_sw() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - sw instruction" << std::endl;
        instructionCode.write(0b11001000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, 0, 1, 0, 0, 1, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_sublw() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - sublw instruction" << std::endl;
        instructionCode.write(0b11110000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, 0, 1, 0, 1, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_xorlw() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - xorlw instruction" << std::endl;
        instructionCode.write(0b11101000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 0, 0, 0, 1, 0, 1, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_call() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - call instruction" << std::endl;
        instructionCode.write(0b10000000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 1, 1, 0, 0, 0, 0, 0, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_goto() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - goto instruction" << std::endl;
        instructionCode.write(0b10100000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_return() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - return instruction" << std::endl;
        instructionCode.write(0b00000000001000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_retlw() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - retlw instruction" << std::endl;
        instructionCode.write(0b11010000000000);
        wait(100, SC_NS);
        compareActualValuesWithExpected(1, 0, 0, 0, 0, 1, 0, 1, 0, 0);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_gotoz() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - gotoz instruction" << std::endl;
        instructionCode.write(0b11010100000000);
        pz.write(1);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 1, 0, 0, 0, 0, 0, 0, 1);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test_gotons() {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Controller test - gotons instruction" << std::endl;
        instructionCode.write(0b11011000000000);
        pz.write(0);
        wait(100, SC_NS);
        compareActualValuesWithExpected(0, 0, 1, 0, 0, 0, 0, 0, 0, 1);
        std::cout << "---------------------------------------------" << std::endl << std::endl;
    }

    void test() {
        test_addwf();
        test_andwf();
        test_clrf();
        test_clrw();
        test_comf();
        test_decf();
        test_decfsz();
        test_incf();
        test_incfsz();
        test_iorwf();
        test_movf();
        test_movwf();
        test_nop();
        test_rlf();
        test_rrf();
        test_subwf();
        test_swapf();
        test_xorwf();
        test_bcf();
        test_bsf();
        test_btfsc();
        test_btfss();
        test_addlw();
        test_andlw();
        test_iorlw();
        test_movlw();
        test_lw();
        test_sw();
        test_sublw();
        test_xorlw();
        test_call();
        test_goto();
        test_return();
        test_retlw();
        test_retlw();
        test_gotoz();
        test_gotons();
    }

    SC_CTOR(Controller_testbench) {
        controller = new Controller("controller");
        controller->instructionCode(instructionCode);
        controller->z(z);
        controller->pz(pz);
        controller->readStack(readStack);
        controller->writeStack(writeStack);
        controller->goCall(goCall);
        controller->skip(skip);
        controller->registerFileWrite(registerFileWrite);
        controller->ti(ti);
        controller->lw(lw);
        controller->accumulatorWrite(accumulatorWrite);
        controller->sw(sw);
        controller->gotoznz(gotoznz);
        controller->traceEnabled = true;

        SC_THREAD(test);
    }

    ~Controller_testbench() {
        delete controller;
    }
};

int sc_main(int argc, char* argv[]) {
    Controller_testbench tb("tb");

    sc_start();

    return 0;
}
