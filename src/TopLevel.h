#ifndef TOPLEVEL_H
#define TOPLEVEL_H

#include <systemc>
#include "Processor.h"
#include "InstructionMemory.h"
#include "DataMemory.h"

template<
    int DATA_WIDTH = 8,
    int DADDR_WIDTH = 8,
    int INSTR_WIDTH = 14,
    int IADDR_WIDTH = 10,
    int STACK_ADDR_WIDTH = 3,
    int REGFILE_ADDR_WIDTH = 7,
    int STACK_DEPTH = (1 << STACK_ADDR_WIDTH),
    int REGFILE_DEPTH = (1 << REGFILE_ADDR_WIDTH)
>
SC_MODULE(TopLevel) {
    sc_in<bool> clk, reset;
    sc_out<sc_uint<IADDR_WIDTH>> IAddr;
    sc_out<sc_uint<DADDR_WIDTH>> DAddr;
    sc_out<sc_uint<DATA_WIDTH>> Write_Data;
    sc_out<sc_uint<DATA_WIDTH>> Read_Data;
    sc_out<bool> error_imem, error_stack;
    sc_out<sc_uint<DATA_WIDTH>> Data_Bus;
    sc_out<sc_uint<INSTR_WIDTH>> Instr;

    sc_signal<bool> sw;
    sc_signal<sc_uint<16>> IRD;

    Processor<
        DATA_WIDTH, DADDR_WIDTH, INSTR_WIDTH, IADDR_WIDTH,
        STACK_ADDR_WIDTH, REGFILE_ADDR_WIDTH, STACK_DEPTH, REGFILE_DEPTH
    >* processor;

    InstructionMemory<IADDR_WIDTH, (1 << IADDR_WIDTH), 16>* instructionMemory;
    DataMemory<DADDR_WIDTH, DATA_WIDTH>* dataMemory;

    SC_CTOR(TopLevel) {
        processor = new Processor<
            DATA_WIDTH, DADDR_WIDTH, INSTR_WIDTH, IADDR_WIDTH,
            STACK_ADDR_WIDTH, REGFILE_ADDR_WIDTH, STACK_DEPTH, REGFILE_DEPTH
        >("processor");

        processor->clk(clk);
        processor->reset(reset);
        processor->Instr(Instr);
        processor->Read_Data(Read_Data);
        processor->IAddr(IAddr);
        processor->DAddr(DAddr);
        processor->Write_Data(Write_Data);
        processor->sw(sw);
        processor->error_imem(error_imem);
        processor->error_stack(error_stack);
        processor->Data_Bus(Data_Bus);

        instructionMemory = new InstructionMemory<IADDR_WIDTH, (1 << IADDR_WIDTH), 16>("instructionMemory");
        instructionMemory->a(IAddr);
        instructionMemory->rd(IRD);

        dataMemory = new DataMemory<DADDR_WIDTH, DATA_WIDTH>("dataMemory");
        dataMemory->clk(clk);
        dataMemory->we(sw);
        dataMemory->a(DAddr);
        dataMemory->wd(Write_Data);
        dataMemory->rd(Read_Data);

        SC_METHOD(assign_instr);
        sensitive << IRD;
    }

    void assign_instr();
};

template<
    int DATA_WIDTH,
    int DADDR_WIDTH,
    int INSTR_WIDTH,
    int IADDR_WIDTH,
    int STACK_ADDR_WIDTH,
    int REGFILE_ADDR_WIDTH,
    int STACK_DEPTH,
    int REGFILE_DEPTH
>
void TopLevel<DATA_WIDTH,
    DADDR_WIDTH,
    INSTR_WIDTH,
    IADDR_WIDTH,
    STACK_ADDR_WIDTH,
    REGFILE_ADDR_WIDTH,
    STACK_DEPTH,
    REGFILE_DEPTH>::assign_instr()
{
    Instr.write(IRD.read().range(INSTR_WIDTH - 1, 0));
}

#endif //TOPLEVEL_H
