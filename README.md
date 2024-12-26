# C Preprocessor for Array Operations

This project implements a preprocessor to process shortcuts for arithmetic operations on arrays in C. It reads a C file with preprocessor commands, parses the commands, and expands them into standard C code.

## Features
- **Declaration**: `$dec(array, n, type)` declares an array.
- **Input**: `$read(file, array)` reads array elements from a file.
- **Output**: `$print(array)` prints array elements.
- **Copy**: `$destination = $source` copies elements from one array to another.
- **Initialization**: `$array = x` initializes all elements of an array to a value.
- **Arithmetic Operations**: Supports `+`, `-`, `*`, and `/` operations on arrays.

## Files
- **`deneme.c`**: Sample C file with preprocessor commands.
- **`main.c`**: The main program that processes the preprocessor commands.
- **`result.c`**: The expanded C code after processing.

## How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/C-Preprocessor-Array-Operations.git
   cd C-Preprocessor-Array-Operations
   ```
2. Compile the program:
   ```bash
   gcc main.c -o preprocessor
   ```
3. Run the preprocessor:
   ```bash
   ./preprocessor
   ```
4. Check the **`result.c`** file for the expanded C code.

## License
This project is open-source and available under the MIT License.
