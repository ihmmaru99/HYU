#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMMEMORY 65536 /* maximum number of words in memory */
#define NUMREGS 8       /* number of machine registers */
#define MAXLINELENGTH 1000

typedef struct stateStruct{
    int pc;
    int mem[NUMMEMORY];
    int reg[NUMREGS];
    int numMemory;
} stateType;

void printState(stateType *);
void isError(char *string);

int ValidRegi(int reg);

int convertNum(int num);

void parseInstfromMem(stateType *statePtr, int *opcode, int *arg0, int *arg1, int *arg2);

void RtypeInst(stateType *statePtr, int opcode, int arg0, int arg1, int dest);
void ItypeInst(stateType *statePtr, int opcode, int arg0, int arg1, int offset);
void JtypeInst(stateType *statePtr, int opcode, int arg0, int arg1);

int main(int argc, char *argv[]){
    char line[MAXLINELENGTH];
    stateType state;
    FILE *filePtr;
    int count = 0;

    if (argc != 2){
        printf("error: usage: %s <machine-code file>\n", argv[0]);
        exit(1);
    }

    filePtr = fopen(argv[1], "r");
    if (filePtr == NULL){
        printf("error: can't open file %s", argv[1]);
        perror("fopen");
        exit(1);
    }

    for (state.numMemory=0; fgets(line, MAXLINELENGTH, filePtr) != NULL; state.numMemory++){

        if (sscanf(line, "%d", state.mem + state.numMemory) != 1){
            printf("error in reading address %d\n", state.numMemory);
            exit(1);
        }
        printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]);
    }

    printState(&state);
    while (1){
        int Halt = 0;
        int opcode, arg0, arg1, arg2;
        parseInstfromMem(&state, &opcode, &arg0, &arg1, &arg2);

        state.pc++;
        count++;

        if (state.pc < 0 || state.pc >= NUMMEMORY)
            isError("PC is out of memory");

        switch (opcode){
        case 0: // [R type] add
        case 1: // [R type] nor
            RtypeInst(&state, opcode, arg0, arg1, arg2);
            break;
        case 2: // [I type] lw
        case 3: // [I type] sw
        case 4: // [I type] beq
            ItypeInst(&state, opcode, arg0, arg1, arg2);
            break;
        case 5: // [J type] jalr
            JtypeInst(&state, opcode, arg0, arg1);
            break;
        case 6: // [O type] halt
            Halt = 1;
            break;
        case 7: // [O type] noop
            break;
        default:
            fprintf(stderr, "unrecognized opcode\n%s", opcode);
			exit(1);
        }

        // [O-TYPE] halt execution in while loop
        if (Halt)
            break;
        
		printState(&state);
    }

    printState(&state);

    fclose(filePtr);
    exit(0);
}

void printState(stateType *statePtr){
    int i;
    printf("\n@@@\nstate:\n");
    printf("\tpc %d\n", statePtr->pc);
    printf("\tmemory:\n");
    for (i=0; i < statePtr->numMemory; i++)
        printf("\t\tmem[ %d ] %d\n", i, statePtr->mem[i]);
    printf("\tregisters:\n");
    for (i = 0; i < NUMREGS; i++)
        printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);
    printf("end state\n");
}

void isError(char *string){
    fprintf(stderr, "error: %s\n", string);
    exit(1);
}

int ValidRegi(int reg){
    return (int)(reg >= 0 && reg < NUMREGS);
}

int convertNum(int num){
    if (num & (1 << 15))
        num -= (1 << 16);
    return (num);
}

void parseInstfromMem(stateType *statePtr, int *opcode, int *arg0, int *arg1, int *arg2){
    int memValue = statePtr->mem[statePtr->pc];

    *opcode = (memValue >> 22) & 0b111;
    *arg0 = (memValue >> 19) & 0b111;
    *arg1 = (memValue >> 16) & 0b111;
    *arg2 = (memValue & 0xFFFF);
}

void RtypeInst(stateType *statePtr, int opcode, int arg0, int arg1, int dest){
    if (!ValidRegi(arg0) || !ValidRegi(arg1) || !ValidRegi(dest))
        isError("Register is not valid.");

    switch (opcode){
    case 0: // add
        statePtr->reg[dest] = statePtr->reg[arg0] + statePtr->reg[arg1];
        break;
    case 1: // nor
        statePtr->reg[dest] = ~(statePtr->reg[arg0] | statePtr->reg[arg1]);
        break;
    default:
        isError("We can't support this opcode");
        break;
    }
}

void ItypeInst(stateType *statePtr, int opcode, int arg0, int arg1, int offset){
    offset = convertNum(offset);

    if (!ValidRegi(arg0) || !ValidRegi(arg1))
        isError("Register is not valid.");

    if (offset > 32767 || offset < -32768)
        isError("Offset is out of range");

    switch (opcode){
    case 2:
        statePtr->reg[arg1] = statePtr->mem[statePtr->reg[arg0] + offset];
        break;
    case 3:
        statePtr->mem[statePtr->reg[arg0] + offset] = statePtr->reg[arg1];
        break;
    case 4:
        if (statePtr->reg[arg0] == statePtr->reg[arg1])
            statePtr->pc += offset;
        break;
    default:
        isError("We can't support this opcode");
        break;
    }
}

void JtypeInst(stateType *statePtr, int opcode, int arg0, int arg1){
    if (!ValidRegi(arg0) || !ValidRegi(arg1))
        isError("Register is not valid.");

    switch (opcode){
    case 5:
        statePtr->reg[arg1] = statePtr->pc;
        statePtr->pc = statePtr->reg[arg0];
        break;
    default:
        isError("We can't support this opcode");
        break;
    }
}