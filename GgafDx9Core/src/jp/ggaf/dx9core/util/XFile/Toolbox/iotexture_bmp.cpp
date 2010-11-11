#include "stdafx.h"
/////////////////////////////////////////////////////////
// IOTexture_BMP.cpp
// load/save BMP textures
//
/////////////////////////////////////////////////////////

//#include "jp/ggaf/core/util/XFile/ToolBox/IOTexture_Bmp.h"

//#define EXIT        {fclose(in); return false;}
//#define EXIT(msg)   {MYTRACE(msg); fclose(in); return false;}

bool ToolBox::IO_Texture_BMP::Load(std::string pFilename, TEXTURE &pT) {
    BITMAPFILEHEADER BmpFH;
    BITMAPINFOHEADER BmpIH;

    // Lit le fichier et son header
    FILE * in = fopen(pFilename.data(), "rb");
    if (!in)
        return false;
    if (fread(&BmpFH, 1, 14, in) != 14) {
        fclose(in); return false;
    }
        //EXIT("Corrupt Bitmap file header.");
    if (fread(&BmpIH, 1, 40, in) != 40) {
        fclose(in); return false;
    }
      //  EXIT("Corrupt Bitmap information header.");

    pT.Width = (uint16) BmpIH.biWidth;
    pT.Height = (uint16) BmpIH.biHeight;
    pT.Depth = (uchar) (BmpIH.biBitCount / 8);

    if (pT.Depth < 3) {
        fclose(in); return false;
    }
        //EXIT("8 and 16 bit depths are not supported.");

    if (BmpIH.biSizeImage == 0) {
        pT.Size = (uint32) (BmpIH.biWidth * BmpIH.biHeight * BmpIH.biBitCount
                / 8);
    } else {
        pT.Size = (uint32) BmpIH.biSizeImage;
    }
    pT.Bits = NEW uchar[pT.Size];

    switch (BmpIH.biBitCount) {
    case 24:
        pT.Type = TXT_RGB;
        break;
    case 32:
        pT.Type = TXT_RGBA;
    }

    fread(pT.Bits, pT.Size, 1, in);

    // Inverse R et B
    uchar t;
    for (uint32 i = 0; i < pT.Size; i += pT.Depth) {
        t = pT.Bits[i];
        pT.Bits[i] = pT.Bits[i + 2];
        pT.Bits[i + 2] = t;
    }

    fclose(in);
    return true;
}

bool ToolBox::IO_Texture_BMP::Save(std::string pFilename, TEXTURE &pT) {
    return false;
}
