#include <iostream>
#include <bitset>
#include "Controller.h"

void Controller::process() {
    trace_operation();
    lw.write(instructionCode.read().range(13, 8) == 0b110001);
    sw.write(instructionCode.read().range(13, 8) == 0b110010);
    bool lwValue = instructionCode.read().range(13, 8) == 0b110001;
    bool swValue = instructionCode.read().range(13, 8) == 0b110010;
    bool call = (instructionCode.read().range(13, 11) == 0b100);
    bool goto_instr = (instructionCode.read().range(13, 11) == 0b101);
    bool wreturn = (instructionCode.read() == 0b00000000001000);
    bool retlw = (instructionCode.read().range(13, 8) == 0b110100);
    bool decfsz = (instructionCode.read().range(13, 8) == 0b001011);
    bool incfsz = (instructionCode.read().range(13, 8) == 0b001111);
    bool btfsc = (instructionCode.read().range(13, 10) == 0b0110);
    bool btfss = (instructionCode.read().range(13, 10) == 0b0111);
    bool gotoz = (instructionCode.read().range(13, 8) == 0b110101);
    bool gotonz = (instructionCode.read().range(13, 8) == 0b110110);

    readStack.write(wreturn || retlw);
    writeStack.write(instructionCode.read().range(13, 11) == 0b100);
    skip.write((z.read() && decfsz) || (z.read() && incfsz) || (z.read() && btfsc) || (!z.read() && btfss));
    ti.write((instructionCode.read().range(13, 12) == 0b11) ? 1 : 0);
    bool gotoznzValue = ((gotoz && pz.read()) ? 1 : ((gotonz && !pz.read()) ? 1 : 0));
    gotoznz.write((gotoz && pz.read()) ? 1 : ((gotonz && !pz.read()) ? 1 : 0));
    goCall.write(goto_instr || call || gotoznzValue);

    bool regFileWriteValue;
    if (instructionCode.read().range(13, 12) == 0b00)
        regFileWriteValue = instructionCode.read()[7];
    else if ((instructionCode.read().range(13, 10) == 0b0100) || (instructionCode.read().range(13, 10) == 0b0101))
        regFileWriteValue = true;
    else
        regFileWriteValue = false;
    registerFileWrite.write(regFileWriteValue);

    accumulatorWrite.write((!regFileWriteValue || lwValue || retlw) && (!swValue) && (!goCall.read()) && (!wreturn));
}

void Controller::trace_operation() {
    if (traceEnabled) {
        std::cout << "time = " << sc_time_stamp() << ", [CONTROLLER] Instruction: " << std::bitset<14>(instructionCode.read()) << std::endl;
    }
}