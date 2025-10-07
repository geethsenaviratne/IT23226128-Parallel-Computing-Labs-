#!/usr/bin/env python3
import random

print("Generating 10,000 random numbers...")
with open('numbers.csv', 'w') as f:
    numbers = [str(random.uniform(0, 100)) for _ in range(10000)]
    f.write(','.join(numbers))

print("Successfully created numbers.csv")
with open('numbers.csv', 'r') as f:
    data = f.read().strip().split(',')
    actual_sum = sum(float(x) for x in data)
    print(f"Expected sum: {actual_sum:.2f}")
