#include<stdio.h>
#include<stdlib.h>
#include<string.h>

# define MASK 0x0000FFFF
# define REG_A 19
# define REG_B 16
# define MAXLINELENGTH 1000
# define MAXMEM 1<<16

// binary opcode
# define OP_ADD  0x00000000
# define OP_NOR  0x00400000
# define OP_LW   0x00800000
# define OP_SW   0x00C00000
# define OP_BEQ  0x01000000
# define OP_JALR 0x01400000
# define OP_HALT 0x01800000
# define OP_NOOP 0x01C00000

void printMemory(FILE*);
int readAndParse(FILE*, char*, char*, char*, char*, char*);

int isNumber(char*);
void isError(char*);

int LabelAddress(char*);

int RtypeInst(char*, char*, char*);
int ItypeInst(char*, char*, char*, int);
int JtypeInst(char*, char*);
int OtypeInst(char*);

char Label_Map[MAXMEM][7];
int Memory[MAXMEM];
int pc = 0;
int MemoryEND;

int main(int argc, char* argv[]){
	int Res, Opcode, Rem;

	char *inFileString, *outFileString;
	FILE *inFilePtr, *outFilePtr;
	char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH],
		arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];

	if(argc != 3){
		printf("error: usage: %s <assembly-code-file> <machine-code-file>\n", argv[0]);
		exit(1);
	}

	inFileString = argv[1];
	outFileString = argv[2];

	inFilePtr = fopen(inFileString, "r");
	if(inFilePtr == NULL){
		printf("error in opening %s\n", inFileString);
		exit(1);
	}

	outFilePtr = fopen(outFileString, "w");
	if(outFilePtr == NULL){
		printf("Error in opening %s\n", outFileString);
		exit(1);
	}

	while (1) {
		if(!readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2))
			break;
		
		if(strlen(label) > 6)
            isError("Error: label is too long.");

		if(!strcmp(label, "")){
			pc++;
			continue;
		}

		if(LabelAddress(label) != -1){
			printf("Error : duplicated label.\n ");
			exit(1);
		}
		strcpy(Label_Map[pc++], label);
	}
	MemoryEND = pc;

	pc = 0;
	rewind(inFilePtr);

	while (1){
		Res = Opcode = Rem = 0;
		if(!readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2))
			break;

		if(!strcmp(opcode, "add")){
			Opcode = OP_ADD;
			Rem = RtypeInst(arg0, arg1, arg2);
		}

		else if(!strcmp(opcode, "nor")){
			Opcode = OP_NOR;
			Rem = RtypeInst(arg0, arg1, arg2);
		}

		else if(!strcmp(opcode, "lw")){
			Opcode = OP_LW;
			Rem = ItypeInst(arg0, arg1, arg2, 0);
		}
		else if(!strcmp(opcode, "sw")){
			Opcode = OP_SW;
			Rem = ItypeInst(arg0, arg1, arg2, 0);
		}
		else if(!strcmp(opcode, "beq")){
			Opcode = OP_BEQ;
			Rem = ItypeInst(arg0, arg1, arg2, 1);
		}
		else if(!strcmp(opcode, "jalr")){
			Opcode = OP_JALR;
			Rem = JtypeInst(arg0, arg1);
		}
		else if(!strcmp(opcode, "halt")){
			Opcode = OP_HALT;
		}
		else if(!strcmp(opcode, "noop")){
			Opcode = OP_NOOP;
		}
		else if(!strcmp(opcode, ".fill")){
			if (isNumber(arg0)){
                long long temp = atoll(arg0);
                if (temp > 2147483647 || temp < -2147483648){
                    isError(".fill value overflow.");
                }
            }
            Rem = OtypeInst(arg0);
		}
		else{
            if(!strcmp(opcode,""))
                isError("empty opcode");
            else{
			    fprintf(stderr, "unrecognized opcode\n%s", opcode);
			    exit(1);
            }
		}
		Res = (Opcode | Rem);
		Memory[pc++] = Res;
	}
	printMemory(outFilePtr);

	return 0;
}

void isError(char *string){
    fprintf(stderr, "error: %s\n", string);
    exit(1);
}

void printMemory(FILE *readFilePtr){
	for(pc=0; pc<MemoryEND; pc++){
		printf("(address %d): %d (hex 0x%x)\n", pc, Memory[pc], Memory[pc]);
		if(readFilePtr != NULL)
			fprintf(readFilePtr, "%d\n", Memory[pc]);
	}
}

int readAndParse(FILE* inFilePtr, char* label, char* opcode, char* reg0, char* reg1, char* reg2){
	char line[MAXLINELENGTH];
	char* ptr = line;

	label[0] = opcode[0] = reg0[0] = reg1[0] = reg2[0] = '\0';

	if(fgets(line, MAXLINELENGTH, inFilePtr) == NULL)
		return 0;

	if(strchr(line, '\n') == NULL)
		isError("error: line too long");

	ptr = line;
	if(sscanf(ptr, "%[^\t\n\r ]", label))
		ptr += strlen(label);

	sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]",
		opcode, reg0, reg1, reg2);
	return 1;
}

int isNumber(char* string){
	int i;
	return((sscanf(string, "%d", &i)) == 1);
}

int LabelAddress(char* label){
	int i;
	for(i = 0; i < MemoryEND; i++)
		if (!strcmp(Label_Map[i], label))
			return i;
	return -1;
}

int RtypeInst(char* reg0, char* reg1, char* offset){
	if(!(isNumber(reg0) && isNumber(reg1) && isNumber(offset)))
		isError("some of arguments are not valid.");

	int RegA = atoi(reg0) << REG_A;
	int RegB = atoi(reg1) << REG_B;
	int Offset = atoi(offset);

	return RegA | RegB | Offset;
}

int ItypeInst(char* reg0, char* reg1, char* offset, int count){
	if(!(isNumber(reg0) && isNumber(reg1)))
		isError("some of arguments are not valid.");

	if(!strcmp(offset, ""))
		isError("empty offset");

	int RegA = atoi(reg0) << REG_A;
	int RegB = atoi(reg1) << REG_B;
	int Offset;
	if (isNumber(offset)) 
		Offset = atoi(offset);
	else{
		if((Offset = LabelAddress(offset)) == -1){
			printf("Error : unknown label.\n");
			printf("%s %s %s\n", reg0, reg1, offset);
			while (1);
			exit(1);
		}

		if(count)
			Offset -= (pc + 1);
	}
	if(Offset < -32768 || Offset > 32767)
		isError("out of range");
	if(count)
		Offset &= MASK;

	return RegA | RegB | Offset;
}

int JtypeInst(char* reg0, char* reg1){
	if(!(isNumber(reg0) && isNumber(reg1)))
		isError("some of arguments are not valid.");

	int RegA = atoi(reg0) << REG_A;
	int RegB = atoi(reg1) << REG_B;

	return RegA | RegB;
}

int OtypeInst(char* reg0){
	if(!strcmp(reg0, ""))
		isError("empty offset");
	int n;

	if (isNumber(reg0))
		n = atoi(reg0);
	else{
		if((n = LabelAddress(reg0)) == -1)
			isError("unknow label.");
	}
	return n;
}