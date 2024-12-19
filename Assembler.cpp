#include <bits/stdc++.h>
using namespace std;

// Map for opcodes
unordered_map<string, string> opcodeMap = {
    {"sub", "0000"},  {"srl", "0001"},  {"andi", "0010"}, 
    {"ori", "0011"},  {"nor", "0100"},  {"bneq", "0101"}, 
    {"and", "0110"},  {"beq", "0111"},  {"sw", "1000"}, 
    {"subi", "1001"}, {"addi", "1010"}, {"sll", "1011"}, 
    {"add", "1100"},  {"lw", "1101"},   {"or", "1110"}, 
    {"j", "1111"},    
    
    {"nop", "0000"},
};

unordered_map<string, string> registerMap = {
    {"$zero", "0000"}, {"$t1", "0001"}, {"$t2", "0010"}, 
    {"$t3", "0011"}, {"$t4", "0100"}, {"$t0", "0101"}, 
    {"$sp", "0110"}};


// Map for labels
unordered_map<string, int> labelMap;

string nop_binary = opcodeMap["nop"] + registerMap["$zero"] + registerMap["$zero"] + registerMap["$zero"] + "0000";


void checkValidRegister(const string &reg)
{
    if (registerMap.find(reg) == registerMap.end())
    {
        cerr << "Invalid register: " << reg << endl;
        cerr << "Exiting program..." << endl;
        exit(1);
    }
}

void checkValidLabel(const string &label)
{
    if (labelMap.find(label) == labelMap.end())
    {
        cerr << "Invalid label: " << label << endl;
        cerr << "Exiting program..." << endl;
        exit(1);
    }
}

string toBinary(int value, int bits)
{
    return bitset<16>(value).to_string().substr(16 - bits, bits);
}

string binaryToHex(const string &binary)
{
    stringstream ss;
    unsigned long decimalValue = bitset<32>(binary).to_ulong(); // Convert binary to decimal
    ss << hex /* << uppercase */ << setw(binary.length() / 4) << setfill('0') << decimalValue; // Convert decimal to hex
    return ss.str();
}

vector<string> readFile(string filename)
{
    vector<string> lines;
    ifstream file(filename);
    string line;
    
    while (getline(file, line))
    {
        if (!line.empty() && line[0] != '#')
        {
            lines.push_back(line);
        }
    }

    return lines;
}

vector<string> tokenizer(string line)
{
    vector<string> tokens;
    string token = "";

    for (char ch : line)
    {
        if (isspace(ch) || ch == ',' || ch == '(' || ch == ')')
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            // Add the delimiter itself as a separate token if it's not a space
            if (ch == '(' || ch == ')')
            {
                tokens.push_back(string(1, ch));
            }
        }
        else if(ch == '#')
        {
            break;
        }
        else
        {
            // Build the current token
            token += ch;
        }
    }

    // Add the last token if any
    if(!token.empty())
    {
        tokens.push_back(token);
    }

    return tokens;
}

vector<string> renameRegisters(vector<string> lines)
{
    vector<string> filteredLines;

    for (int i = 0; i < lines.size(); i++)
    {
        string line = lines[i];
        vector<string> tokens = tokenizer(line);

        if (tokens.size() > 0)
        {
            if(tokens[0].size() > 0 && tokens[0][0] == '@')
            {
                // @ is used to rename registers like
                // @ t3 head
                if(tokens.size() < 3)
                {
                    cerr << "!! Invalid number of arguments for @ instruction." << endl;
                    exit(1);
                }
 
                string oldNameReg = "$" + tokens[1];
                string newNameReg = "$" + tokens[2];

                if(registerMap.find(oldNameReg) == registerMap.end())
                {
                    cerr << "!! Invalid register name: " << oldNameReg << endl;
                    cerr << "!! Cant rename register. Exiting..." << endl;
                    exit(1);
                }

                if(oldNameReg != newNameReg)
                {
                    // Set the binary of the new register to the binary of the old register
                    registerMap[newNameReg] = registerMap[oldNameReg];
                    registerMap.erase(oldNameReg);
                }
            }
            else    
            {
                filteredLines.push_back(line);
            }
        }
    }

    return filteredLines;
}

