
# 8-bit Pipelined MIPS Processor

This repository contains an 8-bit MIPS processor designed in **Logisim**, supporting both pipelined and non-pipelined architectures. The project includes a custom assembler to convert MIPS assembly code into binary files for Logisim's instruction ROM. An extended version of the processor features I/O peripheral support, along with a playable **Snake Game** implemented in MIPS assembly.

---

## Features

### Instruction Set
The MIPS processor supports the following instructions:

| Opcode | Binary | Category    | Instruction | Format |
|--------|--------|-------------|-------------|--------|
| 0      | 0000   | Arithmetic  | `sub`       | R      |
| 1      | 0001   | Logic       | `srl`       | R      |
| 2      | 0010   | Logic       | `andi`      | I      |
| 3      | 0011   | Logic       | `ori`       | I      |
| 4      | 0100   | Logic       | `nor`       | R      |
| 5      | 0101   | Control     | `bneq`      | I      |
| 6      | 0110   | Logic       | `and`       | R      |
| 7      | 0111   | Control     | `beq`       | I      |
| 8      | 1000   | Memory      | `sw`        | I      |
| 9      | 1001   | Arithmetic  | `subi`      | I      |
| 10     | 1010   | Arithmetic  | `addi`      | I      |
| 11     | 1011   | Logic       | `sll`       | R      |
| 12     | 1100   | Arithmetic  | `add`       | R      |
| 13     | 1101   | Memory      | `lw`        | I      |
| 14     | 1110   | Logic       | `or`        | R      |
| 15     | 1111   | Control     | `j`         | J      |

---

### Extended I/O Functionality
The extended MIPS processor supports the following I/O peripherals:

| IO Port | Functionality                     |
|---------|-----------------------------------|
| 0       | X Enable + Data                  |
| 1       | Y Enable + Data                  |
| 2       | Update Flag                      |
| 3       | Flush Flag                       |
| 4       | Keyboard Input                   |
| 5       | Text Output (TTY)                |
| 13      | Signed Decimal Output (7-Segment Display) |
| 14      | Debug Output                     |
| 15      | Random Input                     |

---

## How to Use

### Assembler
To convert `.mips` assembly code to binary `.txt` files for Logisim:

1. **Compile the Assembler:**
   ```bash
   g++ -o assembler Assembler.cpp
   ```
   For the extended MIPS processor, use `Assember_Extended.cpp`:
   ```bash
   g++ -o assembler_extended Assember_Extended.cpp
   ```

2. **Run the Assembler:**
   ```bash
   ./assembler input.mips output.txt
   ```
   Replace `assembler` with `assembler_extended` for the extended version.

3. **Load the Binary in Logisim:**
   Open Logisim, click on the **Instruction ROM**, and use the "Load Image" option to load the `.txt` file.

---

### Logisim Simulation
1. **Open the Circuit File:**
   - For normal MIPS: Use `MIPS_Pipelined.circ` or `MIPS_NonPipelined.circ`.
   - For extended MIPS: Use `MIPS_Pipelined_Extended.circ` or `MIPS_NonPipelined_Extended.circ`.

2. **Load the Binary:**
   Load the assembled binary file into the **Instruction ROM**.

3. **Run the Simulation:**
   Use Logisim's controls to step through or run the simulation.

---

### Snake Game
This repository includes a playable **Snake Game** written in MIPS assembly. To play:

1. Assemble `SNAKE_GAME.mips` using the assembler.
2. Load the generated binary file into the **Instruction ROM**.
3. Connect the required I/O peripherals (e.g., keyboard and TTY) in Logisim.
4. Run the simulation to start playing.

---

## Non-Pipelined Version
Non-pipelined versions of the MIPS processor are included for both normal and extended architectures, making debugging and testing more convenient.

---

## Test Cases
Various test cases are included in the repository, such as:

- **Basic Pipeline Tests**: Test the pipeline functionality.
- **Data Hazard Tests**: Verify handling of data hazards.
- **Matrix Operations**: Perform matrix-related computations.
- **Snake Game**: A playable implementation in MIPS assembly.
- **Provided and Custom Test Cases**: For validation and demonstration.

---

## Contributing
Contributions are welcome! Feel free to submit issues or pull requests for improvements or bug fixes.

---

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

---

## Acknowledgments
Special thanks to the course instructors for their guidance and support in building this project.
