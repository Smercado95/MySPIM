#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{

}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{

}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    *data1 = Reg[r1];
    *data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    unsigned negative = offset >> 15;
    unsigned testNum = 1;
    
    if (negative == testNum)
        *extended_value = offset | 0xffff0000;
    else
        *extended_value = offset & 0x0000ffff;
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
    unsigned rType = 0;
    unsigned iType = 1;
    
    if (ALUSrc == iType)
        ALU(data1, extended_value, ALUOp, ALUresult, Zero);
    else if (ALUSrc == rType) {
        if (funct == 0x21)
            ALUOp = 0;
        else if (funct == 0x23)
            ALUOp = 1;
        else if (funct == 0x24)
            ALUOp = 4;
        else if (funct == 0x2a)
            ALUOp = 2;
        else if (funct == 0x2b)
            ALUOp = 3;
    }
    return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
   //If MemWrite = 1, write into memory
  //If MemRead = 1, read from memory

  //halt if memory is being accessed and if ALUresult is not word aligned
  if(MemWrite == 1 || MemRead == 1)
  {
    if(ALUresult % 4) != 0)
    {
      return 1;
    }
  }

  //Memread: read the content of the memory location addressed by ALUresult to *memdata
  //ALUresult shift the address to the RIGHT by 2 to form the index
  if(MemRead == 1)
  {
    *memdata = Mem[ALUresult >> 2];
  }

  //Memwrite: write the value of data2 to the memory location addressed by ALUresult
  //ALUresult shift the address to the RIGHT by 2 to form the index
  if(MemWrite == 1)
  {
    Mem[ALUresult >> 2] = data2;
  }

  return 0;
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
   //write the data to a regiser addressed by r2 or r3
  //If RegWrite == 1, and MemtoReg ==1, then data coming from memory
  //If RegWrite == 1, and MemtoReg ==0, then data coming from ALU_result

  if(RegWrite == 1)
  {
    //write memdata to register
    if(MemtoReg == 1)
    {
      if(RegDst == 1)
      {
        Reg[r3] = memdata;
      }
      else
      Reg[r2] = memdata;
    }

    //write ALUresult to register
    else(MemtoReg == 0)
    {
      if(RegDst == 0)
      {
        Reg[r2] = ALUresult;
      }
      else
      Reg[r3] = ALUresult;
    }
  }
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
     //Update: PC = PC + 4, increment by 4
  *PC += 4;

    //Branching: add the extended_value bitshifted by 2
    if(Zero == 1 && Branch == 1)
        *PC += extended_value << 2;

    //Jump: Left shift bits of jsec by 2 and use upper 4 bits of PC
    if(Jump == 1)
        *PC = (jsec << 2) | (*PC & 0xf0000000);
}

