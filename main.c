#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

void print_menu(void) {
    printf("\n=========================================\n");
    printf("   ENGINEERING ASSISTANT TOOLKIT (v7.0)  \n");
    printf("=========================================\n");
    printf("1. Resistor Colour Code Decoder\n");
    printf("2. Circuit Analyser (Ohm's Law)\n");
    printf("3. Signal Statistics (Mean/RMS)\n");
    printf("4. RC Filter Calculator\n");
    printf("5. Parallel Resistor Calc (malloc)\n");
    printf("6. Waveform Generator (File I/O)\n");
    printf("7. System Self-Diagnostic\n"); // NEW
    printf("8. Exit\n");
    printf("-----------------------------------------\n");
}

int main(void) {
    int running = 1;
    int choice;
    char buffer[100];

    while (running) {
        print_menu();
        printf("Select an option: ");
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &choice) != 1) {
                printf("Invalid input.\n");
                continue;
            }
        } else {
            break;
        }

        switch (choice) {
            case 1: resistor_decoder();
             break;
            case 2: circuit_analyser();
             break;
            case 3: signal_statistics();
             break;
            case 4: rc_filter_calc();
             break;
            case 5: calc_parallel_resistors();
             break;
            case 6: generate_waveform_file();
             break;
            case 7: run_system_test();
             break;
            case 8: 
                printf("Exiting application. Goodbye QAQ\n");
                running = 0;
                break;
            default:
                printf("Invalid selection. Try 1-8.\n");
        }
    }
    return 0;
}