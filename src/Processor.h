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

    Datapath *ex_datapath;
    Controller *ex_controller;

    SC_CTOR(Processor) {
        ex_datapath = new Datapath("ex_datapath");
        ex_datapath->clk(clk);
        ex_datapath->reset(reset);
        ex_datapath->Instr(Instr);
        ex_datapath->rstack(rstack);
        ex_datapath->wstack(wstack);
        ex_datapath->gocall(gocall);
        ex_datapath->skip(skip);
        ex_datapath->d(d);
        ex_datapath->ti(ti);
        ex_datapath->lw(lw);
        ex_datapath->wew(wew);
        ex_datapath->Read_Data(Read_Data);
        ex_datapath->gotoznz(gotoznz);
        ex_datapath->IAddr(IAddr);
        ex_datapath->DAddr(DAddr);
        ex_datapath->Write_Data(Write_Data);
        ex_datapath->error_imem(error_imem);
        ex_datapath->error_stack(error_stack);
        ex_datapath->z(z);
        ex_datapath->Data_Bus(Data_Bus);
        ex_datapath->pz(pz);

        ex_controller = new Controller("ex_controller");
        ex_controller->Instr(Instr);
        ex_controller->z(z);
        ex_controller->pz(pz);
        ex_controller->readStack(rstack);
        ex_controller->writeStack(wstack);
        ex_controller->gocall(gocall);
        ex_controller->skip(skip);
        ex_controller->d(d);
        ex_controller->ti(ti);
        ex_controller->lw(lw);
        ex_controller->wew(wew);
        ex_controller->sw(sw);
        ex_controller->gotoznz(gotoznz);
    }

    ~Processor() {
        delete ex_datapath;
        delete ex_controller;
    }
};

#endif //PROCESSOR_H
