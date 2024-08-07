#include "Controller.h"

void Controller::process() {
    bool call, goto_instr, retlw, wreturn, decfsz, incfsz, btfsc, btfss, gotoz, gotonz;

    lw.write(Instr.read().range(13, 8) == 0b110001);
    sw.write(Instr.read().range(13, 8) == 0b110010);
    call = (Instr.read().range(13, 11) == 0b100);
    goto_instr = (Instr.read().range(13, 11) == 0b101);
    wreturn = (Instr.read() == 0b00000000001000);
    retlw = (Instr.read().range(13, 10) == 0b110100);
    decfsz = (Instr.read().range(13, 8) == 0b001011);
    incfsz = (Instr.read().range(13, 8) == 0b001111);
    btfsc = (Instr.read().range(13, 10) == 0b0110);
    btfss = (Instr.read().range(13, 10) == 0b0111);
    gotoz = (Instr.read().range(13, 8) == 0b110101);
    gotonz = (Instr.read().range(13, 8) == 0b110110);

    readStack.write(wreturn || retlw);
    writeStack.write(Instr.read().range(13, 11) == 0b100);
    gocall.write(goto_instr || call || gotoznz.read());
    skip.write((z.read() && decfsz) || (z.read() && incfsz) || (z.read() && btfsc) || (!z.read() && btfss));
    ti.write((Instr.read().range(13, 12) == 0b11) ? 1 : 0);
    wew.write((!d.read() || lw.read() || retlw) && (!sw.read()) && (!gocall.read()) && (!wreturn));
    gotoznz.write((gotoz && pz.read()) ? 1 : ((gotonz && !pz.read()) ? 1 : 0));

    if (Instr.read().range(13, 12) == 0b00)
        d.write(Instr.read()[7]);
    else if ((Instr.read().range(13, 10) == 0b0100) || (Instr.read().range(13, 10) == 0b0101))
        d.write(1);
    else
        d.write(0);
}