#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <systemc.h>
#include "Datapath.h"
#include "Controller.h"

template<int DATA_WIDTH = 8, int DADDR_WIDTH = 8, int INSTR_WIDTH = 14, int IADDR_WIDTH = 10, int STACK_ADDR_WIDTH = 3,
    int REGFILE_ADDR_WIDTH = 7, int STACK_DEPTH = (1 << STACK_ADDR_WIDTH), int REGFILE_DEPTH = (1 << REGFILE_ADDR_WIDTH)>
SC_MODULE(Processor) {
    sc_in<bool> clock, reset;
    sc_in<sc_uint<INSTR_WIDTH>> instructionCode;
    sc_in<sc_uint<DATA_WIDTH>> dataFromDataMem;

    sc_out<sc_uint<IADDR_WIDTH>> instructionMemAddress;
    sc_out<sc_uint<DADDR_WIDTH>> dataMemAddress;
    sc_out<sc_uint<DATA_WIDTH>> dataToWriteToDataMem;
    sc_out<bool> sw, instructionMemError, stackError;
    sc_out<sc_uint<DATA_WIDTH>> dataBus;

    sc_signal<bool> goCall, skip, ti, lw, accumulatorWrite, z,
        readStack, writeStack, registerFileWrite, pz, gotoznz;

    Datapath *datapath;
    Controller *controller;

    SC_CTOR(Processor) {
        datapath = new Datapath("datapath");
        datapath->clk(clock);
        datapath->reset(reset);
        datapath->Instr(instructionCode);
        datapath->rstack(readStack);
        datapath->wstack(writeStack);
        datapath->gocall(goCall);
        datapath->skip(skip);
        datapath->d(registerFileWrite);
        datapath->ti(ti);
        datapath->lw(lw);
        datapath->wew(accumulatorWrite);
        datapath->Read_Data(dataFromDataMem);
        datapath->gotoznz(gotoznz);
        datapath->IAddr(instructionMemAddress);
        datapath->DAddr(dataMemAddress);
        datapath->Write_Data(dataToWriteToDataMem);
        datapath->error_imem(instructionMemError);
        datapath->error_stack(stackError);
        datapath->z(z);
        datapath->Data_Bus(dataBus);
        datapath->pz(pz);

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
    }

    ~Processor() {
        delete datapath;
        delete controller;
    }
};

#endif //PROCESSOR_H
