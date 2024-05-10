---

## Weekend Counter

This program calculates the number of weekends between two given dates.

### Description

The program takes input from a file (`in.txt`), consisting of two dates formatted as day, month, and year. It then calculates the number of weekends between these two dates and writes the result to an output file (`out.txt`). 

### How to Use

1. Ensure you have `in.txt` file with the input dates formatted correctly.
2. Compile the program using a C compiler.
3. Run the executable. The program will read the input dates, calculate the number of weekends between them, and write the result to `out.txt`.

### Input Format

The input file (`in.txt`) should contain two lines, each representing a date in the format: day month year. For example:
```
1 1 2024
31 12 2024
```

### Output Format

The output file (`out.txt`) will contain a single number representing the number of weekends between the two input dates.

### Notes

- The program considers Saturday and Sunday as weekends.
- Leap years are taken into account when calculating the number of days in February.

---
