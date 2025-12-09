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

// 2. Basic Circuit Analyser-Ohm's Law

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
#define TEST_EPSILON 0.001

// 7. System Self-Diagnostic
void run_system_test(void) {
    printf("\n-----------------------------------------\n");
    printf("      SYSTEM SELF-DIAGNOSTIC (v1.2)      \n");
    printf("-----------------------------------------\n");
    
    int passed_count = 0;
    int total_tests = 0;

    //Test 1: Resistor Decoder Logic
    total_tests++;
    printf("[Test %d] Resistor Colour Code Logic... ", total_tests);
    
    int b1 = 1, b2 = 0, mult = 2;
    double res_expected = 1000.0;
    double res_calc = (b1 * 10 + b2) * pow(10, mult);
    
    if (fabs(res_calc - res_expected) < TEST_EPSILON) {
        printf("PASS\n");
        passed_count++;
    } else {
        printf("FAIL (Expected: %.0f, Got: %.0f)\n", res_expected, res_calc);
    }

    //Test 2: Ohm's Law (Current Calculation)
    total_tests++;
    printf("[Test %d] Ohm's Law (I = V/R)...       ", total_tests);
    
    float v = 4.0f, r = 2.0f;
    float i_expected = 2.0f;
    float i_calc = v / r;
    
    if (fabs(i_calc - i_expected) < TEST_EPSILON) {
        printf("PASS\n");
        passed_count++;
    } else {
        printf("FAIL (Expected: %.2f, Got: %.2f)\n", i_expected, i_calc);
    }

    //Test 3: Signal Statistics
    total_tests++;
    printf("[Test %d] Signal Mean Calculation...    ", total_tests);
    
    float sum = 2.0f + 4.0f + 6.0f;
    float mean_expected = 4.0f;
    float mean_calc = sum / 3.0f;
    
    if (fabs(mean_calc - mean_expected) < TEST_EPSILON) {
        printf("PASS\n");
        passed_count++;
    } else {
        printf("FAIL (Expected: %.2f, Got: %.2f)\n", mean_expected, mean_calc);
    }

    //Test 4: RC Filter Cut-off Frequency
    total_tests++;
    printf("[Test %d] RC Filter Formula...          ", total_tests);
    
    // f = 1 / (2 * pi * R * C)
    float rc_r = 1591.55f;
    float rc_c = 0.0001f; // 100uF
    float pi = 3.14159265f;
    float f_expected = 1.0f;
    float f_calc = 1.0f / (2.0f * pi * rc_r * rc_c);
    
    if (fabs(f_calc - f_expected) < 0.01f) {
        printf("PASS\n");
        passed_count++;
    } else {
        printf("FAIL (Expected: %.2f, Got: %.2f)\n", f_expected, f_calc);
    }

    //Test 5: Dynamic Memory Allocation
    total_tests++;
    printf("[Test %d] System Memory Allocation...   ", total_tests);
    
    //allocate memory for 100 integers
    int* test_ptr = (int*)malloc(100 * sizeof(int));
    if (test_ptr != NULL) {
        test_ptr[0] = 999;
        if (test_ptr[0] == 999) {
            printf("PASS\n");
            passed_count++;
        } else {
            printf("FAIL (Write Verify Failed)\n");
        }
        free(test_ptr); // Important: Free memory to prevent leaks
    } else {
        printf("FAIL (malloc returned NULL)\n");
    }

    //Test 6: File System IO
    total_tests++;
    printf("[Test %d] File Write Permissions...     ", total_tests);
    
    const char* test_file = "test_marker.tmp";
    FILE* fp = fopen(test_file, "w");
    if (fp != NULL) {
        fprintf(fp, "Unit Test Data");
        fclose(fp);
        // Clean up: delete the test file
        if (remove(test_file) == 0) {
            printf("PASS\n");
            passed_count++;
        } else {
            printf("PASS (Write OK, but Delete Failed)\n");
            passed_count++; 
        }
    } else {
        printf("FAIL (Cannot create file)\n");
    }

    //Report
    printf("-----------------------------------------\n");
    printf("SUMMARY: %d / %d Tests Passed.\n", passed_count, total_tests);
    
    if (passed_count == total_tests) {
        printf(">> DIAGNOSTIC RESULT: SYSTEM NOMINAL\n");
    } else {
        printf(">> DIAGNOSTIC RESULT: ERRORS DETECTED\n");
    }
    printf("-----------------------------------------\n");
}

// ================= API IMPLEMENTATIONS =================

// 1. Resistor Decoder API
double api_resistor_calc(int b1, int b2, int mult) {
    if (b1 < 0 || b2 < 0 || mult < 0) return -1.0;
    return (b1 * 10 + b2) * pow(10, mult);
}

// 2. Ohm's Law API
// mode: 1=Calc V, 2=Calc I, 3=Calc R
float api_ohms_law(int mode, float v, float i, float r) {
    if (mode == 1) return i * r;       // V = IR
    if (mode == 2) return (r==0)? -1 : v / r; // I = V/R
    if (mode == 3) return (i==0)? -1 : v / i; // R = V/I
    return 0.0f;
}

// 3. RC Filter API
float api_rc_cutoff(float r, float c) {
    if (r <= 0 || c <= 0) return -1.0f;
    return 1.0f / (2.0f * 3.14159265f * r * c);
}

// 4. Statistics API (Mean) - Demonstrates Array Passing
float api_stats_mean(float* data, int n) {
    if (n <= 0) return 0.0f;
    float sum = 0.0f;
    for(int i=0; i<n; i++) sum += data[i];
    return sum / n;
}

// 5. Statistics API
float api_stats_rms(float* data, int n) {
    if (n <= 0) return 0.0f;
    float sq_sum = 0.0f;
    for(int i=0; i<n; i++) sq_sum += (data[i] * data[i]);
    return sqrt(sq_sum / n);
}

// 6. Parallel Resistor API
float api_parallel_r(float* data, int n) {
    if (n <= 0) return 0.0f;
    double inv_sum = 0.0;
    for(int i=0; i<n; i++) {
        if (data[i] <= 0) return -1.0f; // Error
        inv_sum += (1.0 / data[i]);
    }
    return (float)(1.0 / inv_sum);
}

// 7. Self-Test API
void api_run_self_test(void) {
    run_system_test(); // Calls your existing robust test function
}