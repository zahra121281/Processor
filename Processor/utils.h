#ifndef __UTILS_H__
#define __UTILS_H__

#include<stdlib.h>
#include<stdio.h>
#include"defs.h"
#include<math.h>
#include<string.h>
#include<string.h>
#include <ctype.h>

#define BUFSIZE 1000



void InitializeRegisters( Processor* processor)
{
    int i = 0 ; 
    if( processor->Registers == NULL )
    {
        processor->Registers = (int *) malloc( 32*sizeof(int)) ;
    }
    for(i =0 ; i< 32 ;i++)
    {
        processor->Registers[i] = 0 ; 
    }
    processor->s0_register = 0 ; 
}

int MYPARSE(char str[] )
{
    int j=0 ; 
    char ch = 'A',ch2;
    if( isdigit(str[0]) )
        sscanf(str , "%d",&j) ; 
    else
        sscanf(str , "%c%d" , &ch2,&j) ;
    return j ; 
}

int TryParse(char str[] )
{
    int i=0 ; 
    for (i = 0; str[i] != '\0'; i++)
    {
    
        if (isalpha(str[i]) != 0){
            return 1 ; 
        }
    }
    return 0 ; 
}

void CheckJump( int* cmdno  , int jump)
{
    // if( jump <*cmdno )
    // {
    //     return ; //not sure 
    // }
    // else if( jump == *cmdno )
    // {
    //     return ; 
    // }
    if( (jump-2) > *cmdno ) 
    {  //jump > cmdno
        *cmdno = (jump-2) ; 
    }
}


