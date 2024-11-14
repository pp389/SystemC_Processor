#include <systemc.h>
#include "TopLevel.h"

int sc_main(int argc, char* argv[]) {
    // Sygnały
    sc_clock clk("clk", 10, SC_NS);  // Okres zegara 10 ns
    sc_signal<bool> reset;  // Sygnał resetu
    sc_signal<sc_uint<8>> read_data;
    sc_signal<sc_uint<14>> instr;
    sc_signal<sc_uint<10>> iaddr;
    sc_signal<sc_uint<8>> daddr;
    sc_signal<sc_uint<8>> write_data;
    sc_signal<bool> sw;  // Sygnał sw
    sc_signal<bool> error_imem, error_stack;
    sc_signal<sc_uint<8>> data_bus;

    // Inicjalizacja modułu TopLevel
    TopLevel<8, 8, 14, 10, 3, 7, 8, 128>* top = new TopLevel<8, 8, 14, 10, 3, 7, 8, 128>("TopLevel");

    // Połączenie sygnałów
    top->clk(clk);
    top->reset(reset);
    top->IAddr(iaddr);
    top->DAddr(daddr);
    top->Write_Data(write_data);
    top->Read_Data(read_data);
    top->error_imem(error_imem);
    top->error_stack(error_stack);
    top->Data_Bus(data_bus);
    top->Instr(instr);


    // Resetowanie
    reset = false;
    sc_start(5, SC_NS);  // Czekaj chwilę, by procesor mógł się zresetować
    reset = true;

    // Rozpoczęcie symulacji na 100 ns, aby procesor mógł odczytać instrukcje i je wykonać
    sc_start(100, SC_NS);

    top->processor->ex_datapath->ex_regfile->dump();
    std::cout << "ACCUMULATOR: " << top->processor->ex_datapath->ex_W->q << std::endl;
    top->dataMemory->dump();

    // Zwolnienie pamięci
    delete top;

    return 0;
}
