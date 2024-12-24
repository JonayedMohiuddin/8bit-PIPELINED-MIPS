
# 8-bit Pipelined MIPS Processor

This repository contains an 8-bit MIPS (Microprocessor without Interlocked Pipelined Stages) processor designed in **Logisim**, supporting both pipelined and non-pipelined architectures. The project includes a custom assembler to convert MIPS assembly code into binary files for MIPS instruction ROM. An extended version of the processor features I/O peripheral support. Also some classical game is implemented in it like: Snake, Tetris.

---

## Demos 

### Classical Snake Game 

[Assembly code of the game](ASSEMBLY/SNAKE_GAME.mips)

<img src="https://github.com/JonayedMohiuddin/8bit-PIPELINED-MIPS/blob/main/IMAGES/SNAKE_GAME_DEMO_MIPS.gif" width="500" height="auto">

<!-- USE IF GITHUB STOPS SHOWING GIF FROM REPO
![SnakeGame](https://media.giphy.com/media/VleEIiyLuSroiPZBTy/giphy.gif)
-->

### Classical Tetris Game

[Assembly code of the game](ASSEMBLY/TETRIS_GAME.mips)

***Will add animation soon***

### Hello World with Counter

[Assembly of Hello World](ASSEMBLY/HELLO_WORLD.mips)

<img src="https://github.com/JonayedMohiuddin/8bit-PIPELINED-MIPS/blob/main/IMAGES/HELLO_WORLD_DEMO_MIPS.gif" width="500" height="auto">

<!-- USE IF GITHUB STOPS SHOWING GIF FROM REPO
![HelloWorld](https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExeDlzbnBrMmlzMjF5YXFheWo1MGN2NDR5OTNmdWxwaWt6NGgwYXMzNCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/qPP3y7IH6vsYHA1Kxe/giphy.gif)
-->

### Random Matrix Display Demo 

[Assembly of Random Matrix](ASSEMBLY/RANDOM_MATRIX.mips)

<img src="https://github.com/JonayedMohiuddin/8bit-PIPELINED-MIPS/blob/main/IMAGES/RANDOM_MATRIX_DISPLAY_DEMO_MIPS.gif" width="500" height="auto">

<!-- USE IF GITHUB STOPS SHOWING GIF FROM REPO
![RandomMatrix](https://media.giphy.com/media/NqDBS3IC6WY3EeLVCu/giphy.gif)
-->

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

### Instruction Set Usages

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
| 6 - 12  | Unused (You can add yours)       |
| 13      | Signed Decimal Output (7-Segment Display) |
| 14      | Debug Output                     |
| 15      | Random Input                     |

*How to use I/O peripherals:*

To output data of `$t0` to a peripheral at port 1 use `lw $t0, 1($io)`

To get input in `$t0` from a peripheral at port 4 use `sw $t0, 4($io)`

---



## How to Use

### Assembler


1. **Compile using Assembler:**
   
   To convert `.mips` assembly code to binary `.txt` files for Logisim first open the Assembler.cpp in your favourite code editos (like vscode or codeblocks). Then change the filename variable in code. 
   Run the assembler and it should generate a file in ./binary/ folder in the directory. 

3. **Load the Binary in Logisim:**
   
   Open logisim and load mips. In intruction or IF (if pipelined) and right click on the rom and click on Load Image and
   then select the .txt binary file you just compiled.
   
   **Or**
   
   Just run the Run_MIPS.bat batch file and select one of the four options shown (1/2/3/4). If logisim shows "The required library file 'ALU.jar' is missing. Please select the file from the following dialog." 
   error just select the ALU.jar from base directory.

---

### Snake Game
This repository includes a playable **Snake Game** written in MIPS assembly. To play:

1. Assemble `SNAKE_GAME.mips` using the assembler.
2. Load the generated binary file into the **Instruction ROM**.
3. Start simulation and set tick speed to 4.1 kHz. Enable tick and enjoy.

---

### Major Limitations

1. Only 8 bit instruction memory allows 256 lines of instruction so cannot write large complex programs.
2. Lack of the 'jal' instruction makes life so much harder. Without jal cannot use any procedure calling as usage of jump forces to return to the same spot. Defeating the advantage of using a procedure.
3. Slow simulation of logisim makes it boring (yes logisim's 4.1kHz is slow)

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

---

## Acknowledgments
Special thanks to the course instructors for their guidance and support in building this project.
