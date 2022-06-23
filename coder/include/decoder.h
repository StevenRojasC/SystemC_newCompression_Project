/* File decoder.h */

#include <systemc.h>

static const int SIZE = 26;

SC_MODULE ( Decoder ) {
    int8_t coded_input[SIZE];
    int8_t buffer_LPC[SIZE];    
    sc_event dec_t;

    void decode(void);
    void dec(int8_t * input);
    int8_t* read(void);

    SC_CTOR( Decoder ) {

        SC_THREAD(decode);
    }
};