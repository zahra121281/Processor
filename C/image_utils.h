#ifndef __IMAGE_UTILS_H__
#define __IMAGE_UTILS_H__
#include<stdlib.h>
#include<memory.h>
#include<stdio.h>
#include"defs.h"
#define COLORBITS 16
#define COLORBYTES (int)(COLORBITS/8)
#define NUMCOLORS (1<<COLORBITS)
#pragma pack(push,1)
typedef struct tagBITMAPFILEHEADER
{
    unsigned short bfType;  //specifies the file type                                  check
    unsigned int bfSize;  //specifies the size in bytes of the bitmap file             check
    unsigned short bfReserved1;  //reserved; must be 0                                 check
    unsigned short bfReserved2;  //reserved; must be 0                                 check
    unsigned int bfOffBits;  //specifies the offset in bytes from the bitmapfileheader to the bitmap bits
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    unsigned int biSize;  //specifies the number of bytes required by the struct        check
    int biWidth;  //specifies width in pixels                                           check
    int biHeight;  //specifies height in pixels                                         check
    unsigned short biPlanes;  //specifies the number of color planes, must be 1         check
    unsigned short biBitCount;  //specifies the number of bits per pixel                check 
    unsigned int biCompression;  //specifies the type of compression                    don't underestand yet
    unsigned int biSizeImage;  //size of image in bytes                                 check
    int biXPelsPerMeter;  //number of pixels per meter in x axis                        check
    int biYPelsPerMeter;  //number of pixels per meter in y axis                        check
    unsigned int biClrUsed;  //number of colors used by the bitmap                      check
    unsigned int biClrImportant;  //number of colors that are important                 check  (again)
}BITMAPINFOHEADER;

typedef struct tagCOLORTABLE {                                                         //check 
    unsigned char r,g,b,junk;
} COLORINDEX;

typedef struct tagBitmapImageHeader {
    BITMAPFILEHEADER bmFileHeader;                                                     //check
    BITMAPINFOHEADER bmInfoHeader;                                                     //check
    COLORINDEX colorIdx[NUMCOLORS];                                                          //check
} BitmapImageHeader;

typedef struct tagBitMapFile {
    BitmapImageHeader bmHeader;                                                         //check
    unsigned char * bmData;    //char                                                             //check
} BitMapFile;

#pragma pack(pop)


void InitImage(BitMapFile* pbmFile, int height, int width)
{
    unsigned int headerSize = 
        sizeof(BITMAPFILEHEADER) + 
        sizeof(BITMAPINFOHEADER) + 
        sizeof(COLORINDEX) * NUMCOLORS;  
    memset(pbmFile, 0, sizeof(BitMapFile));
    pbmFile->bmHeader.bmInfoHeader.biWidth = width;
    pbmFile->bmHeader.bmInfoHeader.biHeight = height;
    pbmFile->bmHeader.bmFileHeader.bfType =  (((unsigned short)'M') << 8) | 'B';
    pbmFile->bmHeader.bmFileHeader.bfSize = headerSize + (width * height*COLORBYTES);
    pbmFile->bmHeader.bmFileHeader.bfOffBits = headerSize;
    pbmFile->bmHeader.bmInfoHeader.biBitCount = COLORBITS;
    pbmFile->bmHeader.bmInfoHeader.biSize = 40;
    pbmFile->bmHeader.bmInfoHeader.biPlanes = 1;
    pbmFile->bmHeader.bmInfoHeader.biSizeImage = (width * height * COLORBYTES);
    pbmFile->bmHeader.bmInfoHeader.biXPelsPerMeter = width ;
    pbmFile->bmHeader.bmInfoHeader.biYPelsPerMeter = height;
    pbmFile->bmHeader.bmInfoHeader.biClrUsed = NUMCOLORS;
    pbmFile->bmData = (unsigned char*) malloc(width * height * COLORBYTES);
}//unsigned char

void WriteBitmapFile(int fileNumber, BitMapFile* pbmFile)
{
    char filename[255];
    sprintf(filename, "%05d.bmp", fileNumber);
    FILE *filePtr = fopen(filename,"wb");
    if (filePtr == NULL)
    {
        printf("Error opening file for write.");
        return;
    }        

    fwrite(& pbmFile->bmHeader, sizeof(BitmapImageHeader), 1, filePtr);
    fwrite( pbmFile->bmData, pbmFile->bmHeader.bmInfoHeader.biSizeImage, 1, filePtr);
    fclose(filePtr);
}

#endif