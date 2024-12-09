#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <systemc.h>
#include "Datapath.h"
#include "Controller.h"

template<int DATA_WIDTH = 8, int DADDR_WIDTH = 8, int INSTR_WIDTH = 14, int IADDR_WIDTH = 10, int STACK_ADDR_WIDTH = 3,
    int REGFILE_ADDR_WIDTH = 7, int STACK_DEPTH = (1 << STACK_ADDR_WIDTH), int REGFILE_DEPTH = (1 << REGFILE_ADDR_WIDTH)>
SC_MODULE(Processor) {
    sc_in<bool> clk, reset;
    sc_in<sc_uint<INSTR_WIDTH>> Instr;
    sc_in<sc_uint<DATA_WIDTH>> Read_Data;

    sc_out<sc_uint<IADDR_WIDTH>> IAddr;
    sc_out<sc_uint<DADDR_WIDTH>> DAddr;
    sc_out<sc_uint<DATA_WIDTH>> Write_Data;
    sc_out<bool> sw;
    sc_out<bool> error_imem, error_stack;
    sc_out<sc_uint<DATA_WIDTH>> Data_Bus;

    sc_signal<bool> gocall, skip, ti, lw, wew, z;
    sc_signal<bool> rstack, wstack, d, pz, gotoznz;

    Datapath *datapath;
    Controller *controller;

    SC_CTOR(Processor) {
        datapath = new Datapath("ex_datapath");
        datapath->clk(clk);
        datapath->reset(reset);
        datapath->Instr(Instr);
        datapath->rstack(rstack);
        datapath->wstack(wstack);
        datapath->gocall(gocall);
        datapath->skip(skip);
        datapath->d(d);
        datapath->ti(ti);
        datapath->lw(lw);
        datapath->wew(wew);
        datapath->Read_Data(Read_Data);
        datapath->gotoznz(gotoznz);
        datapath->IAddr(IAddr);
        datapath->DAddr(DAddr);
        datapath->Write_Data(Write_Data);
        datapath->error_imem(error_imem);
        datapath->error_stack(error_stack);
        datapath->z(z);
        datapath->Data_Bus(Data_Bus);
        datapath->pz(pz);

        controller = new Controller("ex_controller");
        controller->instructionCode(Instr);
        controller->z(z);
        controller->pz(pz);
        controller->readStack(rstack);
        controller->writeStack(wstack);
        controller->goCall(gocall);
        controller->skip(skip);
        controller->registerFileWrite(d);
        controller->ti(ti);
        controller->lw(lw);
        controller->accumulatorWrite(wew);
        controller->sw(sw);
        controller->gotoznz(gotoznz);
    }

    ~Processor() {
        delete datapath;
        delete controller;
    }
};

#endif //PROCESSOR_H
