#include "Ffc.h"

void Ffc::process() {
    if (!reset.read())
        q.write(false);
    else if (clk.posedge())
        q.write(d.read());
}