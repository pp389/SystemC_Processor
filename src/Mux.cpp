#include "Mux.h"

template<int WIDTH>
void Mux2_1<WIDTH>::process() {
    y.write(s.read() ? d1.read() : d0.read());
}