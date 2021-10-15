import argparse

#Set arguments with argpars
parser  = argparse.ArgumentParser(description="Compile assembly")
parser.add_argument('-file' , help = "File to compile", required= True)
parser.add_argument('-output' , help = "Output name", required= False)


#Get args
args = parser.parse_args()
file_input  = args.file
file_output = args.output

#Instruction class
class Instruction():
    BCC = b""
    IV_FLAG = b""
    OPCODE = b""
    OPE1= b""
    OPE2=b""
    DEST = b""
    IV = b""

class InstructionBCC():
    BCC = b""
    NEGA_POSA = b""
    OFFSET = b""

#str = "a"
#bin(int(str,16))
#'0b1010'

#BCC dictionnary
BCC = {
    "B":b"\x08",
    "BEQ":b"\x09",
    "BNE":b"\x10",
    "BLE":b"\x11",
    "BGE":b"\x12",
    "BL":b"\x13",
    "BG":b"\x14"
}

#OPCODE dictionnary
OPCODE = {
    "AND":b"\x00",
    "ORR":b"\x01",
    "EOR":b"\x02",
    "ADD":b"\x03",
    "ADC":b"\x04",
    "CMP":b"\x05",
    "SUB":b"\x06",
    "SBC":b"\x07",
    "MOV":b"\x08",
    "LSH":b"\x09",
    "RSH":b"\x10"
}

#Init instructions tab
instructions = []

f = open(file_input,"r")
lines = f.readlines()

for line in lines :
    instr = Instruction()
    line = line.replace("\n","").replace(","," ").split(" ")
    print(line)
    instr.OPCODE = OPCODE.get(line[0])

    instructions.append(instr)










