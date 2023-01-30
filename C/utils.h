
#ifndef __UTILS_H__
#define __UTILS_H__

#include"defs.h"
#include"image_utils.h"
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<string.h>

static inline double to_degrees(double radians) {
    return radians * (180.0 / M_PI);
}

static inline double to_radian(double degree) {
    return degree * (M_PI/180.0);
}
#define BUFSIZE 1000
void ProcessArgs(int argc, char** argv, Config* outcfg, ImageState* state)
{
    BitmapImageHeader img_color;
    char buff[BUFSIZE];
    FILE* file;
    file = fopen(argv[1], "r"); 
    if (file == NULL) {
        printf("Error: file pointer is null.");
        exit(1);
    }
    Cmd commands[1000];
    int cmdno =0;
    int line=0;
    int token=1;
    
    fscanf(file , "%d%*c%d" , &(outcfg->width) , &(outcfg->height));
    fscanf(file , "%lf%*c%lf%*c%lf%*c%lf ",&(state->minx) ,&(state->maxx),&(state->miny),&(state->maxy));
while (fscanf(file,"%s ", buff)>0 ){

    if (strcmp(buff , "zoom")==0)
    {
        commands[cmdno].cmd = ct_Zoom;
        fscanf(file,"%lf%*c%d" , &(commands[cmdno].zoom) , &(commands[cmdno].steps));
    }
    else if (strcmp(buff , "center") == 0)
    {
        commands[cmdno].cmd = ct_Center;
        fscanf(file ,"%lf%*c%lf%*c%d" , &(commands[cmdno].cx) , &(commands[cmdno].cy),&(commands[cmdno].steps));
    }
    else if(strcmp(buff , "rotate") == 0)
    {
        commands[cmdno].cmd = ct_Rotate;
        fscanf(file,"%lf%*c%d" , &(commands[cmdno].angle1),&(commands[cmdno].steps));
    }
    else if(strcmp(buff , "hold") == 0)
    {
        commands[cmdno].cmd = ct_Hold;
        fscanf(file , "%d" , &(commands[cmdno].steps));
    }

    state->cx1 =0 ;state->cy1=0;

  cmdno++;    
}
    state->angle2 = 0;
    fclose(file);
    outcfg->CmdCount = cmdno;
    outcfg->Commands = (Cmd*) malloc(cmdno*sizeof(Cmd));
    for(int i=0 ;i < cmdno ;i++)
    {
        outcfg->Commands[i]=commands[i] ;  
    }
    
    InitImage(& state->bmFileData, state->config->height, state->config->width);
}

#endif

/*  width*height
minx,maxx,miny,maxy
zoom zoom:steps
center newx,newy:steps
rotate angle:steps
hold steps  */
 
 