
# 8-bit Pipelined MIPS Processor

This repository contains an 8-bit MIPS (Microprocessor without Interlocked Pipelined Stages) processor designed in **Logisim**, supporting both pipelined and non-pipelined architectures. The project includes a custom assembler to convert MIPS assembly code into binary files for MIPS instruction ROM. An extended version of the processor features I/O peripheral support, along with a playable **Snake Game** implemented in MIPS assembly.

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

### MIPS Instruction Set

| Instruction    | Format    | Example                             | Description                                                    |
|----------------|-----------|-------------------------------------|----------------------------------------------------------------|
| `addi`         | I         | `addi dest_reg, src_reg, imm`       | Add immediate value `imm` to `src_reg`, store in `dest_reg` |
| `sub`          | R         | `sub dest_reg, src_reg1, src_reg2`  | Subtract `src_reg2` from `src_reg1`, store result in `dest_reg` |
| `srl`          | R         | `srl dest_reg, src_reg1, src_reg2`  | Shift `src_reg` right by `src_reg2` bits, store result in `dest_reg` |
| `andi`         | I         | `andi dest_reg, src_reg, imm`       | Perform bitwise AND between `src_reg` and `imm`, store in `dest_reg` |
| `ori`          | I         | `ori dest_reg, src_reg, imm`        | Perform bitwise OR between `src_reg` and `imm`, store in `dest_reg` |
| `nor`          | R         | `nor dest_reg, src_reg1, src_reg2`  | Perform bitwise NOR between `src_reg1` and `src_reg2`, store in `dest_reg` |
| `bneq`         | I         | `bneq src_reg1, src_reg2, label`    | Branch if `src_reg1` is not equal to `src_reg2`, to `label` |
| `beq`          | I         | `beq src_reg1, src_reg2, label`     | Branch if `src_reg1` is equal to `src_reg2`, to `label`  |
| `sw`           | I         | `sw src_reg, offset(base_reg)`      | Store word from `src_reg` to memory at address `base_reg + offset` |
| `subi`         | I         | `subi dest_reg, src_reg, imm`       | Subtract immediate value `imm` from `src_reg`, store in `dest_reg` |
| `addi`         | I         | `addi dest_reg, src_reg, imm`       | Add immediate value `imm` to `src_reg`, store in `dest_reg` |
| `sll`          | R         | `sll dest_reg, src_reg, src_reg2`   | Shift `src_reg` left by `src_reg2` bits, store result in `dest_reg` |
| `add`          | R         | `add dest_reg, src_reg1, src_reg2`  | Add `src_reg1` and `src_reg2`, store result in `dest_reg` |
| `lw`           | I         | `lw dest_reg, offset(base_reg)`     | Load word from memory at address `base_reg + offset` into `dest_reg` |
| `or`           | R         | `or dest_reg, src_reg1, src_reg2`   | Perform bitwise OR between `src_reg1` and `src_reg2`, store in `dest_reg` |
| `j`            | J         | `j target`                          | Jump to address `target`                                 |


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
