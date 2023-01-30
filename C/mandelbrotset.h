#ifndef __MANDELBROTSET_H__
#define __MANDELBROTSET_H__

#include"defs.h"
#include"utils.h"
#include<math.h>


int MAX_ITER = 200;
int get_mbs_iter(long double x,long double y)
{
    
    int count =0;
    long double zx =0; long double zy = 0; 
    long double nzx =0; long double nzy =0;
    while ((nzx*nzx + nzy*nzy ) <= 4 && count < MAX_ITER)
    {
        nzx = zx*zx - zy*zy + x; 
        nzy = 2*zx*zy + y;
        zx = nzx ;    
        zy = nzy;
        count++;
    }
    if (count == MAX_ITER)
    {
        return count;
    }    
    else{
        return (count + 1 - (log2(log2(sqrt(nzx*nzx+nzy*nzy)))/2) );
    }
}


void fill_ColorIndex_rgb(ImageState* img , BitmapImageHeader* img_color)
{
    unsigned char R, G ,B;
    int v=0;
    int iter_count;
    int a=0;
        for(iter_count=0;iter_count<=MAX_ITER;(iter_count)++)
        {
            if(iter_count < MAX_ITER)
            {
                v = 765* iter_count/MAX_ITER;
                if(v > 510)
                {
                   R = 255 ;
                   G = 255 ;
                   B = v%255;
                }
                else if(v>255)
                {
                    R = 100;  
                    G = v%255 ;
                    B = 255;
                }
                else
                {
                    R = 0 ;
                    G = 0;
                    B = v%255;
                }
            }
            else
            {
                R = 0 ;G = 0;B =0;
            }
        
        img->bmFileData.bmHeader.colorIdx[iter_count].r = B;
        img->bmFileData.bmHeader.colorIdx[iter_count].g = G;
        img->bmFileData.bmHeader.colorIdx[iter_count].b = R;
        }
        img->bmFileData.bmHeader.bmInfoHeader.biClrUsed = 200;
}


double UpdateImageData(ImageState* state)
{   

    int width = state->config->width;
    int height = state->config->height;
    float X_PIXEL_UNIT = (state->maxx - state->minx)/width;
    float Y_PIXEL_UNIT = (state->maxy - state->miny)/height;
    long double dx ,dy ,r ;
    long double  angel_rad;
    int count=0;
    long double nx , ny;
    double average_color=0;
    for(int y=0;y<height;y++)
{
        for(int x=0;x<width;x++)
        {
            angel_rad = to_radian(state->angle2);
            dx = state->minx + (x*X_PIXEL_UNIT);
            dy = state->maxy - (y*Y_PIXEL_UNIT);
            nx = dx*cos(angel_rad) + dy*sin(angel_rad);
            ny = dy*cos(angel_rad) - dx*sin(angel_rad);
            count = get_mbs_iter(nx, ny);
            state->bmFileData.bmData[(width*y + x)*COLORBYTES] = (unsigned char)(count);
            average_color += count;
        }//
}       
        return average_color/(width*height);    
}

double* ChangeCenter(ImageState* state, double newcx, double newcy, int steps)
{
    double unit_x , unit_y;
    unit_x = (newcx - state->cx1)/steps;
    unit_y = (newcy - state->cy1)/steps;
    double average_color ;
    double *buff = (double*) malloc(sizeof(double)*steps);
    for(int i=1;i<=steps; i++)
    {
        state->minx += (unit_x);
        state->maxx += (unit_x);
        state->miny += (unit_y);
        state->maxy += (unit_y);
        state->cx1 += (unit_x);
        state->cy1 += (unit_y);
        *(buff+i-1) = UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
        printf("center image :%d coordinate (%lf,%lf,%lf,%lf), angel: %lf\n",
        state->image_count,state->minx , state->maxx,state->miny,state->maxy,state->angle2);
    }
    return buff;
}

double* ChangeZoom(ImageState* state, double zoom, int steps)
{
    double* buff;
    buff = (double*) malloc(sizeof(double)*steps);
    long double newminx = state->minx/zoom;
    long double newmaxx = state->maxx/zoom;
    long double newmaxy = state->maxy/zoom;
    long double newminy = state->miny/zoom;
    long double UINT_X1 = (state->maxx - newmaxx)/steps;
    long double UNIT_Y1 = (state->maxy - newmaxy)/steps;
    long double UNIT_X2 = (newminx-state->minx)/steps;
    long double UNIT_Y2 = (newminy - state->miny)/steps;
    for(int i=1; i<=steps; i++)
    {
        state->minx += (double)UNIT_X2;
        state->maxy -= (double)UNIT_Y1;
        state->miny += (double)UNIT_Y2;
        state->maxx -= (double)UINT_X1;
        *(buff+i-1) = UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
        printf("zoom image :%d coordinate (%lf,%lf,%lf,%lf), angel: %lf\n",
        state->image_count,state->minx , state->maxx,state->miny,state->maxy,state->angle2);
    }
    return buff;
}

double* ChangeRotation(ImageState* state, double angle, int steps)
{
    long double average_color;
    double* buff= (double*) malloc(sizeof(double)*steps);
    long double angle_unit = angle/steps;
    for(int i=1; i<=steps; i++)
    {
        state->angle2 = (double)angle_unit*i;
        *(buff+i-1) = UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
        printf("rotate image :%d coordinate (%lf,%lf,%lf,%lf), angel: %lf\n",
        state->image_count,state->minx , state->maxx,state->miny,state->maxy,state->angle2);
       
    }
    return buff;
}

double* Hold(ImageState* state, int steps)
{
  
    double* buff = (double*) malloc(sizeof(double)*steps);
    for(int i=1; i<=steps; i++)
    {
        *(buff+i-1) = UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
    return buff;
}


#endif