void ProcessArgs(int argc , char** argv ,Config* cfg)
{
    char buff[BUFSIZE];
    FILE* file ;
    file = fopen( argv[1] , "r") ;
    if (file == NULL) 
    {
        printf("Error: file pointer is null.\n");
        exit(1);
    }

    Cmd commands[1000] ;
    int cmdno =0;
    int line=0;
    int token=1;
    char str1[10] = {'s' , 's'}, str2[10], str3[10];
    //int nnn = fscanf(file,"%s " , buff ) ; 
    while ( fscanf(file,"%s " , buff ) > 0 )
    {
        if( stricmp(buff ,  "SUB") == 0)
        {
            commands[cmdno].cmd = ct_SUB ;
            fscanf( file ,"%s%*c%s%*c%s" , &str1 , &str2 , &str3 );
            commands[cmdno].Srd = MYPARSE( str1 ) ; 
            commands[cmdno].Srs = MYPARSE(str2 ) ; 
            commands[cmdno].Srt = MYPARSE(str3 ) ; 
            //fscanf( file ,"%s %s %s" , commands[cmdno].Srd , commands[cmdno].Srs , commands[cmdno].Srt ) ; 
        }
        else if( stricmp( buff , "AND") == 0 )
        {
            commands[cmdno].cmd = ct_AND ;
            fscanf( file ,"%s%*c%s%*c%s" , &str1 , &str2 , &str3 );
            commands[cmdno].Srd = MYPARSE( str1 ) ; 
            commands[cmdno].Srs = MYPARSE(str2 ) ; 
            commands[cmdno].Srt = MYPARSE(str3 ) ;
        }

        else if( stricmp( buff , "XOR") == 0)
        {
            commands[cmdno].cmd = ct_XOR ;
            fscanf( file ,"%s%*c%s%*c%s" , &str1 , &str2 , &str3 );
            commands[cmdno].Srd = MYPARSE( str1 ) ; 
            commands[cmdno].Srs = MYPARSE(str2 ) ; 
            commands[cmdno].Srt = MYPARSE(str3 ) ;
        }
        else if( stricmp( buff , "OR") == 0)
        {
            commands[cmdno].cmd = ct_OR ;
            fscanf( file ,"%s%*c%s%*c%s" , &str1 , &str2 , &str3 );
            commands[cmdno].Srd = MYPARSE( str1 ) ; 
            commands[cmdno].Srs = MYPARSE(str2 ) ; 
            commands[cmdno].Srt = MYPARSE(str3 ) ;
        }
        else if( stricmp( buff , "ADDI")==0 )
        {
            commands[cmdno].cmd = ct_ADDI ;
            fscanf( file ,"%s%*c%s%*c%d" , &str1 , &str2 , &(commands[cmdno].Imm)) ; 
            commands[cmdno].Srt = MYPARSE( str1 ) ; 
            commands[cmdno].Srs = MYPARSE(str2 ) ; 
        }
        else if( stricmp( buff , "SUBI")==0)
        {
            commands[cmdno].cmd = ct_SUBI ;
            fscanf( file ,"%s%*c%s%*c%d" , &str1 , &str2 , &(commands[cmdno].Imm)) ; 
            commands[cmdno].Srt = MYPARSE( str1 ) ; 
            commands[cmdno].Srs = MYPARSE(str2 ) ;
        }
        else if( stricmp( buff , "ANDI")==0)
        {
            commands[cmdno].cmd = ct_ANDI ; 
            fscanf( file ,"%s%*c%s%*c%d" , &str1 , &str2 , &(commands[cmdno].Imm)) ; 
            commands[cmdno].Srt = MYPARSE( str1 ) ; 
            commands[cmdno].Srs = MYPARSE(str2 ) ;
        }
        else if( stricmp( buff , "XORI") ==0)
        {
            commands[cmdno].cmd= ct_XORI ; 
            fscanf( file ,"%s%*c%s%*c%d" , &str1 , &str2 , &(commands[cmdno].Imm)) ; 
            commands[cmdno].Srt = MYPARSE( str1 ) ; 
            commands[cmdno].Srs = MYPARSE(str2 ) ;
        }
        else if( stricmp( buff , "ORI")==0)
        {
            commands[cmdno].cmd= ct_ORI ; 
            fscanf( file ,"%s%*c%s%*c%d" , &str1 , &str2 , &(commands[cmdno].Imm)) ; 
            commands[cmdno].Srt = MYPARSE( str1 ) ; 
            commands[cmdno].Srs = MYPARSE(str2 ) ;
        }
        else if( stricmp( buff , "MOV")==0)
        {
            commands[cmdno].cmd= ct_MOV ; 
            fscanf( file ,"%s%*c%s" , &str1 ,&str2) ;
            if(isdigit( str2[0] ) )
            {
                commands[cmdno].Srt = MYPARSE(str1) ; 
                commands[cmdno].Imm = MYPARSE(str2)  ; 
                commands[cmdno].Is_Imm = 1 ; 
            } 
            else
            {
                commands[cmdno].Srt = MYPARSE( str1 ) ; 
                commands[cmdno].Srs = MYPARSE(str2 ) ;
                commands[cmdno].Is_Imm = 0 ; 
            }

            
        }
        else if( stricmp( buff , "SWP")==0)
        {
            commands[cmdno].cmd= ct_SWP; 
            fscanf( file ,"%s%*c%s" , &str1 ,&str2); 
            commands[cmdno].Srt = MYPARSE( str1 ) ; 
            commands[cmdno].Srs = MYPARSE(str2 ) ;

        }
        else if( stricmp( buff , "DUMP_REGS")==0)
        {
            commands[cmdno].cmd = ct_DUMP_REGS ; 
        }
        else if( stricmp( buff , "DUMP_REGS_F") ==0)
        {
            commands[cmdno].cmd = ct_DUMP_REGS_F ; 
        }
        else if( stricmp( buff , "INPUT")==0)
        {
            commands[cmdno].cmd = ct_INPUT ; 
        }
        else if( stricmp( buff , "OUTPUT")==0)
        {
            commands[cmdno].cmd = ct_OUTPUT ; 
        }
        else if( stricmp( buff , "JMP")==0)
        {
            commands[cmdno].cmd = ct_JMP ; 
            fscanf( file ,"%s" , &str1 );
            commands[cmdno].Jump = MYPARSE( str1 ) ; 
        }
        else if( stricmp( buff , "EXIT")==0)
        {
            commands[cmdno].cmd = ct_EXIT ; 
        }

        else if( stricmp( buff , "ADD")==0)
        {
            commands[cmdno].cmd = ct_ADD ;
            fscanf( file ,"%s%*c%s%*c%s" , &str1 , &str2 , &str3 );
            commands[cmdno].Srd = MYPARSE( str1 ) ; 
            commands[cmdno].Srs = MYPARSE(str2 ) ; 
            commands[cmdno].Srt = MYPARSE(str3 ) ;
        }
        cmdno++ ; 
    }

    fclose(file) ; 
    cfg->Commands = (Cmd*) malloc(cmdno*sizeof(Cmd));
    cfg->CmdCount = cmdno ; 
    int i=0 ; 
    for(i=0 ; i< cmdno ; i++ )
    {
        cfg->Commands[i] = commands[i] ;
    }

}


#endif