#include<stdio.h>
#include<stdlib.h>
#include"defs.h"
#include"utils.h"
#include"mandelbrotset.h"

int main(int argc, char** argv)
{
    FILE* file;
    double buff[2000];
    double average_color ;double* num;
    file = fopen("audio.txt","w");
    Config cfg; memset(&cfg, 0, sizeof(Config));
    BitmapImageHeader img_color; memset(&img_color , 0 ,sizeof(COLORINDEX));  
    ImageState state; memset(&state, 0, sizeof(ImageState));
    state.config = &cfg;                          
    ProcessArgs(argc, argv, &cfg, &state);
    fill_ColorIndex_rgb(&state ,&img_color);
    average_color = UpdateImageData(&state);
    WriteBitmapFile(state.image_count++, & state.bmFileData);
    fprintf(file ,"the first picture and average colorindex is %lf\n",average_color );

    for(int i=0;i<cfg.CmdCount; i++)
    {
         switch (cfg.Commands[i].cmd)
         {
             case ct_Center:
                num = ChangeCenter(&state, cfg.Commands[i].cx, cfg.Commands[i].cy, cfg.Commands[i].steps);
                for(int j=0;j<cfg.Commands[i].steps;j++)
                {
                    buff[j] = *(num+j);
                    fprintf(file,"%dth center & average color is %lf\n" ,j+1, buff[j]);
                }
                free(num);
                break;
            
              case ct_Zoom:
                num = ChangeZoom(&state, cfg.Commands[i].zoom, cfg.Commands[i].steps);
                for(int a=0;a<cfg.Commands[i].steps;a++)
                {
                    buff[a] = *(num+a);
                    fprintf(file , "%dth zoom center & averge color is %lf\n" ,a+1, buff[a]);
                }
                free(num);
                break;

              case ct_Rotate:
                num = ChangeRotation(&state, cfg.Commands[i].angle1, cfg.Commands[i].steps);
                 for(int z=0; z <cfg.Commands[i].steps;z++)
                 {
                    buff[z] = *(num+z);
                    fprintf(file , "%dth rotate & averge color is %lf\n" ,z+1, buff[z]);
                 }
                 free(num);
                break;

              case ct_Hold:
                num = Hold(&state, cfg.Commands[i].steps);
                for(int b=0;b<cfg.Commands[i].steps;b++)
                {
                    buff[b] = *(num+b);
                    fprintf(file ,"%dth hold & average color is %lf\n" , b+1,buff[b]);
                }
                free(num);
                break;

       }
    }
    fclose(file);
    return 0;
}