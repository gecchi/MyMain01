/////////////////////////////////////////////////////////
// XFileStructs.h
//
//
/////////////////////////////////////////////////////////

#ifndef _XFILESTRUCTS_H
#define _XFILESTRUCTS_H

#define XOFFILE_FORMAT_MAGIC \
    ((INT32)'x' + ((INT32)'o' << 8) + ((INT32)'f' << 16) + ((INT32)' ' << 24))

#define XOFFILE_FORMAT_VERSION03 \
    ((INT32)'0' + ((INT32)'3' << 8))

//tsuge alter
#define XOFFILE_FORMAT_VERSION02 \
    ((INT32)'0' + ((INT32)'2' << 8))

#define XOFFILE_FORMAT_BINARY \
    ((INT32)'b' + ((INT32)'i' << 8) + ((INT32)'n' << 16) + ((INT32)' ' << 24))

#define XOFFILE_FORMAT_TEXT   \
    ((INT32)'t' + ((INT32)'x' << 8) + ((INT32)'t' << 16) + ((INT32)' ' << 24))

#define XOFFILE_FORMAT_COMPRESSED \
    ((INT32)'c' + ((INT32)'m' << 8) + ((INT32)'p' << 16) + ((INT32)' ' << 24))

#define XOFFILE_FORMAT_FLOAT_BITS_32 \
    ((INT32)'0' + ((INT32)'0' << 8) + ((INT32)'3' << 16) + ((INT32)'2' << 24))

#define XOFFILE_FORMAT_FLOAT_BITS_64 \
    ((INT32)'0' + ((INT32)'0' << 8) + ((INT32)'6' << 16) + ((INT32)'4' << 24))


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
