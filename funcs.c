#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // Requires -lm flag for sqrt and pow functions
#include "funcs.h"


// Helper function to safely get a float from the user
float get_float_input(const char* prompt) {
    float value;
    char buffer[100];
    int valid = 0;
    
   
    while (!valid) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            
            buffer[strcspn(buffer, "\n")] = 0;
            
            // Check if input is a valid float
            if (sscanf(buffer, "%f", &value) == 1) {
                valid = 1;
            } else {
                printf("Error: Invalid input. Please enter a number.\n");
            }
        }
    }
    return value;
}

// Helper function to safely get an integer from the user
int get_int_input(const char* prompt) {
    int value;
    char buffer[100];
    int valid = 0;
    
    while (!valid) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;
            
            if (sscanf(buffer, "%d", &value) == 1) {
                valid = 1;
            } else {
                printf("Error: Invalid input. Please enter an integer.\n");
            }
        }
    }
    return value;
}

// ------------------------------------------
// Menu Feature Functions
// ------------------------------------------

// 1. Resistor Colour Code Decoder
void resistor_decoder(void) {
    printf("\n--- Resistor Colour Code Decoder ---\n");
    printf("Codes: 0:Black, 1:Brown, 2:Red, 3:Orange, 4:Yellow, \n");
    printf("       5:Green, 6:Blue, 7:Violet, 8:Grey, 9:White\n");

    int band1 = get_int_input("Enter Band 1 (0-9): ");
    int band2 = get_int_input("Enter Band 2 (0-9): ");
    int multiplier = get_int_input("Enter Multiplier (0-9): ");

    // Check if inputs are within valid range for colour codes
    if (band1 < 0 || band1 > 9 || band2 < 0 || band2 > 9 || multiplier < 0 || multiplier > 9) {
        printf("Error: Invalid colour code entered. Values must be 0-9.\n");
        return;
    }

    // Formula: (Band1 * 10 + Band2) * 10^Multiplier
    double resistance = (band1 * 10 + band2) * pow(10, multiplier);

    // Print result with unit scaling for better readability
    if (resistance >= 1000000) {
        printf(">> Resistance: %.2f M Ohms\n", resistance / 1000000.0);
    } else if (resistance >= 1000) {
        printf(">> Resistance: %.2f k Ohms\n", resistance / 1000.0);
    } else {
        printf(">> Resistance: %.0f Ohms\n", resistance);
    }
}

// 2. Basic Circuit Analyser (Ohm's Law)

void circuit_analyser(void) {
    printf("\n--- Basic Circuit Analyser (Ohm's Law) ---\n");
    printf("1. Calculate Voltage (V)\n");
    printf("2. Calculate Current (I)\n");
    printf("3. Calculate Resistance (R)\n");
    
    int choice = get_int_input("Select calculation (1-3): ");

    if (choice == 1) {
        // Calculate Voltage: V = I * R
        float i = get_float_input("Current (A): ");
        float r = get_float_input("Resistance (Ohms): ");
        printf(">> Voltage = %.2f V\n", i * r);
        
    } else if (choice == 2) {
        // Calculate Current: I = V / R
        float v = get_float_input("Voltage (V): ");
        float r = get_float_input("Resistance (Ohms): ");
        
        // Prevent division by zero
        if (r == 0) {
            printf("Error: Resistance cannot be zero.\n");
        } else {
            printf(">> Current = %.2f A\n", v / r);
        }
        
    } else if (choice == 3) {
        // Calculate Resistance: R = V / I
        float v = get_float_input("Voltage (V): ");
        float i = get_float_input("Current (A): ");
        
        if (i == 0) {
            printf("Error: Current cannot be zero.\n");
        } else {
            printf(">> Resistance = %.2f Ohms\n", v / i);
        }
        
    } else {
        printf("Invalid selection.\n");
    }
}

// 3. Signal Statistics Tool

