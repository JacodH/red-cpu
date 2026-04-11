const fs = require('fs');

var asm_file_path = '../programs/asm/'+process.argv[2];
var out_file_path = '../programs/raw/'+process.argv[2].split('.')[0]+'.raw';

console.log(`Assembling: ${asm_file_path} -> ${out_file_path}`);

var OP_CODES = {
    "SET": "0x01",
    "MOV": "0x02",
    "CLR": "0x03",
    "GET": "0x04",
    "STR": "0x05",
    "OUT": "0x06",
    "ROM": "0x07",
    "RAM": "0x08",

    "ADI": "0xa1",
    "ADD": "0xa2",
    "SUI": "0xa3",
    "SUB": "0xa4",
    "AND": "0xa5",
    "OR": "0xa6",
    "XOR": "0xa7",
    "NOT": "0xa8",
    "SHL": "0xa9",
    "SHR": "0xaa",
    "LT": "0xab",
    "GT": "0xac",
    "EQ": "0xad",
    "NE": "0xae",

    "NOP": "0xb1",
    "HLT": "0xb2",
    "JMP": "0xb3",
    "JEI": "0xb4",
    "JER": "0xb5",

    "JMPR": "0xb6",
    "JEIR": "0xb7",
    "JERR": "0xb8",

    "PUSH": "0xc1",
    "POP": "0xc2",
    "CALL": "0xc3",
    "RET": "0xc4",
}

var REGISTERS = {
    "reg[a]": "0x00",
    "reg[b]": "0x01",
    "reg[c]": "0x02",
    "reg[d]": "0x03",
    "reg[e]": "0x04",
    "reg[f]": "0x05",
    "reg[g]": "0x06",
    "reg[z]": "0x07",
}

function int_to_hex(int) {
    return "0x"+parseInt(int).toString(16).padStart(2, "0");
}

function operand_to_hex(operand, labels) {
    // Empty operands are just 0x00
    if (operand == undefined) {return "0x00"};

    // Registers
    if (operand.startsWith('reg[') == true) {
        return REGISTERS[operand];
    }

    // Hex immediate go straight in 
    if (operand.startsWith('0x')) {
        return operand;
    }

    // Labels turn into their address
    if (operand.startsWith('$')) {
        operand = operand.slice(1);
        let addr = labels[operand];

        return int_to_hex(addr);
    }


    // Must be decimal immediate 
    return int_to_hex(operand);
}

fs.readFile(asm_file_path, 'utf8', (err, data) => {
    // 1. Clean lines
    var clean_lines = data.split("\r\n");
    for (let i = 0; i < clean_lines.length; i++) {
        clean_lines[i] = clean_lines[i].split(';')[0].trimStart();
        if (clean_lines[i] == "") {
            clean_lines.splice(i, 1);
            i--;
        }
    }
    
    console.log("\n1. Cleaned lines: ");
    // for (line of clean_lines) {console.log(line)};
    
    // 2. Store label addresses 
    var addr = 0;
    var labels = {};
    
    for (line of clean_lines) {
        if (line[line.length-1] == ":") {
            line = line.slice(0, -1);
            labels[line] = addr
        }else {
            addr += 4;
            console.log(int_to_hex(addr)+" | "+line);
        }
    }
    console.log("\n2. Found labels: ");
    console.log(labels);

    // 3. Final, convert everything to hex
    var hex = "";
    for (line of clean_lines) {
        // Skip over labels
        if (line[line.length-1] == ":") { continue };
        
        // For functions, we need to remove the indentation
        line = line.trimStart();
        
        let operands = line.split(" ");
        // console.log(operands);


        // Convert opcode to hex
        hex += OP_CODES[operands[0]]+", ";
        hex += operand_to_hex(operands[1], labels)+", ";
        hex += operand_to_hex(operands[2], labels)+", ";
        hex += operand_to_hex(operands[3], labels)+", \n";
    }

    console.log("\n3. Convert to hex: ");
    console.log(hex);

    console.log(`Size: ${addr}/256 Bytes, ${((addr/256)*100).toFixed()}%`);

    fs.writeFile(out_file_path, hex, err => {
        if (err) {
            console.error(err);
        } else {
            console.log("\nProgram written to .raw file successfully. ");
        }
    });
});
