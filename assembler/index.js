const fs = require('fs');

var asm_file_path = '../programs/asm/'+process.argv[2];
var out_file_path = '../programs/raw/'+process.argv[2].split('.')[0]+'.raw';

console.log(asm_file_path + " -> ", out_file_path);

var OP_CODES = {
    "SET": "0x01",
    "MOV": "0x02",
    "CLR": "0x03",
    "GET": "0x04",
    "STR": "0x05",
    "OUT": "0x06",

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
    "PUSH": "0xb6",
    "POP": "0xb7",
    "CALL": "0xb8",
    "RET": "0xb9",
}

var REGISTERS = {
    "reg[a]": "0x00",
    "reg[b]": "0x01",
    "reg[c]": "0x02",
    "reg[d]": "0x03",
    "reg[e]": "0x04",
    "reg[f]": "0x05",
    "reg[g]": "0x05",
    "reg[z]": "0x06",
}

function operand_to_hex(operand = "0x00") {
    if (operand == "0x00") {return operand};
    if (operand.includes('reg')) {
        return REGISTERS[operand];
    } else {
        // turn immediate into hex
        return "0x"+(parseInt(operand).toString(16)+"").padStart(2, "0")
    }
}

fs.readFile('../programs/'+asm_file_path, 'utf8', (err, data) => {
    var total_bytes = 0;

    if (err) { console.error('Error reading file:', err); return; }

    var out = "";

    console.log("ASM: ")
    let lines = data.split('\r\n');
    for (let i = 0; i < lines.length; i++) {
        let line = lines[i].split(';')[0];

        // skip blank lines
        if (line == "\r" || line == "") {continue;} 
        line = line.replaceAll(',', '');
        
        console.log(line);

        // console.log(line);
        split_line = line.split(' ');

        out += OP_CODES[split_line[0]] + ", ";
        out += operand_to_hex(split_line[1])+ ", ";
        out += operand_to_hex(split_line[2])+ ", ";
        out += operand_to_hex(split_line[3])+ ", ";

        total_bytes += 4;

        out += "\n";
    }

    console.log("---");
    console.log("HEX: ");

    console.log(out);

    console.log(`\nTotal bytes: ${total_bytes}/256 (${(total_bytes/256) * 100}%) `);
    
    fs.writeFile(out_file_path, out, err => {
        if (err) {
            console.error(err);
        } else {
            // file written successfully

            console.log("hex written to file. ");
        }
    });

});