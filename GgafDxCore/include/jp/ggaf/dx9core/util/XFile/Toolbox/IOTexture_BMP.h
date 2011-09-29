/////////////////////////////////////////////////////////
// IOTexture_BMP.h
// load/save BMP textures
//
/////////////////////////////////////////////////////////

#ifndef IOTEXTURE_BMP
#define IOTEXTURE_BMP

#define DEBUG
#include <windows.h>
#include "../framework/frm_IO.h"
//#include <gl\freeglut.h>
//del gecchi
#include <stdio.h>

namespace ToolBox {

class IO_Texture_BMP: Frm::IO<TEXTURE> {
public:
    IO_Texture_BMP(void) {
        _Type = IO_BMP;
    }
    bool Load(std::string pFilename, TEXTURE &pT);
    bool Save(std::string pFilename, TEXTURE &pT);/**/
    bool Load(std::string pFilename, std::vector<TEXTURE> &pVT) {
        return false;
    }
    bool Save(std::string pFilename, std::vector<TEXTURE> &pVT) {
        return false;
    }
};

}
#endif
