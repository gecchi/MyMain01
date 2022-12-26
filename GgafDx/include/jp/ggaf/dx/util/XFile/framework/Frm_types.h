/////////////////////////////////////////////////////////
// Frm_types.h
// Declares basic unambiguous types
//
/////////////////////////////////////////////////////////

#ifndef FRM_TYPES_H
#define FRM_TYPES_H
#include "GgafDxCommonHeader.h"
//#include "jp/ggaf/dx/util/XFile/ToolBox/MyTrace.h"

//del tsuge ëSïî C99 ÇÃå^Ç…ìùàÍ
//typedef short int int16;
//typedef long int int32;
//typedef unsigned short int uint16;
//typedef unsigned long int uint32;
//typedef unsigned char uint8;
//typedef short int int16;
//typedef long int int32;

//Screen description/////////////////////////////
#define OSSCREEN 0
#define GLSCREEN 1

//Resource Types/////////////////////////////////
#define LOAD_TXT 0

//Base IO Formats////////////////////////////////
#define IO_NOTYPE 0 //no file type defined
#define IO_BMP  1   //Bitmap file
#define IO_3DX	 14  //DirectX X 3D Model File description

//Texture description////////////////////////////
#define TXT_IDEM  0
#define TXT_ALPHA 1
#define TXT_LA    2
#define TXT_RGB   3
#define TXT_RGBA  4

struct TEXTURE {
    uint8_t Type, Depth; //Type of texture and bit depth
    uint32_t Width, Height; //Width and height of texture
    uint32_t Size; //Size of texture = Width * Height
    uint32_t Compressed; //Compressed size of texture
    uint8_t* Bits; //texture data
};

#include "jp/ggaf/dx/util/XFile/framework/Frm_3dMath.h"

#endif