void updateLabelMaps(vector<string> lines)
{
    int lineNumber = 0;
    for (string line : lines)
    {
        vector<string> tokens = tokenizer(line);

        if(tokens.size() == 0) continue;

        if (tokens[0].size() > 0 && tokens[0].back() == ':')
        {
            string label = tokens[0].substr(0, tokens[0].size() - 1);
            labelMap[label] = lineNumber;

            cerr << "Label: " << label << " at line: " << lineNumber << endl;
        }
        else
        {
            lineNumber++;
        }
    }
}

string getBinary(vector<string> tokens, int lineNumber)
{
    string opcode = opcodeMap[tokens[0]];
    string binary = "";

    if(tokens[0] == "nop")
    {
        // NOP : sub $zero, $zero, $zer
        binary = nop_binary;
        cerr << opcode << " " << registerMap["$zero"] << " " << registerMap["$zero"] << " " << registerMap["$zero"] << " " << "0000" << endl;
    }
    else if (tokens[0] == "j")
    {
        if(tokens.size() < 2)
        {
            cerr << "!! Invalid number of arguments for j instruction." << endl;
            exit(1);
        }
        // J-type: Opcode + Address
        // Input Structure: j jumpAddress [label or number]
        string jumpAddress = tokens[1];

        // two possiblity either a number was given or a label
        int address;
        if (isdigit(jumpAddress[0])) 
        {
            address = stoi(jumpAddress);
        }
        else 
        {
            address = labelMap[jumpAddress];
        }

        binary = opcode + toBinary(address, 8) + "00000000";
        
        cerr << "JMP " << opcode << " " << toBinary(address, 8) << " " << "00000000" << endl;
    }
    else if (tokens[0] == "sub" || tokens[0] == "and" || tokens[0] == "or" || 
             tokens[0] == "nor" || tokens[0] == "add") 
    {
        // NORMAL R TYPE
        // R-type: Opcode + rs + rt + rd + shift
        // Input Structure: sub rd, rs, rt
        if(tokens.size() < 4)
        {
            cerr << "!! Invalid number of arguments for " << tokens[0] << " instruction." << endl;
            exit(1);
        }
        string rd = tokens[1];
        string rs = tokens[2];
        string rt = tokens[3];

        checkValidRegister(rs);
        checkValidRegister(rt);
        checkValidRegister(rd);

        binary = opcode + registerMap[rs] + registerMap[rt] + registerMap[rd] + "0000";

        cerr << tokens[0] << " " << opcode << " " << registerMap[rs] << " " << registerMap[rt] << " " << registerMap[rd] << " " << "0000" << endl;
    }
    else if (tokens[0] == "srl" || tokens[0] == "sll")
    {
        // SHIFT R TYPE
        // R-type: Opcode + rs + rt + rd + shift
        // Input Structure: srl rd, rt, shiftAmt
        if(tokens.size() < 4)
        {
            cerr << "!! Invalid number of arguments for " << tokens[0] << " instruction." << endl;
            exit(1);
        }

        string rd = tokens[1];
        string rt = tokens[2];
        string shiftAmt = tokens[3];

        checkValidRegister(rt);
        checkValidRegister(rd);

        int shiftAmount = stoi(shiftAmt);

        // WHEN SHIFTING USE RS AS NUMBER , RT AS DESTINATION REGISTER , SHIFT AMOUNT AS SHIFT AMOUNT
        binary = opcode + registerMap[rt] + registerMap[rd] + toBinary(shiftAmount, 8);

        cerr << tokens[0] << " " << opcode << " " << registerMap[rt] << " " << registerMap[rd] << " " << toBinary(shiftAmount, 8) << endl;
    }
    else if(tokens[0] == "addi" || tokens[0] == "subi" || 
            tokens[0] == "andi" || tokens[0] == "ori")
    {
        // I-type: Opcode + rs + rt + Immediate
        // Input Structure: addi rt, rs, imm
        if(tokens.size() < 4)
        {
            cerr << "!! Invalid number of arguments for " << tokens[0] << " instruction." << endl;
            exit(1);
        }

        string rt = tokens[1];
        string rs = tokens[2];
        string imm = tokens[3];

        checkValidRegister(rs);
        checkValidRegister(rt);

        int immediate = stoi(imm);

        binary = opcode + registerMap[rs] + registerMap[rt] + toBinary(immediate, 8);

        cerr << tokens[0] << " " << opcode << " " << registerMap[rs] << " " << registerMap[rt] << " " << toBinary(immediate, 8) << endl;
    }
    else if(tokens[0] == "lw" || tokens[0] == "sw")
    {
        // Updated I-type format for lw/sw: Opcode + rs + rt + Immediate
        // Input Structure: lw rt, offset(rs)
        // TOKENS INCLUDE PARANTHESIS ALSO
        if(tokens.size() < 5)
        {
            cerr << "!! Invalid number of arguments for " << tokens[0] << " instruction." << endl;
            exit(1);
        }

        string rt = tokens[1]; // Get the destination register (e.g., $t0)
        string imm = tokens[2]; // Get the offset (e.g., 4)
        string rs = tokens[4]; // Get the source register (e.g., $t1)

        checkValidRegister(rt);
        checkValidRegister(rs);

        int immediate = stoi(imm);

        // binaryInstruction = opcode + registerMap[rs] + registerMap[rt] + toBinary(immediate, 8);
        binary = opcode + registerMap[rs] + registerMap[rt] + toBinary(immediate, 8);

        cerr << tokens[0] << " " << opcode << " " << registerMap[rs] << " " << registerMap[rt] << " " << toBinary(immediate, 8) << endl;
    }
    else if(tokens[0] == "beq" || tokens[0] == "bneq")
    {
        // BRANCH I TYPE
        // I-type: Opcode + rs + rt + Immediate
        // Input Structure: beq rt, rs, label
        if(tokens.size() < 4)
        {
            cerr << "!! Invalid number of arguments for " << tokens[0] << " instruction." << endl;
            exit(1);
        }

        string rt = tokens[1];
        string rs = tokens[2];
        string label = tokens[3];
 
        checkValidRegister(rs);
        checkValidRegister(rt);
        checkValidLabel(label);

        int address = labelMap[label];
        
        // calculating the offset
        int offset = address - lineNumber - 1;
        if(offset < 0) offset = 256 + offset;

        binary = opcode + registerMap[rs] + registerMap[rt] + toBinary(offset, 8);
        cerr << tokens[0] << " " << opcode << " " << registerMap[rs] << " " << registerMap[rt] << " " << toBinary(offset, 8) << endl;
    }
    else { 
        // DO NOTHING
    }

    return binary;
}

