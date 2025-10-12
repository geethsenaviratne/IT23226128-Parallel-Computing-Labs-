import random

# Create a CSV file with 10,000 random numbers in vertical format
with open('numbers.csv', 'w') as f:
    for i in range(10000):
        f.write(f"{random.randint(1, 1000)}")
        if i < 9999:
            f.write("\n")

print("Created create_numbers.csv with 10,000 random numbers in vertical format")
print("Each number is on a separate line for easy viewing in Excel")
