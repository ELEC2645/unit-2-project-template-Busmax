import tkinter as tk
from tkinter import ttk, messagebox
import ctypes
import sys
import os
import matplotlib.pyplot as plt 
import numpy as np             


lib_name = "libeng.dll" if sys.platform == "win32" else "./libeng.so"

try:
    c_lib = ctypes.CDLL(os.path.abspath(lib_name))

    
    # Resistor
    c_lib.api_resistor_calc.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]
    c_lib.api_resistor_calc.restype = ctypes.c_double
    
    # Ohm's Law
    c_lib.api_ohms_law.argtypes = [ctypes.c_int, ctypes.c_float, ctypes.c_float, ctypes.c_float]
    c_lib.api_ohms_law.restype = ctypes.c_float
    
    # RC Filter
    c_lib.api_rc_cutoff.argtypes = [ctypes.c_float, ctypes.c_float]
    c_lib.api_rc_cutoff.restype = ctypes.c_float
    
    # Array Helpers (Statistics & Parallel R)

    FloatArrayType = ctypes.POINTER(ctypes.c_float)
    
    c_lib.api_stats_mean.argtypes = [FloatArrayType, ctypes.c_int]
    c_lib.api_stats_mean.restype = ctypes.c_float
    
    c_lib.api_stats_rms.argtypes = [FloatArrayType, ctypes.c_int]
    c_lib.api_stats_rms.restype = ctypes.c_float
    
    c_lib.api_parallel_r.argtypes = [FloatArrayType, ctypes.c_int]
    c_lib.api_parallel_r.restype = ctypes.c_float

except Exception as e:
    messagebox.showerror("Error", f"Library load failed: {e}\nDid you compile libeng.dll/.so?")
    sys.exit()


class EngApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Engineering Assistant Pro (C-Backend)")
        self.root.geometry("600x650")
        

        header = tk.Frame(root, bg="#003366", pady=10)
        header.pack(fill="x")
        tk.Label(header, text="Engineering Toolkit v7.0", font=("Helvetica", 18, "bold"), fg="white", bg="#03B11A").pack()
        tk.Label(header, text="Powered by C Logic Engine", font=("Arial", 10), fg="#cccccc", bg="#003366").pack()

  
        notebook = ttk.Notebook(root)
        notebook.pack(expand=True, fill="both", padx=10, pady=10)
        
   
        self.create_resistor_tab(notebook)
        self.create_ohm_tab(notebook)
        self.create_stats_tab(notebook) 
        self.create_rc_tab(notebook)
        self.create_parallel_tab(notebook)
        self.create_wave_tab(notebook)
        

        bottom_frame = tk.Frame(root, pady=10)
        bottom_frame.pack(fill="x")
        
        btn_check = tk.Button(bottom_frame, text="Run System Self-Diagnostic", command=self.run_self_check, bg="#a6ff00", width=25)
        btn_check.pack(side="left", padx=20)
        
        btn_exit = tk.Button(bottom_frame, text="Exit Application", command=root.quit, bg="#ff9666", width=20)
        btn_exit.pack(side="right", padx=20)

    def to_c_array(self, py_list):
        arr_type = ctypes.c_float * len(py_list)
        return arr_type(*py_list)

    def create_resistor_tab(self, nb):
        frame = ttk.Frame(nb); nb.add(frame, text="Resistor")
        
        tk.Label(frame, text="Band 1 (0-9):").pack(pady=5)
        b1 = tk.Entry(frame); b1.pack()
        tk.Label(frame, text="Band 2 (0-9):").pack(pady=5)
        b2 = tk.Entry(frame); b2.pack()
        tk.Label(frame, text="Multiplier (0-9):").pack(pady=5)
        mul = tk.Entry(frame); mul.pack()
        
        res_lbl = tk.Label(frame, text="Result: -", font=("Arial", 14, "bold"), fg="blue")
        
        def calc():
            try:
                val = c_lib.api_resistor_calc(int(b1.get()), int(b2.get()), int(mul.get()))
                res_lbl.config(text=f"{val:,.0f} Ω")
            except: res_lbl.config(text="Invalid Input")
            
        tk.Button(frame, text="Decode", command=calc).pack(pady=10)
        res_lbl.pack(pady=10)

    def create_ohm_tab(self, nb):
        frame = ttk.Frame(nb); nb.add(frame, text="Ohm's Law")
        
        mode_var = tk.IntVar(value=1)
        tk.Radiobutton(frame, text="Calc Voltage (V)", variable=mode_var, value=1).pack()
        tk.Radiobutton(frame, text="Calc Current (I)", variable=mode_var, value=2).pack()
        tk.Radiobutton(frame, text="Calc Resistance (R)", variable=mode_var, value=3).pack()
        
        tk.Label(frame, text="Value 1 (V/I/R):").pack()
        v1 = tk.Entry(frame); v1.pack()
        tk.Label(frame, text="Value 2 (V/I/R):").pack()
        v2 = tk.Entry(frame); v2.pack()
        
        res_lbl = tk.Label(frame, text="Result: -", font=("Arial", 14, "bold"), fg="blue")
        
        def calc():
            try:
              
                m = mode_var.get()
                val1 = float(v1.get())
                val2 = float(v2.get())
                
                result = 0.0
                if m == 1: result = c_lib.api_ohms_law(1, 0, val1, val2) # Calc V (pass I, R)
                if m == 2: result = c_lib.api_ohms_law(2, val1, 0, val2) # Calc I (pass V, R)
                if m == 3: result = c_lib.api_ohms_law(3, val1, val2, 0) # Calc R (pass V, I)
                
                res_lbl.config(text=f"Result: {result:.2f}")
            except: res_lbl.config(text="Input Error")
            
        tk.Button(frame, text="Calculate", command=calc).pack(pady=10)
        res_lbl.pack()


    def create_stats_tab(self, nb):
        frame = ttk.Frame(nb); nb.add(frame, text="Stats")
        
        tk.Label(frame, text="Enter numbers (comma separated):").pack(pady=5)
        entry = tk.Entry(frame, width=50); entry.pack()
        entry.insert(0, "1.5, 2.5, 3.5, 4.5")
        
        res_lbl = tk.Label(frame, text="Mean: - | RMS: -", font=("Arial", 12), fg="blue")
        
        def calc():
            try:
                nums = [float(x) for x in entry.get().split(',')]
                c_arr = self.to_c_array(nums) # Convert to C pointer
                
                # Call C functions
                mean = c_lib.api_stats_mean(c_arr, len(nums))
                rms = c_lib.api_stats_rms(c_arr, len(nums))
                
                res_lbl.config(text=f"Mean: {mean:.4f} | RMS: {rms:.4f}")
            except: res_lbl.config(text="Format Error")
            
        tk.Button(frame, text="Compute (via C Pointers)", command=calc).pack(pady=10)
        res_lbl.pack()


    def create_rc_tab(self, nb):
        frame = ttk.Frame(nb); nb.add(frame, text="RC Filter")
        tk.Label(frame, text="R (Ohms):").pack(); r_ent = tk.Entry(frame); r_ent.pack()
        tk.Label(frame, text="C (Farads):").pack(); c_ent = tk.Entry(frame); c_ent.pack()
        res_lbl = tk.Label(frame, text="- Hz", font=("Arial", 14), fg="blue")
        
        def calc():
            try:
                fc = c_lib.api_rc_cutoff(float(r_ent.get()), float(c_ent.get()))
                res_lbl.config(text=f"{fc:.2f} Hz")
            except: res_lbl.config(text="Error")
        tk.Button(frame, text="Calculate Cutoff", command=calc).pack(pady=10)
        res_lbl.pack()


    def create_parallel_tab(self, nb):
        frame = ttk.Frame(nb); nb.add(frame, text="Parallel R")
        tk.Label(frame, text="Resistors (comma separated):").pack(pady=5)
        entry = tk.Entry(frame, width=50); entry.pack()
        res_lbl = tk.Label(frame, text="Total R: -", font=("Arial", 14), fg="green")
        
        def calc():
            try:
                nums = [float(x) for x in entry.get().split(',')]
                c_arr = self.to_c_array(nums)
                
                total = c_lib.api_parallel_r(c_arr, len(nums))
                if total < 0: res_lbl.config(text="Invalid (Negative R)")
                else: res_lbl.config(text=f"Total: {total:.2f} Ω")
            except: res_lbl.config(text="Error")
            
        tk.Button(frame, text="Calc Parallel (via C)", command=calc).pack(pady=10)
        res_lbl.pack()


    def create_wave_tab(self, nb):
        frame = ttk.Frame(nb); nb.add(frame, text="Waveform")
        tk.Label(frame, text="Frequency (Hz):").pack(); f_ent = tk.Entry(frame); f_ent.pack()
        tk.Label(frame, text="Amplitude (V):").pack(); a_ent = tk.Entry(frame); a_ent.pack()
        
        def plot():
            try:
                f = float(f_ent.get())
                a = float(a_ent.get())
                t = np.linspace(0, 1, 1000)
                y = a * np.sin(2 * np.pi * f * t)
                
                plt.figure(figsize=(5,3))
                plt.plot(t, y)
                plt.title(f"Sine Wave {f}Hz")
                plt.xlabel("Time (s)"); plt.ylabel("Voltage (V)")
                plt.grid(True)
                plt.show()
            except: messagebox.showerror("Error", "Invalid plotting parameters")
            
        tk.Button(frame, text="Generate & Plot", command=plot, bg="#add8e6").pack(pady=20)

    def run_self_check(self):
        print("\n--- GUI Initiating C Self-Diagnostic ---")
        # Call C function, which prints to stdout (Console)
        c_lib.api_run_self_test()
        messagebox.showinfo("System Check", "Diagnostic routine executed.\nPlease check the CONSOLE/TERMINAL for the detailed report.")


if __name__ == "__main__":
    root = tk.Tk()
    app = EngApp(root)
    root.mainloop()