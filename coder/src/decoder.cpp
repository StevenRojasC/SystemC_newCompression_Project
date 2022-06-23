#include "../include/decoder.h"
#include <lz4.h>

void Decoder::decode( void ) {
    while (true) {
        wait(dec_t);
        
        printf("********** Running Decoder!!!! **********\n\n");

        int i;
        int compressed_length = SIZE;

        char szSource[SIZE];
        for (i=0; i<SIZE; i++) {
            szSource[i] = coded_input[i];
            if (szSource[i] == (char)0) {
                compressed_length -= 1;
            }
        }

        char* pchCompressedInput = new char[compressed_length];
        printf("Compressed length: %d\n", compressed_length);

        for (i=0; i<compressed_length; i++) {
            pchCompressedInput = pchCompressedInput + szSource[i];
        }

        char* pchDeCompressed = new char[SIZE];

        LZ4_decompress_fast(pchCompressedInput, pchDeCompressed, SIZE);

        printf("Decompressed data: [%s]\n", pchDeCompressed);

        if (compressed_length == SIZE) {
            printf("Data is not compressed!\n");
            printf("Sending data just as received...\n\n");

            for (i=0; i<SIZE; i++) {
                buffer_LPC[i] = *(szSource+i);
            }        
        } else {
            printf("Decompression success!\nDecompressed file: %d bytes out of %d bytes\n", SIZE, compressed_length);
            printf("Sending decompressed data!\n\n");

            for (i=0; i<SIZE; i++) {
                buffer_LPC[i] = *(pchDeCompressed+i);
            }  
        }

        printf("********** Decoder finished execution!!!! **********\n\n");
    }
}

void Decoder::dec(int8_t * input) {
    std::copy(input, input+SIZE, coded_input);

    dec_t.notify(2, SC_NS);
}

int8_t* Decoder::read(void) {

    return buffer_LPC;
}