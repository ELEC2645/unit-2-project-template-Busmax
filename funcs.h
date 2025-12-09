#ifndef FUNCS_H
#define FUNCS_H

void resistor_decoder(void);
void circuit_analyser(void);
void signal_statistics(void);
void rc_filter_calc(void);
void calc_parallel_resistors(void);
void generate_waveform_file(void);

// Self-Test 
void run_system_test(void); 

float get_float_input(const char* prompt);
int get_int_input(const char* prompt);

double api_resistor_calc(int b1, int b2, int mult);
float api_ohms_law(int mode, float v, float i, float r); 
float api_rc_cutoff(float r, float c);
float api_stats_mean(float* data, int n); 
float api_stats_rms(float* data, int n);  
float api_parallel_r(float* data, int n);
void api_run_self_test(void); 
#endif