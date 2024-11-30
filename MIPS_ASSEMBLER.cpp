#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <iomanip> // For formatting hexadecimal output

using namespace std;

// Map for opcodes
unordered_map<string, string> opcodeMap = {
    {"sub", "0000"}, {"srl", "0001"}, {"andi", "0010"}, {"ori", "0011"}, {"nor", "0100"}, {"bneq", "0101"}, {"and", "0110"}, {"beq", "0111"}, {"sw", "1000"}, {"subi", "1001"}, {"addi", "1010"}, {"sll", "1011"}, {"add", "1100"}, {"lw", "1101"}, {"or", "1110"}, {"j", "1111"}};

// Map for registers
unordered_map<string, string> registerMap = {
    {"$zero", "0000"}, {"$t0", "0101"}, {"$t1", "0100"}, {"$t2", "0011"}, {"$t3", "0010"}, {"$t4", "0001"}, {"$sp", "0110"}};

// Function to convert immediate/address values to binary
string toBinary(int value, int bits)
{
    return bitset<16>(value).to_string().substr(16 - bits, bits);
}

// Function to convert binary string to hexadecimal string
string binaryToHex(const string &binary)
{
    stringstream ss;
    unsigned long decimalValue = bitset<32>(binary).to_ulong(); // Convert binary to decimal
    ss << hex /* << uppercase */ << setw(binary.length() / 4) << setfill('0') << decimalValue; // Convert decimal to hex
    return ss.str();
}

// Function to parse and convert assembly instruction to binary
string convertToBinary(const string &line)
{
    stringstream ss(line);
    string instruction, rd, rs, rt, imm, jumpAddress, shiftAmt;
    ss >> instruction;

    // Identify instruction type based on opcode
    string opcode = opcodeMap[instruction];
    string binaryInstruction;

    if (instruction == "j")
    {
        // J-type: Opcode + Address
        ss >> jumpAddress;
        int address = stoi(jumpAddress);
        binaryInstruction = opcode + toBinary(address, 8) + "00000000";

        cerr << "JMP " << opcode << " " << toBinary(address, 8) << " " << "00000000" << endl;
    }
    else if (instruction == "sub" || instruction == "and" || instruction == "or" || 
             instruction == "nor" || instruction == "add") 
    {
        // NORMAL R TYPE
        // R-type: Opcode + rs + rt + rd + shift
        ss >> rd >> rs >> rt;
        binaryInstruction = opcode + registerMap[rs] + registerMap[rt] + registerMap[rd] + "0000";

        cerr << "ALU " << opcode << " " << registerMap[rs] << " " << registerMap[rt] << " " << registerMap[rd] << " " << "0000" << endl;
    }
    else if (instruction == "srl" || instruction == "sll")
    {
        // SHIFT R TYPE
        // R-type: Opcode + rs + rt + rd + shift
        ss >> rd >> rt >> shiftAmt;
        int shiftAmount = stoi(shiftAmt);
        // WHEN SHIFTING USE RS AS NUMBER , RT AS DESTINATION REGISTER , SHIFT AMOUNT AS SHIFT AMOUNT
        binaryInstruction = opcode + registerMap[rt] + registerMap[rd] + toBinary(shiftAmount, 8);

        cerr << "SHI " << opcode << " " << registerMap[rt] << " " << registerMap[rd] << " " << toBinary(shiftAmount, 8) << endl;
    }
    else if(instruction == "lw"   || instruction == "sw"   || 
            instruction == "addi" || instruction == "subi" || 
            instruction == "andi" || instruction == "ori")
    {
        // I-type: Opcode + rs + rt + Immediate
        ss >> rt >> rs >> imm;
        int immediate = stoi(imm);
        binaryInstruction = opcode + registerMap[rs] + registerMap[rt] + toBinary(immediate, 8);
    
        cerr << "IMM " << opcode << " " << registerMap[rs] << " " << registerMap[rt] << " " << toBinary(immediate, 8) << endl;
    }

    return binaryInstruction;
}


int main()
{
    string filename = "REGISTER_DEMO.txt";

    string inputFileName = "";
    inputFileName += "ASSEMBLY_";
    inputFileName += filename;

    string outputFilename = "";
    outputFilename += "BINARY_";
    outputFilename += filename;

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFilename);

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cerr << "Error opening file." << endl;
        return 1;
    }

    outputFile << "v2.0 raw" << endl; // Set output file format to raw

    string line;
    while (getline(inputFile, line))
    {
        if (line.empty() || line == "\n") continue;
        string binary = convertToBinary(line);
        string hexValue = binaryToHex(binary); // Convert binary to hexadecimal
        outputFile << hexValue << endl; // Save hexadecimal value to file
        // cerr << binary << endl; // Print binary value to console
    }

    inputFile.close();
    outputFile.close();

    cout << "Conversion complete. Check '" << outputFilename << "' for results in hexadecimal format." << endl;

    return 0;
}

/*

addi $t0 $zero 10
addi $t1 $zero 20
sw   $t0 $zero 0
sw   $t1 $zero 1 
lw   $t0 $zero 0
lw   $t1 $zero 1
add  $t0 $t1 $t2
sll  $t2 $t2 1
sw   $t2 $zero 2 
j    0

*/