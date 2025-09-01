import csv
import matplotlib.pyplot as plt
import sys

# Usage: python3 plot_speedup.py <csv_file> <title>
if len(sys.argv) != 3:
    print("Usage: python3 plot_speedup.py <csv_file> <title>")
    sys.exit(1)

csv_file = sys.argv[1]
title = sys.argv[2]

# Read CSV
procs = []
times = []

with open(csv_file, 'r') as f:
    reader = csv.DictReader(f)
    for row in reader:
        procs.append(int(row[list(row.keys())[0]]))
        times.append(float(row[list(row.keys())[1]]))

# Sort by processors
procs, times = zip(*sorted(zip(procs, times)))

# Compute speedup
t1 = times[0]  # time with 1 processor
speedup = [t1 / t for t in times]

# Plot Time vs Processors
plt.figure()
plt.plot(procs, times, marker='o', linestyle='-', color='blue')
plt.xlabel('Number of Processors')
plt.ylabel('Time (s)')
plt.title(f'{title} - Time vs Processors')
plt.grid(True)
plt.savefig(f'{title.replace(" ", "_").lower()}_time.png', dpi=150)

# Plot Speedup
plt.figure()
plt.plot(procs, speedup, marker='o', linestyle='-', color='green', label='Observed')
plt.plot(procs, procs, linestyle='--', color='red', label='Ideal')
plt.xlabel('Number of Processors')
plt.ylabel('Speedup')
plt.title(f'{title} - Speedup')
plt.legend()
plt.grid(True)
plt.savefig(f'{title.replace(" ", "_").lower()}_speedup.png', dpi=150)

print(f"Plots saved: {title.replace(' ', '_').lower()}_time.png and _speedup.png")
