#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

#include"defs.h"
#include"utils.h"
#include"processor.h"


int main(int argc, char** argv)
{
    Config cfg   ; memset(&cfg , 0 , sizeof(Config)) ; 
    int i=0 ;
    ProcessArgs( argc , argv , &cfg ) ; 
    Processor processor ; memset(&processor , 0 , sizeof(Processor)) ;
    processor.Registers = (int *) malloc( 32*sizeof(int)) ;
    InitializeRegisters( &processor) ; 
    for(i=0 ; i< cfg.CmdCount ; i++)
    {
        switch (cfg.Commands[i].cmd)
        {
            case ct_ADD:  
                ADD(&processor , cfg.Commands[i].Srd ,cfg.Commands[i].Srs , cfg.Commands[i].Srt , ct_ADD ) ;
                break;
            case ct_SUB:
                SUB(&processor , cfg.Commands[i].Srd ,cfg.Commands[i].Srs , cfg.Commands[i].Srt ,ct_SUB) ;
                break ; 
            case ct_AND:
                AND(&processor , cfg.Commands[i].Srd ,cfg.Commands[i].Srs , cfg.Commands[i].Srt ,ct_AND) ;
                break ;
            case ct_XOR:
                XOR(&processor , cfg.Commands[i].Srd ,cfg.Commands[i].Srs , cfg.Commands[i].Srt, ct_XOR ) ;
                break ;
            case ct_OR :
                OR(&processor , cfg.Commands[i].Srd ,cfg.Commands[i].Srs , cfg.Commands[i].Srt,ct_OR ) ;
                break ;
            case ct_ADDI:
                ADDI(&processor , cfg.Commands[i].Srd ,cfg.Commands[i].Srs , cfg.Commands[i].Imm , ct_ADDI ) ; //???
                break ;
            case ct_SUBI:
                SUBI(&processor , cfg.Commands[i].Srd ,cfg.Commands[i].Srs , cfg.Commands[i].Imm,ct_SUBI ) ;
                break ;
            case ct_ANDI:
                ANDI(&processor , cfg.Commands[i].Srd ,cfg.Commands[i].Srs , cfg.Commands[i].Imm ,ct_ANDI) ; 
                break ;
            case ct_XORI:
                XORI(&processor , cfg.Commands[i].Srd ,cfg.Commands[i].Srs , cfg.Commands[i].Imm ,ct_XORI) ; 
                break ;
            case ct_ORI:
                ORI(&processor , cfg.Commands[i].Srd ,cfg.Commands[i].Srs , cfg.Commands[i].Imm , ct_ORI) ; 
                break ;
            case ct_MOV:
                MOV( &processor , cfg.Commands[i] ) ; 
                break ;
            case ct_SWP:
                SWP(&processor , cfg.Commands[i].Srd ,cfg.Commands[i].Srs  ) ; 
                break ;
            case ct_DUMP_REGS:
                DUMP_REGS(&processor) ; 
                break ;
            case ct_DUMP_REGS_F:
                DUMP_REGS_F(&processor) ;
                break ;
            case ct_INPUT:
                INPUT( &processor) ; 
                break ;
            case ct_OUTPUT:
                OUTPUT( &processor ) ; 
                break ;
            case ct_JMP:
                CheckJump( &i , cfg.Commands[i].Jump ) ; 
                break ;
            case ct_EXIT:
                printf("program is closing.!!") ; 
                exit(0) ; 
                break ;
            default:
                printf("there was an error while processing input file") ; 
                exit(1) ;
                break;
        }
    }
    
    // // int i=10,j;
    // // char ch = 'A',ch2;
    // // float a=3.14,b;
    // // char str[20]="s21";
    
    // // FILE * file = fopen ("com.txt", "rb");
    // // char str1[10] = {'s','d','f','f','s','f'}, str2[10], str3[10];
    // // fscanf( file ,"%s %s %s" , &str1 , &str2 , &str3 );
    // // int oo = sscanf(str2 ,"%c%d",&ch2,&j);
    // // printf("%c %d \n",ch2 , j);
    // // j = MYPARSE( str ) ; 
    // // // printf( "%u" , j);
    // // int d = 99999 ;
    // int n = 1 ; 
    // // if( d < 0 )
    // //     n = 1 ; 
    // // else
    // //     n = 0 ; 
    // printf( "%u" , rr() << 3 );
    //int OverFlow = 0 ; 
    //int parity = 0 ; int sign = 0 ; int zero = 0 ; 
    //parity = 1 ;
    //sign   = ( 1 << 2)  ; 
    //zero = ( 1<< 1) ;
    //if( type == ct_ADD || type == ct_ADDI || ct_SUB== type || ct_SUBI == type )
    //   OverFlow = (1 << 5 ) ; 
    //processor->s0_register =0 ; 
    //printf( "%d\n"  , (parity + sign + zero + OverFlow)) ;   
    //printf( "%d"  , CheckParityFlag( 8 ) ) ;   
    
    return 0;

}

