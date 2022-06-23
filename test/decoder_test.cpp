#include <systemc.h>
#include <decoder.h>

static const int input_range = int(pow(2, 8));

int8_t RX_coded_input[SIZE];
int8_t* LPC_output_port;


void print_input_values(void) {
    int z;
    printf("Current data at input: [ ");
    for (z=0; z<SIZE; z++) {
        int temp1 = RX_coded_input[z];
        printf("%d ", temp1);
    }
    printf("]\n\n");
}

void write_random_inputs(Decoder * module) {

    int z;
    for (z=0; z<SIZE; z++) {
        int8_t temp = (rand() % input_range) - (input_range/2); // Random generation of inputs
        RX_coded_input[z] = temp;
        // printf("%d", temp);
    }

    int8_t rand_length = rand() % 2;
    if (rand_length == 1) {
        RX_coded_input[SIZE-rand_length] = (int8_t)0;
    }

    printf("Wrote random values at input !!!\n\n");
    print_input_values();
    module->dec(RX_coded_input);
}

void print_output_values(Decoder * module) {
    LPC_output_port = module->read();
    
    int z;
    printf("Data at output: [ ");
    for (z=0; z<SIZE; z++) {
        char temp = LPC_output_port[z];
        printf("%d ", temp);
    }
    printf("]\n\n\n\n");
}


int sc_main(int argc, char* argv[]) {

    Decoder uut("uut");

    sc_trace_file *pTraceFile;
    pTraceFile = sc_create_vcd_trace_file( "encoder_testbench" );
    pTraceFile->set_time_unit(1, SC_NS);

    // Dump the desired signals
    sc_trace(pTraceFile, RX_coded_input, "RX_coded_input");
    sc_trace(pTraceFile, LPC_output_port, "LPC_output_port");

    printf("\nStarting Testbench........\n\n");

    sc_start(0, SC_NS);

    int i;
    for (i=0; i<20; i++){
        cout << "@" << sc_time_stamp()<< endl;

        write_random_inputs(&uut);

        sc_start(10, SC_NS);

        print_output_values(&uut);
    }

    sc_stop();

    printf("\n\nTestbench Ended........\n\n");

    return 0;
}