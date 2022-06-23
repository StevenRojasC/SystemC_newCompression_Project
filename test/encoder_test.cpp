#include <systemc.h>
#include <encoder.h>

static const int input_range = int(pow(2, 8));


sc_signal<sc_int<8> > buffer_LPC_input[SIZE];

sc_signal<sc_int<8> > codec_output_port[SIZE];


void print_input_values(void) {
    int z;
    printf("Current data at input: [ ");
    for (z=0; z<SIZE; z++) {
        int temp1 = buffer_LPC_input[z].read();
        printf("%d ", temp1);
    }
    printf("]\n\n");
}

void write_random_inputs(Encoder * module) {

    int z;
    for (z=0; z<SIZE; z++) {
        int8_t temp = (rand() % input_range) - (input_range/2);
        buffer_LPC_input[z] = temp;
    }
    printf("Wrote random values at input !!!\n\n");
    print_input_values();
    module->enc();
}

void print_output_values(Encoder * module) {

    module->out();

    int z;
    printf("Data at output: [ ");
    for (z=0; z<SIZE; z++) {
        char temp = codec_output_port[z].read();
        printf("%d ", temp);
    }
    printf("]\n\n\n\n");
}



int sc_main(int argc, char* argv[]) {

    printf("\nStarting Testbench........\n\n");

    Encoder uut("uut");

    int i;
    for (i=0; i<SIZE; i++) {
        uut.buffer_LPC[i](buffer_LPC_input[i]);
        uut.codec_output[i](codec_output_port[i]);
    }

    sc_start(0, SC_NS);

    for (i=0; i<20; i++){
        cout << "@" << sc_time_stamp()<< endl;

        write_random_inputs(&uut);

        sc_start(10, SC_NS);

        print_output_values(&uut);

        sc_start(10, SC_NS);
    }

    sc_stop();

    printf("\n\nTestbench Ended........\n\n");

    return 0;
}