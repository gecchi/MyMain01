/////////////////////////////////////////////////////////
// XFileStructs.h
//
//
/////////////////////////////////////////////////////////

#ifndef _XFILESTRUCTS_H
#define _XFILESTRUCTS_H
#include "jp/ggaf/GgafDxCommonHeader.h"

#define XOFFILE_FORMAT_MAGIC \
    ((int32_t)'x' + ((int32_t)'o' << 8) + ((int32_t)'f' << 16) + ((int32_t)' ' << 24))

#define XOFFILE_FORMAT_VERSION03 \
    ((int32_t)'0' + ((int32_t)'3' << 8))

//tsuge alter
#define XOFFILE_FORMAT_VERSION02 \
    ((int32_t)'0' + ((int32_t)'2' << 8))

#define XOFFILE_FORMAT_BINARY \
    ((int32_t)'b' + ((int32_t)'i' << 8) + ((int32_t)'n' << 16) + ((int32_t)' ' << 24))

#define XOFFILE_FORMAT_TEXT   \
    ((int32_t)'t' + ((int32_t)'x' << 8) + ((int32_t)'t' << 16) + ((int32_t)' ' << 24))

#define XOFFILE_FORMAT_COMPRESSED \
    ((int32_t)'c' + ((int32_t)'m' << 8) + ((int32_t)'p' << 16) + ((int32_t)' ' << 24))

#define XOFFILE_FORMAT_FLOAT_BITS_32 \
    ((int32_t)'0' + ((int32_t)'0' << 8) + ((int32_t)'3' << 16) + ((int32_t)'2' << 24))

#define XOFFILE_FORMAT_FLOAT_BITS_64 \
    ((int32_t)'0' + ((int32_t)'0' << 8) + ((int32_t)'6' << 16) + ((int32_t)'4' << 24))


struct XFileHeader {
   unsigned long Magic;
   unsigned short Major_Version;
   unsigned short Minor_Version;
   unsigned long Format;
   unsigned long Float_Size;
};

#define X_NAME         			 1
#define X_STRING       			 2
#define X_INTEGER      			 3
#define X_GUID         			 5
#define X_INTEGER_LIST 			 6
#define X_FLOAT_LIST   			 7

#define X_OBRACE      			 10
#define X_EBRACE      			 11
#define X_OPAREN      			 12
#define X_CPAREN      			 13
#define X_OBRACKET    			 14
#define X_CBRACKET    			 15
#define X_OANGLE      			 16
#define X_CANGLE      			 17
#define X_DOT         			 18
#define X_COMMA       			 19
#define X_SEMICOLON   			 20
#define X_TOKEN_TEMPLATE    	 31
#define X_WORD        			 40
#define X_DWORD       			 41
#define X_FLOAT       			 42
#define X_DOUBLE      			 43
#define X_CHAR        			 44
#define X_UCHAR       			 45
#define X_SWORD       			 46
#define X_SDWORD      			 47
#define X_VOID        			 48
#define X_LPSTR       			 49
#define X_UNICODE     			 50
#define X_CSTRING		     		 51
#define X_ARRAY       			 52

//Personal tokens
#define X_ERROR					 -1
#define X_TEMPLATE 				 60
#define X_HEADER 					 61
#define X_FRAME 					 62
#define X_FRAMETRANSFORMMATRIX 63
#define X_MESH 					 64
#define X_MESHTEXTURECOORDS 	 65
#define X_MESHMATERIALLIST 	 66
#define X_MATERIAL 				 67
#define X_SKINMESHHEADER 		 68
#define X_SKINWEIGHTS 			 69
#define X_TEXTUREFILENAME		 70
#define X_MESHNORMALS			 71
#define X_ANIMATIONSET			 72
#define X_ANIMATION			 	 73
#define X_ANIMATIONKEY		 	 74

#define X_COMMENT					 254
#define X_UNKNOWN					 255 //unknown block



#endif
