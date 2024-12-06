#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <iomanip> 
#include <algorithm>

using namespace std;

// Map for opcodes
unordered_map<string, string> opcodeMap = {
    {"lw", "0000"}, {"nor", "0001"}, {"addi", "0010"}, {"bneq", "0011"}, {"beq", "0100"}, {"ori", "0101"}, {"andi", "0110"}, {"add", "0111"}, {"and", "1000"}, {"subi", "1001"}, {"sub", "1010"}, {"srl", "1011"}, {"sll", "1100"}, {"sw", "1101"}, {"or", "1110"}, {"j", "1111"}};

// Map for registers
unordered_map<string, string> registerMap = {
    {"$zero", "0000"}, {"$t1", "0001"}, {"$t2", "0010"}, {"$t3", "0011"}, {"$t4", "0100"}, {"$t0", "0101"}, {"$sp", "0110"}};

// Map for labels
unordered_map<string, int> labelMap;

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
    ss << hex << setw(binary.length() / 4) << setfill('0') << decimalValue; // Convert decimal to hex
    return ss.str();
}

// Function to remove all commas from a string
string removeCommas(const string &str)
{
    string result = str;
    result.erase(remove(result.begin(), result.end(), ','), result.end());
    return result;
}

// function to get the line number of labels
int updateLabels(const string &line, int lineNumber)
{
    string cleanLine = removeCommas(line);
    stringstream ss(cleanLine);
    string instruction;
    ss >> instruction;

    int val = 1;

    if (instruction[0] == '#'){
    }
    else if (instruction == "j"){
    }
    else if (instruction == "sub" || instruction == "and" || instruction == "or" || instruction == "nor" || instruction == "add"){
    }
    else if (instruction == "srl" || instruction == "sll"){
    }
    else if (instruction == "lw" || instruction == "sw"){
    }
    else if (instruction == "addi" || instruction == "subi" || instruction == "andi" || instruction == "ori"){
    }
    else if (instruction == "beq" || instruction == "bneq"){
    }
    else {
        // LABEL
        string label = instruction;
        label.pop_back();
        labelMap[label] = lineNumber;
        cerr << "LABEL " << label << " " << lineNumber << endl;

        val = 0;
    }
    return val;
}

