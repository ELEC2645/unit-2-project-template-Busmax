#ifndef FUNCS_H
#define FUNCS_H

void resistor_decoder(void);
void circuit_analyser(void);
void signal_statistics(void);
void rc_filter_calc(void);
void calc_parallel_resistors(void); 
void generate_waveform_file(void); 

// Helper functions
float get_float_input(const char* prompt);
int get_int_input(const char* prompt);

#endif