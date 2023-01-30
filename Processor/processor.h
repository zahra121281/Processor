#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include <stdio.h>
#include <string.h>
#include<math.h>
#include"defs.h"
#include"utils.h"

int CheckParityFlag(int num)
{
    int detector = 1 ; 
    int count = 0 ;
    int i=0; 
    int c = 0 ; 
    for(i=0 ; i< 32  ;i++ )
    {
        c = (detector & num) ; 
        detector = (detector << 1) ;
        if( c != 0 )
        {
            count += 1 ; 
        } 
    }
    if ( count %2 !=0 )
        return 1; 
    return 0 ;  
}

int CheckZeroFlag(int num)
{
    if( num == 0 )
        return 1 ; 
    return 0 ; 
}

int CheckSignFlag(int num)
{
    if( num < 0 )
        return 1 ;
    return 0 ;
}
int CheckOverFlowFlag(int Srd , int Srt , int Srs, cmd_type type )
{
    unsigned int detector = pow(2 , 31 ) ; 
    int signbit1 = Srt & detector ; 
    int signbit2 = Srs & detector ; 
    int signbit3 = Srd & detector ; 
    if( (signbit1*signbit2*(signbit3^1) + (signbit1^1)*(signbit2^1)*signbit3) == 1){
        printf("overflow has occured in calculating.!!\n") ; 
        return 1 ; 

    }
    return 0 ;

}

void CheckSituationRegister(Processor* processor , int Srd , int Srt , int Srs , cmd_type type )
{
    //0 1 2 5 
    int OverFlow = 0 ; 
    int parity = 0 ; int sign = 0 ; int zero = 0 ; 
    parity = CheckParityFlag( Srd) ;
    sign   = ( CheckSignFlag(Srd ) << 2)  ; 
    zero = (CheckZeroFlag(Srd ) << 1) ;
    if( type == ct_ADD || type == ct_ADDI || ct_SUB== type || ct_SUBI == type )
        OverFlow = (CheckOverFlowFlag(Srd , Srt , Srs, type) << 5 ) ; 
    //processor->s0_register =0 ; 
    processor->s0_register = (parity + sign + zero + OverFlow) ;   
}


void ADD( Processor* processor , int Srd ,int Srs ,int Srt, cmd_type type  )
{
    if( processor != NULL ){
        int srt = 0 , srs ; 
        if( Srt < 32 && Srs < 32&& Srd < 32  ){
            srt = processor->Registers[Srt] ; 
            srs = processor->Registers[Srs] ;
            processor->Registers[Srd] = srt + srs ; 
            CheckSituationRegister( processor , processor->Registers[Srd] , srs , srt,type  ) ; 
        }
        else
        {
            printf("the number of registers must be between 0 and 31.\n") ;
        }
    }
    else
    {
        printf("processor was null here !!\n") ; 
        return ; 
    }

}

void SUB( Processor* processor , int Srd ,int Srs ,int Srt, cmd_type type  )
{
    if( processor != NULL ){
        int srt = 0 , srs ; 
        if( Srt < 32 && Srs < 32 && Srd < 32 ){
            srt = processor->Registers[Srt] ; 
            srs = processor->Registers[Srs] ;
            processor->Registers[Srd] = srt - srs ; 
            CheckSituationRegister( processor , processor->Registers[Srd] , srs , srt,type  ) ; 
        }
        else
        {
            printf("the number of registers must be between 0 and 31.\n") ;
        }
    }
    else
    {
        printf("processor was null here !!\n") ; 
        return ; 
    }
}

void AND( Processor* processor , int Srd ,int Srs ,int Srt , cmd_type type )
{
    if( processor != NULL ){
        int srt = 0 , srs ; 
        if( Srt < 32 && Srs < 32&& Srd < 32  ){
            srt = processor->Registers[Srt] ; 
            srs = processor->Registers[Srs] ;
            processor->Registers[Srd] = srt & srs ; 
            CheckSituationRegister( processor , processor->Registers[Srd] , srs , srt  ,type  ) ; 
        }
        else
        {
            printf("the number of registers must be between 0 and 31.\n") ;
        }
    }
    else
    {
        printf("processor was null here !!\n") ; 
        return ; 
    }
}

void XOR( Processor* processor , int Srd ,int Srs ,int Srt, cmd_type type  )
{
    int srt = 0 , srs ; 
    if( processor !=NULL ){
        int srt = 0 , srs ; 
        if( Srt < 32 && Srs < 32  && Srd < 32  ){
            srt = processor->Registers[Srt] ; 
            srs = processor->Registers[Srs] ;
            processor->Registers[Srd] = srt ^ srs ; 
            CheckSituationRegister( processor , processor->Registers[Srd] , srs , srt,type  ) ; 
        }
        else
        {
            printf("the number of registers must be between 0 and 31.\n") ;
        }
    }
    else
    {
        printf("processor was null here !!\n") ; 
        return ; 
    }
}