string convertToBinary(const string &line, int lineNumber)
{
    string cleanLine = removeCommas(line);
    stringstream ss(cleanLine);
    string instruction, rd, rs, rt, imm, jumpAddress, shiftAmt;
    ss >> instruction;

    // Identify instruction type based on opcode
    string opcode = opcodeMap[instruction];
    string binaryInstruction;

    // Comment handling
    if (instruction[0] == '#') 
    {
        cerr << "COMMENT " << cleanLine << endl;
    }
    else if (instruction == "j")
    {
        // J-type: Opcode + Address
        ss >> jumpAddress;
        int address;
        if (isdigit(jumpAddress[0])) 
        {
            address = stoi(jumpAddress);
        }
        else 
        {
            address = labelMap[jumpAddress];
        }

        binaryInstruction = opcode + toBinary(address, 8) + "00000000";

        cerr << "JMP " << opcode << " " << toBinary(address, 8) << " " << "00000000" << endl;
    }
    else if (instruction == "sub" || instruction == "and" || instruction == "or" || 
             instruction == "nor" || instruction == "add") 
    {
        // NORMAL R TYPE
        ss >> rd >> rs >> rt;
        binaryInstruction = opcode + registerMap[rs] + registerMap[rt] + registerMap[rd] + "0000";

        cerr << "ALU " << opcode << " " << registerMap[rs] << " " << registerMap[rt] << " " << registerMap[rd] << " " << "0000" << endl;
    }
    else if (instruction == "srl" || instruction == "sll")
    {
        // SHIFT R TYPE
        ss >> rd >> rt >> shiftAmt;
        int shiftAmount = stoi(shiftAmt);
        binaryInstruction = opcode + registerMap[rt] + registerMap[rd] + toBinary(shiftAmount, 8);

        cerr << "SHI " << opcode << " " << registerMap[rt] << " " << registerMap[rd] << " " << toBinary(shiftAmount, 8) << endl;
    }
    else if (instruction == "lw" || instruction == "sw")
    {
        // Updated I-type format for lw/sw: Opcode + rs + rt + Immediate
        ss >> rt; // Get the destination register (e.g., $t0)

        string offsetAndSrc; // Format: offset($src_register)
        ss >> offsetAndSrc;

        // Extract offset and source register
        size_t parenPos = offsetAndSrc.find('(');
        int offset = stoi(offsetAndSrc.substr(0, parenPos)); // Extract offset before '('
        string src = offsetAndSrc.substr(parenPos + 1, offsetAndSrc.length() - parenPos - 2); // Extract register inside '()'

        binaryInstruction = opcode + registerMap[src] + registerMap[rt] + toBinary(offset, 8);

        cerr << "MEM " << opcode << " " << registerMap[src] << " " << registerMap[rt] << " " << toBinary(offset, 8) << endl;
    }
    else if (instruction == "addi" || instruction == "subi" || instruction == "andi" || instruction == "ori")
    {
        // I-type: Opcode + rs + rt + Immediate
        ss >> rt >> rs >> imm;
        int immediate = stoi(imm);

        if (immediate < 0) 
        {
            immediate = immediate + 512;
        }

        binaryInstruction = opcode + registerMap[rs] + registerMap[rt] + toBinary(immediate, 8);
    
        cerr << "IMM " << opcode << " " << registerMap[rs] << " " << registerMap[rt] << " " << toBinary(immediate, 8) << endl;
    }
    else if (instruction == "beq" || instruction == "bneq")
    {
        // BRANCH I TYPE
        ss >> rt >> rs >> imm;
        int address = labelMap[imm];
        int offset = address - lineNumber - 1;
        if (offset < 0) offset = 256 + offset;

        binaryInstruction = opcode + registerMap[rs] + registerMap[rt] + toBinary(offset, 8);
        cerr << "BRANCH " << opcode << " " << registerMap[rs] << " " << registerMap[rt] << " " << toBinary(offset, 8) << endl;
    }
    else 
    {
        // LABEL
        string label = instruction;
        label.pop_back();
        labelMap[label] = lineNumber;
        cerr << "LABEL " << label << " " << lineNumber << endl;

        return "";
    }

    return binaryInstruction;
}


int main()
{
    string path       = "D:\\CSE_CourseMaterials\\CSES 210 - ARCHITECTURE SESSIONAL\\MIPS_Assignment_03\\ASSEMBLY\\";
    string binaryPath = "D:\\CSE_CourseMaterials\\CSES 210 - ARCHITECTURE SESSIONAL\\MIPS_Assignment_03\\BINARY\\";
    
    string filename = "tushar_sir.mips";
    string inputFileName = path + filename;

    string outputFilename = binaryPath + "BIN_" + filename.substr(0, filename.find(".")) + ".txt";

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFilename);

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cerr << "Error opening file." << endl;
        return 1;
    }

    outputFile << "v2.0 raw" << endl;

    // label update
    string line;
    int lineNumber = 0;
    while (getline(inputFile, line))
    {
        if (line.empty() || line == "\n") continue;
        int val = updateLabels(line, lineNumber);
        if (val == 0) continue;
        lineNumber++;
    }
    cout<<"ALL THE JUMPS EVALUATED\n"<<endl;

    inputFile.close();
    ifstream inputFile2(inputFileName);

    lineNumber = 0;
    while (getline(inputFile2, line))
    {
        if (line.empty() || line == "\n") continue;
        string binary = convertToBinary(line, lineNumber);
        if (binary.empty()) continue;
        string hexValue = binaryToHex(binary);
        outputFile << hexValue << endl;
        lineNumber++;
    }

    inputFile2.close();
    outputFile.close();

    cout << "Conversion complete. Check '" << outputFilename << "' for results in hexadecimal format." << endl;

    return 0;
}
