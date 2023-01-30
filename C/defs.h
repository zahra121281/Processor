#ifndef __DEFS_H__
#define __DEFS_H__
#include"image_utils.h"

typedef enum 
{
    ct_Center = 1,
    ct_Zoom = 2,
    ct_Rotate = 3,
    ct_Hold = 4,
} cmd_type;


typedef struct _cmd
{
    cmd_type cmd;
    int steps;
    double cx,cy;                                       //to start the zoom 
    double zoom;
    double angle1;                                       //angle to rotate
} Cmd;


typedef struct _config
{
    int width;
    int height;
    Cmd* Commands;
    int CmdCount;

} Config;

typedef struct _image_state
{
    double cx1, cy1;
    double minx, maxx, miny, maxy;                      //to indicate the axises
    double angle2;                                       //last angle
    Config* config;                                     // height, width;
    int image_count;
    BitMapFile bmFileData;
} ImageState;
#endif