#include "Controller.h"

void Controller::process() {
    lw.write(instructionCode.read().range(13, 8) == 0b110001);
    sw.write(instructionCode.read().range(13, 8) == 0b110010);
    bool call = (instructionCode.read().range(13, 11) == 0b100);
    bool goto_instr = (instructionCode.read().range(13, 11) == 0b101);
    bool wreturn = (instructionCode.read() == 0b00000000001000);
    bool retlw = (instructionCode.read().range(13, 10) == 0b110100);
    bool decfsz = (instructionCode.read().range(13, 8) == 0b001011);
    bool incfsz = (instructionCode.read().range(13, 8) == 0b001111);
    bool btfsc = (instructionCode.read().range(13, 10) == 0b0110);
    bool btfss = (instructionCode.read().range(13, 10) == 0b0111);
    bool gotoz = (instructionCode.read().range(13, 8) == 0b110101);
    bool gotonz = (instructionCode.read().range(13, 8) == 0b110110);

    readStack.write(wreturn || retlw);
    writeStack.write(instructionCode.read().range(13, 11) == 0b100);
    goCall.write(goto_instr || call || gotoznz.read());
    skip.write((z.read() && decfsz) || (z.read() && incfsz) || (z.read() && btfsc) || (!z.read() && btfss));
    ti.write((instructionCode.read().range(13, 12) == 0b11) ? 1 : 0);
    accumulatorWrite.write((!registerFileWrite.read() || lw.read() || retlw) && (!sw.read()) && (!goCall.read()) && (!wreturn));
    gotoznz.write((gotoz && pz.read()) ? 1 : ((gotonz && !pz.read()) ? 1 : 0));

    if (instructionCode.read().range(13, 12) == 0b00)
        registerFileWrite.write(instructionCode.read()[7]);
    else if ((instructionCode.read().range(13, 10) == 0b0100) || (instructionCode.read().range(13, 10) == 0b0101))
        registerFileWrite.write(1);
    else
        registerFileWrite.write(0);
}