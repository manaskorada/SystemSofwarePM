#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 500

int pas[500];

void print_output() {

}

int base( int BP, int L) {
    int arb = BP; // arb = activation record base
    while ( L > 0) {
        arb = pas[arb];
        L--;
    }
    return arb;
}



int main(int argc, char **argv) {
    // Fill PAS array with 0s
    for (int i = 0; i < 500; i++) {
        pas[i] = 0;
    }


    // Fetches file input
    FILE* finput = fopen(argv[1], "r");
    int fetch_index = 0;
    while (fscanf(finput, "%d %d %d", &pas[fetch_index], &pas[fetch_index+1], &pas[fetch_index+2]) != EOF) {
        fetch_index += 3;
    }
    fclose(finput);

    int BP = 499;
    int SP = BP + 1;
    int PC = 0;
    int IR[3] = {0, 0, 0};

    printf("                PC   BP     SP   stack\n");
    printf("Initial values: %d   %d   %d\n", PC, BP, SP);

    

    
    
    while (pas[PC] != 0) {
        IR[0] = pas[PC];
        IR[1] = pas[PC+1];
        IR[2] = pas[PC+2];

        

        switch(IR[0]) {
            case 1: // LIT
                SP = SP - 1;
                pas[SP] = IR[2];
                break;
            case 2:
                switch(IR[2]) {
                    case 0: // RTN
                        SP = BP + 1;
                        BP = pas[SP - 2];
                        PC = pas[SP - 3];
                        break;
                    case 1: // ADD
                        pas[SP + 1] = pas[SP + 1] + pas[SP];
                        SP = SP + 1;
                        break;
                    case 2: // SUB
                        pas[SP + 1] = pas[SP + 1] - pas[SP];
                        SP = SP + 1;
                        break;
                    case 3: // MUL
                        pas[SP + 1] = pas[SP + 1] * pas[SP];
                        SP = SP + 1;
                        break;
                    case 4: // DIV
                        pas[SP + 1] = pas[SP + 1] / pas[SP];
                        SP = SP + 1;
                        break;
                    case 5: // EQL
                        pas[SP + 1] = (pas[SP + 1] == pas[SP]);
                        SP = SP + 1;
                        break;
                    case 6: // NEQ
                        pas[SP + 1] = (pas[SP + 1] != pas[SP]);
                        SP = SP + 1;
                        break;
                    case 7: // LSS
                        pas[SP + 1] = (pas[SP + 1] < pas[SP]);
                        SP = SP + 1;
                        break;
                    case 8: // LEQ
                        pas[SP + 1] = (pas[SP + 1] <= pas[SP]);
                        SP = SP + 1;
                        break;
                    case 9: // GTR
                        pas[SP + 1] = (pas[SP + 1] > pas[SP]);
                        SP = SP + 1;
                        break;
                    case 10: // GEQ
                        pas[SP + 1] = (pas[SP + 1] >= pas[SP]);
                        SP = SP + 1;
                        break;
                    case 11: // ODD
                        pas[SP] = pas[SP] % 2;
                        break;
                }
                break;
            case 3: // LOD
                SP = SP - 1;
                pas[SP] = pas[base(BP, IR[1]) - IR[2]];
                break;
            case 4: // STO
                pas[base(BP, IR[1]) - IR[2]] = pas[SP];
                SP = SP + 1;
                break;
            case 5: // CAL
                pas[SP - 1] = base(BP, IR[1]);
                pas[SP - 2] = BP;
                pas[SP - 3] = PC;
                BP = SP - 1;
                PC = IR[2];
                break;
            case 6: // INC
                SP = SP - IR[2];
                break;
            case 7: // JMP
                PC = IR[2];
                break;
            case 8: // JPC
                if (pas[SP] == 0) {
                    PC = IR[2];
                }
                SP = SP + 1;
                break;
            case 9: // SYS
                switch(IR[2]) {
                    case 1:
                        printf("%d", pas[SP]);
                        SP = SP + 1;
                        break;
                    case 2:
                        
                        break;
                    case 3:
                        break;
                }
                break;
            
        }
    }

    
    PC += 3;
}

