#include "stdafx.h"
////////////////////////////////////////////////////////////////
// TBox_Textures.cpp
// Converts a texture format to another
//
////////////////////////////////////////////////////////////////

//#include "jp/ggaf/core/util/XFile/ToolBox/TBox_Textures.h"

#define CTOL(C)     (*(UINT32*)&C)
#define PCTOL(PC)	  (*(UINT32*)PC)
#define PCTOS(PC)	  (*(UINT16*)PC)

////////////////////////////////////////////////////////////
// Main convert function
//
////////////////////////////////////////////////////////////
void ToolBox::ConvText::Convert(TEXTURE* pText, UINT8 pType) {
    if (pText->Type == pType)
        return;

    switch (pType) {
    case TXT_RGBA:
        if (pText->Type == TXT_RGB)
            RGB2RGBA(pText);
        break;
    case TXT_ALPHA:
        if (pText->Type == TXT_RGB)
            RGB2A(pText);
        break;
    case TXT_LA:
        if (pText->Type == TXT_RGB)
            RGB2LA(pText);
        break;

    }
}

////////////////////////////////////////////////////////////
// Convert a 24 bit texture to 32 bit while setting the
// alpha component to 0 if the color is the registerd tranp
// color
////////////////////////////////////////////////////////////
void ToolBox::ConvText::RGB2RGBA(TEXTURE* pText) {
    UINT8* tempBits;
    UINT32 tempSize;

    tempSize = pText->Width * pText->Height * 4;
    tempBits = NEW UINT8[tempSize];

    UINT32 src, dst;

    dst = 0;
    for (src = 0; src < pText->Size; src += pText->Depth, dst += 4) {
        tempBits[dst] = pText->Bits[src];
        tempBits[dst + 1] = pText->Bits[src + 1];
        tempBits[dst + 2] = pText->Bits[src + 2];
        tempBits[dst + 3] = 0;
        if (CTOL(tempBits[dst]) != _tColor)
            tempBits[dst + 3] = 255;
    }

    delete[] pText->Bits;
    pText->Bits = tempBits;
    pText->Size = tempSize;
    pText->Depth = 4;
    pText->Type = TXT_RGBA;
}

////////////////////////////////////////////////////////////
// Convert a 24 bit texture to 8 bit alpha
////////////////////////////////////////////////////////////
void ToolBox::ConvText::RGB2A(TEXTURE* pText) {
    UINT8* tempBits;
    UINT32 tempSize;

    tempSize = pText->Width * pText->Height * 1;
    tempBits = NEW UINT8[tempSize];

    UINT32 src, dst;
    UINT32 test;

    dst = 0;
    for (src = 0; src < pText->Size; src += pText->Depth, dst++) {
        test = (pText->Bits[src] << 24) + (pText->Bits[src + 1] << 16)
                + (pText->Bits[src + 2] << 8) + 0;
        if (test == _tColor)
            tempBits[dst] = 0;
        else
            tempBits[dst] = (UINT8) ((pText->Bits[src] + pText->Bits[src + 1]
                    + pText->Bits[src + 2]) / 3);
    }

    delete[] pText->Bits;
    pText->Bits = tempBits;
    pText->Size = tempSize;
    pText->Depth = 1;
    pText->Type = TXT_ALPHA;
}

////////////////////////////////////////////////////////////
// Convert a 24 bit texture to 16 bit luminance-alpha
////////////////////////////////////////////////////////////
void ToolBox::ConvText::RGB2LA(TEXTURE* pText) {
    UINT8* tempBits;
    UINT32 tempSize;

    tempSize = pText->Width * pText->Height * 2;
    tempBits = NEW UINT8[tempSize];

    UINT32 src, dst;
    UINT32 test;

    dst = 0;
    for (src = 0; src < pText->Size; src += pText->Depth, dst += 2) {
        test = (pText->Bits[src] << 24) + (pText->Bits[src + 1] << 16)
                + (pText->Bits[src + 2] << 8) + 0;
        if (test == _tColor) {
            tempBits[dst] = 0;
            tempBits[dst + 1] = 0;
        } else {
            tempBits[dst] = 255;
            tempBits[dst + 1] = (UINT8) ((pText->Bits[src] + pText->Bits[src
                    + 1] + pText->Bits[src + 2]) / 3);
        }
    }

    delete[] pText->Bits;
    pText->Bits = tempBits;
    pText->Size = tempSize;
    pText->Depth = 2;
    pText->Type = TXT_LA;
}

