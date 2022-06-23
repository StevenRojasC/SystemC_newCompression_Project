#include "../include/encoder.h"
#include <lz4.h>

void Encoder::encode( void ) {
    while(true) {
        wait(in_t);

        printf("********** Running Encoder!!!! **********\n\n");

        int i;

        char szSource[SIZE];
        for (i=0; i<SIZE; i++) {
            szSource[i] = buffer_LPC[i].read();
        }
        // std::string s(szSource);       // Esta es la solucion a nuestros problemas

        char* pchCompressed = new char[SIZE];

        // int result = LZ4_compress_default((const char *)(&s), pchCompressed, SIZE, SIZE);
        int result = LZ4_compress_default((const char *)(&szSource), pchCompressed, SIZE, SIZE);

        if (result == 0) {
            printf("Compression failed! Data can't be compressed any further!\n");
            printf("Sending data just as received...\n\n");
            pchCompressed = szSource;

            for (i=0; i<SIZE; i++) {
                temp_output[i] = *(pchCompressed+i);
            }        
        } else {
            printf("Compression success!\nCompressed file: %d bytes out of %d bytes\n", result, SIZE);
            printf("Sending compressed data!\n\n");

            for (i=0; i<SIZE; i++) {
                if (result < i) {
                    temp_output[i] = *(pchCompressed+i);
                    if (*(pchCompressed+i) == 0) {
                        temp_output[i] = (int8_t)-1;
                    }
                } else {
                    temp_output[i] = (int8_t)0;
                }
            }
        }

        printf("********** Encoder finished execution!!!! **********\n\n");
    }
}

void Encoder::enc(void) {
    in_t.notify(2, SC_NS);
}

void Encoder::out(void){
    out_t.notify(8, SC_NS);
}

void Encoder::write(void) {
    while(true){
        wait(out_t);

        int i;
        for (i=0; i<SIZE; i++) {
                codec_output[i].write(temp_output[i]);
            }  
    }
}