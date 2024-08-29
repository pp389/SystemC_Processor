#include "Register.h"

template<int WIDTH>
void Register_we<WIDTH>::process() {
    if (!reset.read())
        q.write(0);
    else if (clk.posedge()) {
        if (we.read())
            q.write(d.read());
        else
            q.write(q.read());
    }
}