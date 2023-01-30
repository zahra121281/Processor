#ifndef __DEFS_H__
#define __DEFS_H__
#include <string.h>

typedef enum 
{
    //put the names of your methods here ; 
    ct_SUB =1 ,
    ct_AND =2  , 
    ct_XOR = 3, 
    ct_OR  = 4 , 
    ct_ADDI =5, 
    ct_SUBI =6, 
    ct_ANDI =7, 
    ct_XORI =8, 
    ct_ORI =9, 
    ct_MOV =10,
    ct_SWP =11, 
    ct_DUMP_REGS =12, 
    ct_DUMP_REGS_F =13, 
    ct_INPUT =14, 
    ct_OUTPUT =15, 
    ct_JMP =16, 
    ct_EXIT =17 ,
    ct_ADD =18

} cmd_type;


typedef struct _cmd
{
    cmd_type cmd;
    int Srs ;
    int Srt ;
    int Srd ;  
    int Imm ;  
    int Jump ; 
    int Is_Imm ;                                   
} Cmd;
typedef struct _config
{
    Cmd* Commands;
    int CmdCount;
} Config;

//rd rs rt

typedef struct _processor
{
    int* Registers ; 
    unsigned char s0_register ;   
} Processor;



#endif