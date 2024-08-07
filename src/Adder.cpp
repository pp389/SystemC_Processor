#include "Adder.h"

template<int WIDTH>
void Adder<WIDTH>::process() {
    sc_uint<WIDTH + 1> sum = a.read() + b.read();
    cout.write(sum[WIDTH]);
    y.write(sum.range(WIDTH-1, 0));
}