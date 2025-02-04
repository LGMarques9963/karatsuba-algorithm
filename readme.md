# Karatsuba Binary Multiplication

## Description
This project was developed for the "Projeto e Otimização de Algoritmos" (Algorithm Design and Optimization) course. The goal is to implement the **Karatsuba algorithm** for multiplying arbitrarily large binary integers. Unlike conventional multiplication, this algorithm reduces the number of required operations using a divide-and-conquer approach.

## Features
- Implements **Karatsuba's fast multiplication** method for binary numbers.
- Works entirely in **binary representation** (no base-10 operations involved).
- Reads input numbers from **command-line arguments**.
- Includes a Python script (`test.py`) to verify correctness and measure performance.
- Supports test case input from `zz.txt`.

## Files in This Repository
- `main.c` - C implementation of the Karatsuba algorithm.
- `test.py` - Python script to validate results and benchmark performance.
- `zz.txt` - Test cases containing binary numbers.

## Installation & Compilation
### Requirements
- A **C compiler** (e.g., `gcc` on Linux/macOS, `MinGW` on Windows)
- Python (for optional testing script)

### Compilation
Compile the C program using:
```sh
gcc -o karatsuba main.c -Wall
```

## Usage
Run the compiled executable by passing two binary numbers as arguments:
```sh
./karatsuba 1101 1011
```
Example output:
```
Product: 10011111
```

Alternatively, you can use the Python testing script to compare the results of the C implementation with Python's native integer multiplication:
```sh
python test.py
```

## Testing
The `test.py` script:
1. Reads test cases from `zz.txt`.
2. Calls the C implementation with each test case.
3. Performs a Python-based integer multiplication.
4. Compares and verifies correctness.
5. Generates large random binary numbers for performance benchmarking.

## Technologies Used
- **C** for algorithm implementation.
- **Python** for validation and benchmarking.
- **Karatsuba algorithm** for efficient binary multiplication.

## Future Improvements
- Extend support for multi-threading to further speed up execution.

## License
This project is for educational purposes and does not include a specific license.

## Author
Developed as part of a university project for the "Projeto e Otimização de Algoritmos" course.