int main()
{
    string path = "ASSEMBLY\\";
    string binaryPath = "BINARY\\";
    
    string filename = "PIPELINE_TEST.mips";

    string inputFileName = path + filename;
    string outputFilename = binaryPath + "BIN_" + filename.substr(0, filename.find("."));
    outputFilename += ".txt";

    ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        cerr << "Error opening file. " << inputFileName  << endl;
        return 1;
    }

    ofstream outputFile(outputFilename);
    if(!outputFile.is_open())
    {
        cerr << "Error creating output file. " << outputFilename << endl;
        return 1;
    }

    outputFile << "v2.0 raw" << endl;

    vector<string> lines = readFile(inputFileName);

    // Set $sp to the highest memory address available
    lines.insert(lines.begin(), "addi $sp, $zero, -1");

    lines = renameRegisters(lines);
    updateLabelMaps(lines);

    // for (string line : lines) cerr << line << endl; 

    int lineNumber = 0;
    for (string line : lines)
    {
        vector<string> tokens = tokenizer(line);
        if(tokens.size() > 0)
        {
            string binary = getBinary(tokens, lineNumber);
            if(!binary.empty() && binary != "\n" && binary != "")
            {
                outputFile << binaryToHex(binary) << endl;
                lineNumber++;
            }
        }
    }

    inputFile.close();
    outputFile.close();

    cerr << endl;
    cerr << "Binary conversion completed." << endl;
    cout << "TOTAL BYTES: " << lineNumber << endl;
    cerr << "Output file: " << outputFilename << endl;
    
    // instruction memory is 8 bit wide, so only 256 instructions can be stored
    if(lineNumber > 256)
    {
        cerr << "!! Instruction memory overflow. Only 256 instructions are allowed." << endl;
    }

    return 0;
}