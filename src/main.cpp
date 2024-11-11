#include <systemc.h>
#include "TopLevel.h"  // Zak�adaj�c, �e modu� jest zapisany w tym pliku

// G��wna klasa symulacyjna
SC_MODULE(testbench)
{
    // Deklaracja sygna��w
    sc_signal<bool> clk, reset;
    sc_signal<sc_uint<10>> IAddr;
    sc_signal<sc_uint<8>> DAddr;
    sc_signal<sc_uint<8>> Write_Data;
    sc_signal<sc_uint<8>> Read_Data;
    sc_signal<bool> error_imem, error_stack;
    sc_signal<sc_uint<8>> Data_Bus;
    sc_signal<sc_uint<14>> Instr;

    // Instancja CPU
    TopLevel<> cpu_inst;

    // Proces generuj�cy sygna� zegara
    void generate_clk()
    {
        while (true) {
            clk.write(true);
            wait(10, SC_NS);  // Czas trwania jednej po�owy cyklu zegara
            clk.write(false);
            wait(10, SC_NS);  // Czas trwania drugiej po�owy cyklu zegara
        }
    }

    // Proces generuj�cy sygna� resetu
    void generate_reset()
    {
        reset.write(true);
        wait(20, SC_NS);  // Czas resetu
        reset.write(false);
    }

    // Konstruktor
    SC_CTOR(testbench)
        : cpu_inst("cpu_inst")
    {
        // Po��czenie sygna��w z instancj� CPU
        cpu_inst.clk(clk);
        cpu_inst.reset(reset);
        cpu_inst.IAddr(IAddr);
        cpu_inst.DAddr(DAddr);
        cpu_inst.Write_Data(Write_Data);
        cpu_inst.Read_Data(Read_Data);
        cpu_inst.error_imem(error_imem);
        cpu_inst.error_stack(error_stack);
        cpu_inst.Data_Bus(Data_Bus);
        cpu_inst.Instr(Instr);

        // Procesy
        SC_THREAD(generate_clk);
        SC_THREAD(generate_reset);
    }
};

// G��wna funkcja symulacyjna
int sc_main(int argc, char* argv[])
{
    // Utworzenie obiektu testbench
    testbench tb("tb");

    // Uruchomienie symulacji przez 1000 jednostek czasu
    sc_start(1000, SC_NS);

    return 0;
}