void OR( Processor* processor , int Srd ,int Srs ,int Srt, cmd_type type  )
{
    int srt = 0 , srs ; 
    if( processor != NULL ){
        int srt = 0 , srs ; 
        if( Srt < 32 && Srs < 32  && Srd < 32  ){
            srt = processor->Registers[Srt] ; 
            srs = processor->Registers[Srs] ;
            processor->Registers[Srd] = srt | srs ; 
            CheckSituationRegister( processor , processor->Registers[Srd] , srs , srt,type  ) ; 
        }
        else
        {
            printf("the number of registers must be between 0 and 31.\n") ;
        }
    }
    else
    {
        printf("processor was null here !!\n") ; 
        return ; 
    }
}
void ADDI( Processor* processor , int Srt ,int Srs ,int imm  , cmd_type type )
{ 
    if( processor != NULL ){
        int srt = 0 , srs ; 
        if( Srt <32 && Srs < 32 ){
            srs = processor->Registers[Srs] ;
            processor->Registers[Srt] = imm + srs ; 
            CheckSituationRegister( processor , processor->Registers[Srt] , srs , imm , type ) ; 
        }
        else
        {
            printf("the number of registers must be between 0 and 31.\n") ;
        }
    }
    else
    {
        printf("processor can not be null!!\n") ; 
    }
}
void SUBI( Processor* processor , int imm ,int Srs ,int Srt , cmd_type type )
{
    if( processor != NULL ){
        int srt = 0 , srs ; 
        if( Srt <32 && Srs < 32 ){
            srs = processor->Registers[Srs] ;
            processor->Registers[Srt] =  srs - imm ; 
            CheckSituationRegister( processor , processor->Registers[Srt] , srs , imm , type ) ; 
        }
        else
        {
            printf("the number of registers must be between 0 and 31.\n") ;
        }
    }
    else
    {
        printf("processor can not be null!!\n") ; 
    }
}
void ANDI( Processor* processor , int imm ,int Srs ,int Srt , cmd_type type )
{
    if( processor != NULL ){
        int srt = 0 , srs ; 
        if( Srt <32 && Srs < 32 ){
            srs = processor->Registers[Srs] ;
            processor->Registers[Srt] =  srs & imm ; 
            CheckSituationRegister( processor , processor->Registers[Srt] , srs , imm , type ) ; 
        }
        else
        {
            printf("the number of registers must be between 0 and 31.\n") ;
        }
    }
    else
    {
        printf("processor can not be null!!\n") ; 
    }
}
void XORI( Processor* processor , int imm ,int Srs ,int Srt, cmd_type type  )
{
    if( processor != NULL ){
        int srt = 0 , srs ; 
        if( Srt <32 && Srs < 32 ){
            srs = processor->Registers[Srs] ;
            processor->Registers[Srt] =  srs ^ imm ; 
            CheckSituationRegister( processor , processor->Registers[Srt] , srs , imm , type ) ; 
        }
        else
        {
            printf("the number of registers must be between 0 and 31.\n") ;
        }
    }
    else
    {
        printf("processor can not be null!!\n") ; 
    }
}
void ORI( Processor* processor , int imm ,int Srs ,int Srt , cmd_type type )
{

    if( processor != NULL ){
        int srt = 0 , srs ; 
        if( Srt <32 && Srs < 32 ){
            srs = processor->Registers[Srs] ;
            processor->Registers[Srt] =  srs | imm ; 
            CheckSituationRegister( processor , processor->Registers[Srt] , srs , imm , type ) ; 
        }
        else
        {
            printf("the number of registers must be between 0 and 31.\n") ;
        }
    }
    else
    {
        printf("processor can not be null!!\n") ; 
    }
}

void MOV(Processor* processor , Cmd cmd )
{
    if( processor != NULL )
    {
        if( cmd.Is_Imm == 1 )
        {
            if( cmd.Srt < 32 )
                processor->Registers[cmd.Srt] = cmd.Imm ; 
            else
            {
                printf("the number of registers must be between 0 and 31.\n") ; 
            }
        }
        else
        {
            if( cmd.Srt < 32 && cmd.Srs < 32 )
                processor->Registers[cmd.Srt]  = processor->Registers[cmd.Srs] ; 
            else
                printf("the number of registers must be between 0 and 31.\n") ;
        }
    }
    else
    {
        printf("the processor can not be null !!\n") ; 
    }
}

void SWP(Processor *processor , int Srt , int Srs )
{
    if( processor != NULL )
    {
        if( Srt < 32 && Srs < 32 ){
            int tmp = processor->Registers[Srs] ; 
            processor->Registers[Srs] = processor->Registers[Srt];
            processor->Registers[Srt] = tmp ; 
        }
        else
        {
            printf("the number of registers must be between 0 and 31.\n") ;
        }
    }
    else
    {
        printf("the processor can not be null !!\n") ; 
    }
    
}

void DUMP_REGS(Processor *processor )
{
    if( processor != NULL )
    {
        int i = 0 ;
        for(i=0 ; i< 32 ;i++ )
        {
            printf("register number %d :%d\n" ,i ,processor->Registers[i]  ) ; 
        }
        printf("Register S0: %u\n" , processor->s0_register) ; 
    }
    else
    {
        printf("the processor can not be null !!\n") ; 
    }

}

void DUMP_REGS_F(Processor* processor)
{
    FILE* file; file = fopen("DUMP_REGS.txt","w");
    if (file == NULL) 
    {
        printf("Error: file pointer is null.\n");
        exit(1);
    }
    if( processor != NULL ){
        int i=0;
        for( i=0 ; i< 32 ;i++ )
        {
            fprintf(file ,"register number %d :%d\n" ,i ,processor->Registers[i] );
        }
        fprintf(file , "Register S0: %u" , processor->s0_register ) ;
        fclose(file) ;
    }
    else
    {
        printf("the processor can not be null !!\n") ; 
    } 
}

void INPUT(Processor* processor)
{
    if( processor != NULL )
    {
        char S0[10]  ; 
        printf("enter input : \n") ; 
        scanf( "%s" , &S0) ; 
        if( TryParse( S0 ) == 0)
        { 
            processor->s0_register = MYPARSE(S0) ; 
        }
        else
        {
            printf("your input was not valid.\n") ; 
            return ; 
        }
    }
    else
    {
        printf("the processor can not be null !!\n") ; 
    }
}

void OUTPUT(Processor* processor)
{
    if( processor != NULL )
        printf("%d" , processor->s0_register ) ; 
    else
        printf("the processor can not be null !!\n") ; 
}



#endif 
