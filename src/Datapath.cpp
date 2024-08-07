#include "Datapath.h"

void Datapath::set_z() {
    z.write(!(Data_Bus.read().or_reduce()));
}

void Datapath::assign_addresses() {
    IAddr.write(PC);
    DAddr.write(k1);
}