void signal_statistics(void) {
    printf("\n--- Signal Statistics (Mean & RMS) ---\n");
    
    int n = get_int_input("Enter number of samples (max 100): ");
    
    // Validate size to prevent array overflow
    if (n <= 0 || n > 100) { 
        printf("Error: Please enter a size between 1 and 100.\n");
        return;
    }

    // Using a static array for simplicity as taught in early units
    float samples[100]; 
    float sum = 0.0;
    float sq_sum = 0.0;

    for (int i = 0; i < n; i++) {
        char prompt[32];
        sprintf(prompt, "Sample %d: ", i + 1); // Create a dynamic prompt string
        samples[i] = get_float_input(prompt);
        
        sum += samples[i];
        sq_sum += (samples[i] * samples[i]);
    }

    // Calculate statistics
    float mean = sum / n;
    float rms = sqrt(sq_sum / n); 

    printf(">> Mean Value: %.4f\n", mean);
    printf(">> RMS Value:  %.4f\n", rms);
}

// 4. RC Low-Pass Filter Calculator

void rc_filter_calc(void) {
    printf("\n--- RC Low-Pass Filter Calculator ---\n");
    
    float r = get_float_input("Resistance (Ohms): ");
    float c = get_float_input("Capacitance (Farads): "); 

    // Physical check: components cannot be negative
    if (r <= 0 || c <= 0) {
        printf("Error: Component values must be positive.\n");
        return;
    }

    float pi = 3.14159265;
    float fc = 1.0 / (2.0 * pi * r * c);
    
    printf(">> Cut-off Frequency: %.2f Hz\n", fc);
}

// 5. Parallel Resistor Calculator

void calc_parallel_resistors(void) {
    printf("\n--- Parallel Resistor Calculator ---\n");
    
    int n = get_int_input("How many resistors are in parallel? ");
    
    if (n <= 1) {
        printf("Error: Need at least 2 resistors for parallel calculation.\n");
        return;
    }

    // Allocate memory dynamically for 'n' floats
    float* resistors = (float*)malloc(n * sizeof(float));
    
    //Check if memory allocation was successful
    if (resistors == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // Input loop for resistor values
    for (int i = 0; i < n; i++) {
        char prompt[32];
        sprintf(prompt, "Enter Resistor %d value (Ohms): ", i + 1);
        resistors[i] = get_float_input(prompt);
    }

    double inverse_sum = 0.0;
    int error = 0;

    for (int i = 0; i < n; i++) {
        if (resistors[i] <= 0) {
            printf("Error: Resistor %d has invalid value (must be > 0).\n", i + 1);
            error = 1;
            break; 
        }
        inverse_sum += (1.0 / resistors[i]);
    }

    if (!error) {
        double r_total = 1.0 / inverse_sum;
        printf(">> Total Parallel Resistance: %.2f Ohms\n", r_total);
    }

    // Free the allocated memory to prevent memory leaks
    free(resistors);
    printf("(Memory freed)\n");
}

// 6. Waveform Generator

void generate_waveform_file(void) {
    printf("\n--- Sine Wave Generator (to CSV) ---\n");
    
    float freq = get_float_input("Enter Frequency (Hz): ");
    float amp = get_float_input("Enter Amplitude (V): ");
    float duration = get_float_input("Enter Duration (s): ");
    
    // Fixed sample rate for simplicity
    int sample_rate = 1000; 
    int total_samples = (int)(duration * sample_rate);

    // Open file for writing 
    FILE *fp = fopen("waveform.csv", "w");
    
    if (fp == NULL) {
        printf("Error: Could not create output file.\n");
        return;
    }

    // Write CSV Header
    fprintf(fp, "Time(s),Voltage(V)\n");

    // Generate data and write to file
    float pi = 3.14159265;
    for (int i = 0; i < total_samples; i++) {
        double t = (double)i / sample_rate;
        double v = amp * sin(2.0 * pi * freq * t);
        
        fprintf(fp, "%.4f,%.4f\n", t, v);
    }

    // Close file to save changes
    fclose(fp);
    
    printf(">> Success! Data saved to 'waveform.csv'.\n");
}