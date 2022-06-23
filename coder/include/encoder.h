/* File encoder.h */

#include <systemc.h>

static const int SIZE = 26;

SC_MODULE ( Encoder ) {
    sc_in< sc_int<8> > buffer_LPC[SIZE];

    sc_event in_t;

    sc_int<8> temp_output[SIZE];

    sc_out< sc_int<8> > codec_output[SIZE];

    sc_event out_t;

    void encode(void);
    void enc(void);
    void out(void);
    void write(void);

    SC_CTOR( Encoder ) {
        SC_THREAD(encode);
        SC_THREAD(write);
    }
};