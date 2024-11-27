#ifndef DATAPATH_H
#define DATAPATH_H

#include <systemc.h>
#include "Mux.h"
#include "Ffc.h"
#include "Register.h"
#include "Adder.h"
#include "RegisterFile.h"
#include "Stack.h"
#include "ALU.h"

SC_MODULE(Datapath) {
    static const int DATA_WIDTH = 8;
    static const int DADDR_WIDTH = 8;
    static const int INSTR_WIDTH = 14;
    static const int IADDR_WIDTH = 10;
    static const int STACK_ADDR_WIDTH = 3;
    static const int REGFILE_ADDR_WIDTH = 7;
    static const int STACK_DEPTH = (1 << STACK_ADDR_WIDTH);
    static const int REGFILE_DEPTH = (1 << REGFILE_ADDR_WIDTH);

    sc_in<bool> clk, reset;
    sc_in<sc_uint<INSTR_WIDTH>> Instr;
    sc_in<bool> rstack, wstack, gocall, skip;
    sc_in<bool> d, ti, lw, wew;
    sc_in<sc_uint<DATA_WIDTH>> Read_Data;
    sc_in<bool> gotoznz;

    sc_out<sc_uint<IADDR_WIDTH>> IAddr;
    sc_out<sc_uint<DADDR_WIDTH>> DAddr;
    sc_out<sc_uint<DATA_WIDTH>> Write_Data;
    sc_out<bool> error_imem, error_stack;
    sc_out<bool> z;
    sc_out<sc_uint<DATA_WIDTH>> Data_Bus;
    sc_out<bool> pz;

    sc_signal<sc_uint<8>> k1;
    sc_signal<sc_uint<10>> k2;
    sc_signal<sc_uint<7>> f;
    sc_signal<sc_uint<IADDR_WIDTH>> PCPlus, PC, PC1, PC2, PC3, PC4, PC5;
    sc_signal<sc_uint<DATA_WIDTH>> A_ALU, RF_out, W, W1;
    sc_signal<bool> c, wffc, ff_rstack;
    sc_signal<sc_uint<IADDR_WIDTH>> const1, const2, const3;
    sc_signal<sc_uint<7>> const4;

    // Moduły
    Register<IADDR_WIDTH>* ex_pc;
    Mux2_1<IADDR_WIDTH>* ex_pc1, * ex_pc2, * ex_pc3, * ex_pc5;
    Ffc* ex_rstack;
    Adder<IADDR_WIDTH>* ex_adder;
    Stack<IADDR_WIDTH, STACK_ADDR_WIDTH, STACK_DEPTH>* ex_stack;
    RegisterFile<REGFILE_ADDR_WIDTH, REGFILE_DEPTH, DATA_WIDTH>* ex_regfile;
    Mux2_1<DATA_WIDTH>* ex_A_ALU, * ex_W1;
    Register_we<DATA_WIDTH>* ex_W;
    ALU<DATA_WIDTH>* ex_alu;
    Ffc* ex_ffc, * ex_ffpz;

    // Proces do odczytu Instr i ustawienia sygnałów k1, k2, f
    void process_instr() {
        k1.write(Instr.read().range(7, 0));    // 8 bitów od 0 do 7
        k2.write(Instr.read().range(9, 0));    // 10 bitów od 0 do 9
        f.write(Instr.read().range(6, 0));     // 7 bitów od 0 do 6
        const4.write(Instr.read().range(13, 7));  // 7 bitów od 7 do 13
    }

    // Konstruktor
    SC_CTOR(Datapath) :
        clk("clk"),
        reset("reset"),
        Instr("Instr")
    {
        const1.write(1);
        const2.write(2);

        // Zarejestrowanie procesu do obsługi sygnału Instr
        SC_METHOD(process_instr);
        sensitive << Instr;  // Proces wrażliwy na zmiany sygnału Instr

        // Inicjalizacja innych modułów
        ex_pc = new Register<IADDR_WIDTH>("ex_pc");
        ex_pc->clk(clk);
        ex_pc->reset(reset);
        ex_pc->d(PC1);
        ex_pc->q(PC);

        ex_pc1 = new Mux2_1<IADDR_WIDTH>("ex_pc1");
        ex_pc1->d0(PC2);
        ex_pc1->d1(PC5);
        ex_pc1->s(gocall);
        ex_pc1->y(PC1);

        ex_pc2 = new Mux2_1<IADDR_WIDTH>("ex_pc2");
        ex_pc2->d0(PCPlus);
        ex_pc2->d1(PC4);
        ex_pc2->s(ff_rstack);
        ex_pc2->y(PC2);

        ex_pc3 = new Mux2_1<IADDR_WIDTH>("ex_pc3");
        ex_pc3->d0(const1);
        ex_pc3->d1(const2);
        ex_pc3->s(skip);
        ex_pc3->y(PC3);

        ex_pc5 = new Mux2_1<IADDR_WIDTH>("ex_pc5");
        ex_pc5->d0(k2);  // k2 pochodzi z Instr

        sc_bv<IADDR_WIDTH> temp;
        temp.range(IADDR_WIDTH - 1, IADDR_WIDTH - 2) = 0;
        temp.range(IADDR_WIDTH - 3, 0) = k1.read();  // k1 pochodzi z Instr
        const3.write(temp.to_uint());
        ex_pc5->d1(const3);

        ex_pc5->s(gotoznz);
        ex_pc5->y(PC5);

        ex_rstack = new Ffc("ex_rstack");
        ex_rstack->clk(clk);
        ex_rstack->reset(reset);
        ex_rstack->d(rstack);
        ex_rstack->q(ff_rstack);

        ex_adder = new Adder<IADDR_WIDTH>("ex_adder");
        ex_adder->a(PC);
        ex_adder->b(PC3);
        ex_adder->result(PCPlus);
        ex_adder->carryOut(error_imem);

        ex_stack = new Stack<IADDR_WIDTH, STACK_ADDR_WIDTH, STACK_DEPTH>("ex_stack");
        ex_stack->data_in(PCPlus);
        ex_stack->clk(clk);
        ex_stack->reset(reset);
        ex_stack->rd(rstack);
        ex_stack->wr(wstack);
        ex_stack->data_out(PC4);
        ex_stack->error(error_stack);

        ex_regfile = new RegisterFile<REGFILE_ADDR_WIDTH, REGFILE_DEPTH, DATA_WIDTH>("ex_regfile");
        ex_regfile->clk(clk);
        ex_regfile->we(d);
        ex_regfile->a(f);
        ex_regfile->wd(Data_Bus);
        ex_regfile->rd(RF_out);

        ex_A_ALU = new Mux2_1<DATA_WIDTH>("ex_A_ALU");
        ex_A_ALU->d0(RF_out);
        ex_A_ALU->d1(k1);
        ex_A_ALU->s(ti);
        ex_A_ALU->y(A_ALU);

        ex_W1 = new Mux2_1<DATA_WIDTH>("ex_W1");
        ex_W1->d0(Data_Bus);
        ex_W1->d1(Read_Data);
        ex_W1->s(lw);
        ex_W1->y(W1);

        ex_W = new Register_we<DATA_WIDTH>("ex_W");
        ex_W->clk(clk);
        ex_W->reset(reset);
        ex_W->we(wew);
        ex_W->d(W1);
        ex_W->q(Write_Data);

        ex_alu = new ALU<DATA_WIDTH>("ex_alu");
        ex_alu->a(A_ALU);
        ex_alu->b(Write_Data);
        ex_alu->instruction(const4);
        ex_alu->carryFlipFlop(wffc);
        ex_alu->output(Data_Bus);
        ex_alu->carryFlag(c);

        ex_ffc = new Ffc("ex_ffc");
        ex_ffc->clk(clk);
        ex_ffc->reset(reset);
        ex_ffc->d(c);
        ex_ffc->q(wffc);

        ex_ffpz = new Ffc("ex_ffpz");
        ex_ffpz->clk(clk);
        ex_ffpz->reset(reset);
        ex_ffpz->d(z);
        ex_ffpz->q(pz);

        SC_METHOD(set_z);
        sensitive << Data_Bus;

        SC_METHOD(assign_addresses);
        sensitive << PC << k1;
    }

    void set_z();

    void assign_addresses();
};



#endif //DATAPATH_H
