import argparse

#Set arguments with argpars
parser  = argparse.ArgumentParser(description="Compile assembly")
parser.add_argument('-f','-file' , help = "File to compile", required= True)
parser.add_argument('-o','-output' , help = "Output name", required= True)
parser.add_argument('-v', '-verbose',help ="Verbose mode", action='store_true')


#Get args
args = parser.parse_args()
file_input  = args.f
file_output = args.o
verbose = args.v


#Padding for BCC, OPCODE, REGISTERS
def padding(entree):
    if (len(entree) <4):
        add = 4- len(entree)
        sortie = "0"*add + entree
        return sortie
    else:
        return entree



#BCC dictionnary
BCC = {
    "B":"08",
    "BEQ":"09",
    "BNE":"10",
    "BLE":"11",
    "BGE":"12",
    "BL":"13",
    "BG":"14"
}

#Register dictionnary
REGISTERS = {
    "R0":"00",
    "R1":"01",
    "R2":"02",
    "R3":"03",
    "R4":"04",
    "R5":"05",
    "R6":"06",
    "R7":"07",
    "R8":"08",
    "R9":"09",
    "R10":"10",
    "R11":"11",
    "R12":"12",
    "R13":"13",
    "R14":"14",
    "R15":"15"
}
#OPCODE dictionnary
OPCODE = {
    "AND":"00",
    "ORR":"01",
    "EOR":"02",
    "ADD":"03",
    "ADC":"04",
    "CMP":"05",
    "SUB":"06",
    "SBC":"07",
    "MOV":"08",
    "LSH":"09",
    "RSH":"10"
}

#Init instructions tab
instructions = []

#Read assembly file, s extension
f = open(file_input,"r")
lines = f.readlines()

for line in lines :
    instr = ""
    line = line.replace("\n","").replace(","," ").split(" ")
    line = [s.upper() for s in line if (len(s) !=0 )]
    if verbose :
        print("Instruction Array")
        print(line)
    if (BCC.get(line[0],"None") != "None"):
        instr += padding(bin(int(BCC.get(line[0]),10)).replace("0b",""))
        if ("-" in line[1]):
            instr +="1" #Negatif
        else:
            instr += "0" #Positif
        offset = bin(int(line[1].replace("0x","").replace("-","").replace("+",""),16)).replace("0b","")
        if (len(offset)<26) :
            add = 26 - len(offset)
            instr += "0"*add + offset
        else: 
            instr += offset
        instructions.append(instr)
    else:
        instr +="0000"
        instr +="000"
        if (len(line) == 3):#Compare 
            if (line[2].isnumeric()): 
                instr+="1"
                instr+=padding(bin(int(OPCODE.get(line[0]),16)).replace("0b",""))
                instr+="0000"
                instr+="0000"
                instr+=padding(bin(int(REGISTERS.get(line[1]),16)).replace("0b",""))
                iv=bin(int(line[2],16)).replace("0b","")
                if (len(iv)<8) :
                    add = 8- len(iv)
                    instr += "0"*add + iv
                else: 
                    instr += iv

            else:
                instr+="0"
                instr+=padding(bin(int(OPCODE.get(line[0]),16)).replace("0b",""))
                instr+=padding(bin(int(REGISTERS.get(line[1]),16)).replace("0b",""))
                instr+=padding(bin(int(REGISTERS.get(line[2]),16)).replace("0b",""))
                instr+="0000"
                instr+="00000000"
            instructions.append(instr)

        if (len(line) == 4):
            if (line[3].isnumeric()):
                instr+="1"
                instr+=padding(bin(int(OPCODE.get(line[0]),16)).replace("0b",""))
                instr+=padding(bin(int(REGISTERS.get(line[2]),16)).replace("0b",""))
                instr+="0000"         
                instr+=padding(bin(int(REGISTERS.get(line[1]),16)).replace("0b",""))
                iv=bin(int(line[3],16)).replace("0b","")
                if (len(iv) <8) :
                    add = 8- len(iv)
                    instr += "0"*add + iv
                else: 
                    instr += iv    
                
            else:
                instr+="0"
                instr+=padding(bin(int(OPCODE.get(line[0]),16)).replace("0b",""))
                instr+=padding(bin(int(REGISTERS.get(line[2]),16)).replace("0b",""))
                instr+=padding(bin(int(REGISTERS.get(line[3]),16)).replace("0b",""))      
                instr+=padding(bin(int(REGISTERS.get(line[1]),16)).replace("0b",""))
                instr+="00000000"
            instructions.append(instr)
    
#Write instructions in binary file
f = open(file_output, "wb")
for line in instructions:
    if verbose :
        print("Bits :", line)
        print("Length: ", len(line))
    int_value = int(line,2)
    if verbose :
        print("Int value: ", int_value)
    byte_value = int_value.to_bytes(4,byteorder="big")
    if verbose :
        print("Byte value: ", byte_value)

    #Write bit by bit instructions
    for i in range(0,4):
        #print(int(line[i*8:(i+1)*8],2).to_bytes(1,byteorder="big"))
        f.write(int(line[i*8:(i+1)*8],2).to_bytes(1,byteorder="big"))

                












