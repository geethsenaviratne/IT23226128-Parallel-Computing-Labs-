import matplotlib.pyplot as plt

# ---- Your recorded data ----
processors = [1, 2, 3, 4]
time_sum = [0.000001, 0.000142, 0.000012, 0.000011] 
time_pi  = [0.227177, 0.162901, 0.078811, 0.058368] 

# ---- Calculate speedups ----
speedup_sum = [time_sum[0] / t for t in time_sum]
speedup_pi  = [time_pi[0] / t for t in time_pi]

# ---- Time vs Processors ----
plt.figure(figsize=(8,5))
plt.plot(processors, time_sum, 'o-', label='Sum')
plt.plot(processors, time_pi, 'o-', label='Pi (Monte Carlo)')
plt.title('Time vs Number of Processes')
plt.xlabel('Number of Processes (MPI ranks)')
plt.ylabel('Time (seconds)')
plt.grid(True)
plt.legend()
plt.savefig('time_vs_procs.png', dpi=150)
plt.show()

# ---- Speedup vs Processors ----
plt.figure(figsize=(8,5))
plt.plot(processors, speedup_sum, 'o-', label='Sum')
plt.plot(processors, speedup_pi, 'o-', label='Pi (Monte Carlo)')
plt.plot(processors, processors, '--', label='Ideal Speedup')
plt.title('Speedup vs Number of Processes')
plt.xlabel('Number of Processes (MPI ranks)')
plt.ylabel('Speedup (T1 / Tp)')
plt.grid(True)
plt.legend()
plt.savefig('speedup_vs_procs.png', dpi=150)
plt.show()

