/*
	EMULATOR FOR A PC CONTANING:
		* 8086 CPU
		* 1 MB Ram (so cool)
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
/*
	CPU 
*/
// REGISTERS
struct regs{
	uint8_t AH,BH,CH,DH,AL,BL,CL,DL,AX,BX,CX,DX;
};
// INDEX REGISTERS
uint8_t SI,DI,BP,SP;
// PROGRAM COUNTER
int IP = 0;
// SEGMENT REGISTERS
uint8_t CS,DS,ES,SS;
// FLAGS
int O,D,I,T,S,Z,A,P,C;
// funcs
void printHelp();
void run(uint8_t opcode, int* IP, struct regs *rg, int v);//, uint8_t* buffer);
/*
	MEMORY
*/
uint8_t memory[1000000]; // create 1mb of memory
// FILE
uint8_t* buffer;
int main(int args, char** argv){
	int v = 1;
	//if(argv[2] == "-v") v = 1;
	struct regs rg = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	if(!argv[1]){
		printHelp();
	}
	// LOAD FILE
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){printf("[FATAL ERROR] FILE %s NOT FOUND\n",argv[1]);
	exit(1);}
	fseek(fp, 0L, SEEK_END);
	int s = ftell(fp);
	
	buffer = (uint8_t*)malloc(sizeof(uint8_t)*ftell(fp));
	rewind(fp);
	fread(buffer,sizeof(uint8_t)*s,1,fp);
	
	//
	// run
	printf("SIZE = %d\n",s);
	while(IP < s){
		if(buffer[IP] == 0) IP= IP + 1; 
		printf("CURRENTLY EXECUTING: %x\n",buffer[IP]);
		//if(i % 10 == 0)
		//	printf("\n");
		run(buffer[IP],&IP, &rg,v);//, buffer);
		// give us an update
		if(v == 1){
			printf("REGISTERS: \n");
			printf("AH = %x\n",rg.AH);
			printf("BH = %x\n",rg.BH);
			printf("CH = %x\n",rg.CH);
			printf("DH = %x\n",rg.DH);
			printf("AL = %x\n",rg.AL);
			printf("BL = %x\n",rg.BL);
			printf("CL = %x\n",rg.CL);
			printf("DL = %x\n",rg.DL);
			printf("AX = %x\n",rg.AX);
			printf("BX = %x\n",rg.BX);
			printf("CX = %x\n",rg.CX);
			printf("DX = %x\n",rg.DX);
			printf("=====================\n");
		}

	}
	// dump
	if(v == 1){
		printf("BINARY DUMP: \n");
		for(int i = 0; i < s; i++)
			printf("0x%x ",buffer[i]);
		printf("\n");
	}
	// Dump memory
	FILE* out = fopen("mem.bin", "wb");
	fwrite(memory,sizeof(memory),1,out);
	printf("Wrote contents of RAM to mem.bin.\n");
	if(1){
			printf("REGISTERS: \n");
			printf("AH = %x\n",rg.AH);
			printf("BH = %x\n",rg.BH);
			printf("CH = %x\n",rg.CH);
			printf("DH = %x\n",rg.DH);
			printf("AL = %x\n",rg.AL);
			printf("BL = %x\n",rg.BL);
			printf("CL = %x\n",rg.CL);
			printf("DL = %x\n",rg.DL);
			printf("AX = %x\n",rg.AX);
			printf("BX = %x\n",rg.BX);
			printf("CX = %x\n",rg.CX);
			printf("DX = %x\n",rg.DX);
			printf("=====================\n");
	}
	return 0;
}
void printHelp(){
	printf("intelEmu 8086\n");
	printf("Usage:\n");
	printf("./8086 binary\n");
}
// commands
void mov(uint8_t src, uint8_t *dest){
	printf("[mov] 0x%x to 0x%x\n",src,*dest);
	*dest = src;
}
// utils
int locInMem(uint8_t a){
	int addr = a;
	return addr;
}
void run(uint8_t opcode, int* IP,struct regs *rg, int v){
	printf("OP 0x%x at IP %d\n",opcode,*IP);
	switch(opcode){
		/*
			MOV INSTRUCTIONS
			MOV dest, src
			eg: mov AL, 3 ; move 3 into register al
		*/
		// MOV AL, ib
		case 0xb0:
			//rg->AL = buffer[*IP+1];
			mov(buffer[*IP+1], &rg->AL);
			*IP=*IP + 2;
			break;
		// MOV AH, ib
		case 0xb4:
			mov(buffer[*IP+1], &rg->AH);
			*IP=*IP + 2;
			break;
		// MOV AX, iw
		case 0xb8:
			mov(buffer[*IP+1], &rg->AX);
			*IP=*IP + 3;
			break;
		// MOV CL ib
		case 0xb1:
			mov(buffer[*IP+1], &rg->CL);
			*IP=*IP + 2;
			break;
		// MOV CH ib
		case 0xb5:
			mov(buffer[*IP+1], &rg->CH);
			*IP=*IP + 2;
			break;
		// MOV CX ib
		case 0xb9:
			mov(buffer[*IP+1], &rg->CX);
			*IP=*IP + 3;
			break;
		// MOV DL ib
		case 0xb2:
			mov(buffer[*IP+1], &rg->DL);
			*IP=*IP + 2;
			break;
		// MOV DH ib
		case 0xb6:
			mov(buffer[*IP+1], &rg->DH);
			*IP=*IP + 2;
			break;
		// MOV DX ib
		case 0xba:
			mov(buffer[*IP+1], &rg->DX);
			*IP=*IP + 2;
			break;
		// MOV BL ib
		case 0xb3:
			mov(buffer[*IP+1], &rg->BL);
			*IP=*IP + 2;
			break;
		// MOV BH ib
		case 0xb7:
			mov(buffer[*IP+1], &rg->BH);
			*IP=*IP + 2;
			break;
		// MOV BX ib
		case 0xbb:
			mov(buffer[*IP+1], &rg->BX);
			*IP=*IP + 3;
			break;
		// other adressing modes
		// MOV AL rmb
		case 0xa0:
			mov(&memory[buffer[*IP+1]], &rg->AL);
			*IP=*IP + 3;
			break;
		default:
			if(v == 1)
				printf("UNRECOGNIZED OPCODE 0x%x\n",opcode);
			*IP= *IP + 1;
			break;
	}
	//printf("[run] IP = %d\n",*IP);
}
